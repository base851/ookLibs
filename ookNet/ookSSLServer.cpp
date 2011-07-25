/*
 Copyright © 2011, Ted Biggs
 All rights reserved.
 http://tbiggs.com
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 
 - Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 
 - Neither the name of Ted Biggs, nor the names of his
 contributors may be used to endorse or promote products
 derived from this software without specific prior written
 permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */
 /*! 
 \class ookSSLServer
 \headerfile ookSSLServer.h "ookLibs/ookNet/ookSSLServer.h"
 \brief Base class for implementing an SSL server. This class simply 
 listens for connections and then hands them off to individual server
 threads which do the actual work.

 The Server and ServerThreads communicate via the Observer/Dispatcher/Handler
 framework found in ookCore. Servers derive from the ookTextMessageHandler class
 and maintain ookMsgDispatcher which is passed to the individual server threads.
 Both the server and server thread register interest in a particualr message type
 with the dispatcher. They also post messages to the dispatcher for handling. In
 this manner both the server and server thread can intercommunicate and only receive
 messages which they are interested in.
 */
#include "ookLibs/ookNet/ookSSLServer.h"
#include "ookLibs/ookNet/ookSSLServerThread.h"
#include "ookLibs/ookCore/ookMsgObserver.h"
#include "boost/asio.hpp"
#include "ookLibs/ookCore/ookMsgObserver.h"


/*! 
 \brief Initialization constructor.

 \param iPort	The server port.
 \param mthd	The asio::ssl::context_base::method for the connection.
 Default is asio::ssl::context_base::sslv23_client. Options are:

sslv2
sslv2_client
sslv2_server
sslv3
sslv3_client
sslv3_server
tlsv1
tlsv1_client
tlsv1_server
sslv23
sslv23_client
sslv23_server 
 */
ookSSLServer::ookSSLServer(int iPort, base_method mthd)
	: _iPort(iPort), _mthd(mthd)
{	
	_io_service = boost::shared_ptr<asio::io_service>(new asio::io_service);
	_context = boost::shared_ptr<asio::ssl::context>(new asio::ssl::context(*_io_service, mthd));
	_dispatcher.RegisterObserver(new ookMsgObserver<ookSSLServer, ookTextMessage>(this, &ookSSLServer::HandleMsg));
}

/*! 
 \brief Copy constructor.
 */
ookSSLServer::ookSSLServer(const ookSSLServer& cpy)
{
	_iPort = cpy._iPort;	
	_vServerThreads = cpy._vServerThreads;
	_dispatcher = cpy._dispatcher;
	_mthd = cpy._mthd;
  _io_service = cpy._io_service;
	_context = cpy._context;	
}

/*! 
 \brief Overloaded assignment operator.
 */
