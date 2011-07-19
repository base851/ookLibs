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
#include "ookLibs/ookUtil/ookString.h"
#include "ookLibs/ookNet/ookSSLClient.h"

ookSSLClient::ookSSLClient(string ipaddr, int iPort, base_method mthd)
: _ipaddr(ipaddr), _iPort(iPort), _context(_io_service, mthd)
{

}

ookSSLClient::~ookSSLClient()
{
	try
	{
		this->Stop();		
	}
	catch(...)
	{
	}
}

void ookSSLClient::AddVerifyPath(string path)
{
	boost::system::error_code err;
	
	_context.add_verify_path(path, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::AddVerifyPath(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::LoadVerifyFile(string filename)
{
	boost::system::error_code err;
	
	_context.load_verify_file(filename, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::LoadVerifyFile(): " << err.message() << endl;
		throw err;
	}
}


void ookSSLClient::SetOptions(int opt)
{
	boost::system::error_code err;
	
	_context.set_options(opt, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::SetOptions(): " << err.message() << endl;
		throw err;
	}
}

template <typename PasswordCallback>
void ookSSLClient::SetPasswordCallback(PasswordCallback cb)
{
	boost::system::error_code err;
	
	_context.set_password_callback(cb, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::SetPasswordCallback(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::SetVerifyMode(int mode)
{
	boost::system::error_code err;
	
	_context.set_verify_mode(mode, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::SetVerifyMode(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::UseCertificateChainFile(string filename)
{
	boost::system::error_code err;
	
	_context.use_certificate_chain_file(filename, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::UseCertificateChainFile(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::UseCertificateFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;
	
	_context.use_certificate_file(filename, frmt, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::UseCertificateFile(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::UsePrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;
	
	_context.use_private_key_file(filename, frmt, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::UsePrivateKeyFile(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::UseRSAPrivateKeyFile(string filename, base_file_format frmt=asio::ssl::context_base::pem)
{
	boost::system::error_code err;
	
	_context.use_rsa_private_key_file(filename, frmt, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::UseRSAPrivateKeyFile(): " << err.message() << endl;
		throw err;
	}
}

void ookSSLClient::UseTmpDHFile(string filename)
{
	boost::system::error_code err;
	
	_context.use_tmp_dh_file(filename, err);
	
	if(err)
	{
		cout << "Error in ookSSLClient::UseTmpDHFile(): " << err.message() << endl;
		throw err;
	}
}

string ookSSLClient::Read()
{
	string ret;
	
	try
	{
		//Initialize our size variables
		int messageSize = 0;
		int messageHeaderSize = sizeof(int); 
		system::error_code error;	
	
		//Fetch the message header which sets out the size of the upcoming message
		char* hdrBuf = new char[messageHeaderSize];
	
		long iRead = _sock->read_some(asio::buffer(hdrBuf, messageHeaderSize), error);	
	
		if((iRead == 0) || (iRead != messageHeaderSize) || error)
			throw error;
	
		hdrBuf[messageHeaderSize] = '\0';
	
		messageSize = atoi(hdrBuf);
	
		if(messageSize <= 0)
			throw error;
	
		//Now fetch the message
		char* msgBuf = new char[messageSize];
	
		iRead = _sock->read_some(asio::buffer(msgBuf, messageSize), error);	
	
		if((iRead == 0) || (iRead != messageSize) || error)
			throw error;	
	
		msgBuf[messageSize] = '\0';
	
		ret = msgBuf;
	}
	catch (system::error_code& e)
	{
		std::cerr << "Something bad happened in ookSSLServerThread::WriteMsg: " << e.message() << endl;
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLClient::Read()" << endl;		
	}			
	
	return ret;
}

void ookSSLClient::HandleMsg(string msg)
{
	cout << "Received: " << msg << endl;
}

void ookSSLClient::WriteMsg(string msg)
{
	try
	{
		//Get the size of our header int and the message itself
		int messageSize = (int) msg.length();
		
		if(messageSize <= 0)
			return;
		
		//Convert the int length value to our header string
		string msgHdr = ookString::ConvertInt2String(messageSize);
		msgHdr = ookString::LeftPad(msgHdr, '0', sizeof(int));
		
		string msgBuf = msgHdr + msg;
		
		asio::write(*_sock, asio::buffer(msgBuf, msgBuf.length()));
	}
	catch (system::error_code& e)
	{
		std::cerr << "Something bad happened in ookSSLServerThread::WriteMsg: " << e.message() << endl;
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLClient::WriteMsg()" << endl;		
	}		
}

bool ookSSLClient::DoHandshake()
{
	try
	{
		system::error_code error;	
	
		_sock->handshake(boost::asio::ssl::stream_base::client, error);
	
		if(error)
		{
			cout << "SSL handshake error: " << error.message() << endl;
			return false;
		}
	
		return true;
	}
	catch(system::error_code& e)
	{
		std::cerr << "Something bad happened in ookSSLServerThread::WriteMsg: " << e.message() << endl;		
	}
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLClient::DoHandshake()" << endl;		
	}	
	
	return false;
}

void ookSSLClient::Run()
{
	try 
	{	
		tcp::resolver resolver(_io_service);
		tcp::resolver::query query(tcp::v4(), _ipaddr, ookString::ConvertInt2String(_iPort));
		tcp::resolver::iterator iterator = resolver.resolve(query);
	
//		_context.set_verify_mode(boost::asio::ssl::context::verify_none); 
//		_context.load_verify_file("ca.pem");		
	
		_sock = boost::shared_ptr<ssl_socket>(new ssl_socket(_io_service, _context));	
		
		_sock->lowest_layer().connect(*iterator);	
	
		if(this->DoHandshake())
		{
			try
			{
				while(this->IsRunning())
				{
					this->HandleMsg(this->Read());
				}
			}
			catch (system::error_code& e)
			{
				std::cerr << "Connection Closed: " << e.message() << endl;
			}
		}
	} 
	catch (system::error_code& e) 
	{
		std::cerr << "Connection Closed: " << e.message() << endl;		
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLClient::Run()" << endl;		
	}
}
