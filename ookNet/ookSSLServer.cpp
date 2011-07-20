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

/*! 
 \brief Initialization constructor.
 */
ookSSLServer::ookSSLServer(int iPort, base_method mthd)
	: _iPort(iPort), _context(_io_service, mthd)
{	
	_dispatcher.RegisterObserver(new ookMsgObserver<ookSSLServer, ookTextMessage>(this, &ookSSLServer::HandleMsg));
}

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

void ookSSLServer::AddVerifyPath(string path)
{
	boost::system::error_code err;

	_context.add_verify_path(path, err);

	if(err)
		throw err;
}

void ookSSLServer::LoadVerifyFile(string filename)
{
	boost::system::error_code err;

	_context.load_verify_file(filename, err);

	if(err)
		throw err;
}


void ookSSLServer::SetOptions(int opt)
{
	boost::system::error_code err;

	_context.set_options(opt, err);

	if(err)
		throw err;
}

void ookSSLServer::SetPasswordCallback()
{
	boost::system::error_code err;

	_context.set_password_callback(boost::bind(&ookSSLServer::PasswordCB, this), err);

	if(err)
		throw err;
}

string ookSSLServer::PasswordCB() const
{
	return "";
}


void ookSSLServer::SetVerifyMode(int mode)
{
	boost::system::error_code err;

	_context.set_verify_mode(mode, err);

	if(err)
		throw err;
}

void ookSSLServer::UseCertificateChainFile(string filename)
{
	boost::system::error_code err;

	_context.use_certificate_chain_file(filename, err);

	if(err)
		throw err;
}

void ookSSLServer::UseCertificateFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context.use_certificate_file(filename, frmt, err);

	if(err)
		throw err;
}

void ookSSLServer::UsePrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context.use_private_key_file(filename, frmt, err);

	if(err)
		throw err;
}

void ookSSLServer::UseRSAPrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;

	_context.use_rsa_private_key_file(filename, frmt, err);

	if(err)
		throw err;
}

void ookSSLServer::UseTmpDHFile(string filename)
{
	boost::system::error_code err;

	_context.use_tmp_dh_file(filename, err);

	if(err)
		throw err;
}

ssl_thread_ptr ookSSLServer::GetServerThread(ssl_socket_ptr sock)
{
	ssl_thread_ptr thrd(new ookSSLServerThread(sock, &_dispatcher));

	//Save off the server thread to our list
	_vServerThreads.push_back(thrd);
	
	return thrd;
}

vector<ssl_thread_ptr>& ookSSLServer::GetServerThreads()
{
	return _vServerThreads;
}

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

void ookSSLServer::HandleMsg(ookTextMessage* msg)
{
	cout << "Received message: " << msg->GetMsg() << endl;
}

void ookSSLServer::Run()
{
	try
	{

		tcp::acceptor accptr(_io_service, tcp::endpoint(tcp::v4(), _iPort));
		
		//Now that the context and acceptor are initialized, we can start the io service
		//_io_service.run();
		
		while(this->IsRunning())
		{			
			boost::system::error_code err;

			ssl_socket_ptr sock = boost::shared_ptr<ssl_socket>(new ssl_socket(_io_service, _context));
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