ookSSLServer& ookSSLServer::operator= (const ookSSLServer &cpy)
{
	if (&cpy != this)
	{
		_iPort = cpy._iPort;	
		_vServerThreads = cpy._vServerThreads;
		_dispatcher = cpy._dispatcher;
		_mthd = cpy._mthd;
		_io_service = cpy._io_service;
		_context = cpy._context;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */
ookSSLServer::~ookSSLServer()
{
	try
	{
		this->Stop();
	}
	catch (...)
	{
	}	
}

/*! 
 \brief Adds a directory path to verification files.

 \param path The full path to verification files.
 */
void ookSSLServer::AddVerifyPath(string path)
{
	boost::system::error_code err;

	_context->add_verify_path(path, err);

	if(err)
		throw err;
}

/*! 
 \brief Loads a verification file.

 \param filename The name of the verification file.
 */
void ookSSLServer::LoadVerifyFile(string filename)
{
	boost::system::error_code err;

	_context->load_verify_file(filename, err);

	if(err)
		throw err;
}

/*! 
 \brief Sets one or more options for the connection context.

 \param opt The option(s) for the connection. This is a bitwise OR 
 of boost::asio::ssl::context_base::options. Options are:

 SSL_OP_ALL
 SSL_OP_SINGLE_DH_USE
 SSL_OP_NO_SSLv2
 SSL_OP_NO_SSLv3
 SSL_OP_NO_TLSv1
 */
void ookSSLServer::SetOptions(int opt)
{
	boost::system::error_code err;

	_context->set_options(opt, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies the password callback function.

 \param cb The password callback function.
 */
void ookSSLServer::SetPasswordCallback()
{
	boost::system::error_code err;

	_context->set_password_callback(boost::bind(&ookSSLServer::PasswordCB, this), err);

	if(err)
		throw err;
}

/*! 
 \brief The password callback function. This should be overridden
 to return the correct password is the key file has a password.

 \return The password for the key file.
 */
string ookSSLServer::PasswordCB() const
{
	return "";
}

/*! 
 \brief Sets one or more options for peer verification.

 \param opt The option(s) for verification. This is a bitwise OR 
 of boost::asio::ssl::context_base::verify_mode. Options are:

 SSL_VERIFY_NONE
 SSL_VERIFY_PEER
 SSL_VERIFY_FAIL_IF_NO_PEER_CERT
 SSL_VERIFY_CLIENT_ONCE
 */
void ookSSLServer::SetVerifyMode(int mode)
{
	boost::system::error_code err;

	_context->set_verify_mode(mode, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies a certificate chain file to use.

	\param filename The name of the certificate chain file.
 */
void ookSSLServer::UseCertificateChainFile(string filename)
{
	boost::system::error_code err;

	_context->use_certificate_chain_file(filename, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies a certificate file to use.

 \param filename The name of the certificate file.
 \param frmt The asio::ssl::context_base::file_format of the certificate. Default is 
 asio::ssl::context_base::pem. Options are:

pem
asn1

 */
void ookSSLServer::UseCertificateFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context->use_certificate_file(filename, frmt, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies a private key file to use.

 \param filename The name of the private key file.
 \param frmt The asio::ssl::context_base::file_format of the certificate. Default is 
 asio::ssl::context_base::pem. Options are:

pem
asn1

 */
void ookSSLServer::UsePrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context->use_private_key_file(filename, frmt, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies an RSA private key file to use.

 \param filename The name of the RSA private key file.
 \param frmt The asio::ssl::context_base::file_format of the certificate. Default is 
 asio::ssl::context_base::pem. Options are:

pem
asn1

 */
void ookSSLServer::UseRSAPrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context->use_rsa_private_key_file(filename, frmt, err);

	if(err)
		throw err;
}

/*! 
 \brief Specifies a temporary DH file to use.

 \param filename The name of the temporary DH file.
 */
void ookSSLServer::UseTmpDHFile(string filename)
{
	boost::system::error_code err;

	_context->use_tmp_dh_file(filename, err);

	if(err)
		throw err;
}

/*! 
 \brief Instantiates a new server thread for a socket connection.

 \return A new ookSSLServerThread.
 */
ssl_thread_ptr ookSSLServer::GetServerThread(ssl_socket_ptr sock)
{
	ssl_thread_ptr thrd(new ookSSLServerThread(sock, &_dispatcher));

	//Save off the server thread to our list
	_vServerThreads.push_back(thrd);
	
	return thrd;
}

/*! 
 \brief Returns the current list of server threads.

 \return A list of ookSSLServerThreads.
 */
vector<ssl_thread_ptr>& ookSSLServer::GetServerThreads()
{
	return _vServerThreads;
}

/*! 
 \brief Iterates through the server thread list and removes any
 which are no longer running.
 */
void ookSSLServer::CleanServerThreads()
{
	int iSize = _vServerThreads.size();
	for(int i=0; i < iSize; i++)
	{
		bool bDoErase = false;

		try
		{
			if(_vServerThreads[i] == NULL)
				bDoErase = true;
			else if(!_vServerThreads[i]->IsRunning())
				bDoErase = true;
		}
		catch(...) //If something freaky happens we can trash it
		{
			bDoErase = true;
		}

		if(bDoErase)
		{
			_vServerThreads.erase(_vServerThreads.begin() + i);

			i--; //We want to back this up one so that we stay in the same 
					 //position in the loop. Everything just shifted left one slot.

			iSize--; //The size of the container just went down by one
		}
	}

}

/*! 
 \brief Handles a message forwarded by the observer/dispatcher. This should be 
 overriden and customized by implementing classes. For example, if the message 
 read in is in XML format, this is the method where the message could be parsed 
 and then dealt with accordingly.

 \return The message to be handled.
 */
void ookSSLServer::HandleMsg(ookTextMessagePtr msg)
{
	cout << "Received message: " << msg->GetMsg() << endl;
}

/*! 
 \brief The socket accept loop. Incoming socket connection requests are accepted
 and, if valid, forwarded to a new server thread for handling.
 */
void ookSSLServer::Run()
{
	try
	{

		tcp::acceptor accptr(*_io_service, tcp::endpoint(tcp::v4(), _iPort));
		
		//Now that the context and acceptor are initialized, we can start the io service
		//_io_service.run();
		
		while(this->IsRunning())
		{			
			boost::system::error_code err;

			ssl_socket_ptr sock = boost::shared_ptr<ssl_socket>(new ssl_socket(*_io_service, *_context));
			accptr.accept(sock->lowest_layer(), err);
			
			asio::ip::tcp::endpoint remote_ep = sock->lowest_layer().remote_endpoint();
			
			cout << "Accepted new client from " << remote_ep.address().to_string() << endl;			
			
			if(!err)
			{
				//Declare a server thread and start it up
				ssl_thread_ptr thrd = this->GetServerThread(sock);
				thrd->Start();	
			}
		}
		
		//_io_service.stop();
	}
	catch (std::exception& e)
	{
		std::cerr << "Something bad happened in ookSSLServer::Run: " << e.what() << "\n";
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLServer::Run()" << endl;		
	}	
}