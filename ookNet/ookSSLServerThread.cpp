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
#include "ookLibs/ookNet/ookSSLServerThread.h"

ookSSLServerThread::ookSSLServerThread(ssl_socket_ptr sock, ookMsgDispatcher* dispatcher) 
: _sock(sock), _dispatcher(dispatcher)
{
	
}

ookSSLServerThread::~ookSSLServerThread()
{
	try 
	{
		this->Stop();		
	}
	catch (...) 
	{
	}
}

string ookSSLServerThread::Read()
{
	string ret;
	
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
	
	return ret;
}

void ookSSLServerThread::HandleMsg(string msg)
{
	ookTextMessage message(msg);
	_dispatcher->PostMsg(&message);
}

void ookSSLServerThread::WriteMsg(string msg)
{	
	try
	{
		//Get the size of our header int and the message itself
		int messageSize = (int) msg.length();
		
		//Convert the int length value to our header string
		string msgHdr = ookString::ConvertInt2String(messageSize);
		msgHdr = ookString::LeftPad(msgHdr, '0', sizeof(int));
		
		string msgBuf = msgHdr + msg;
		
		asio::write(*_sock, asio::buffer(msgBuf, msgBuf.length()));
	}
	catch (system::error_code& e)
	{
		std::cerr << "Something bad happened in ookSSLServerThread::WriteMsg: " << e.message() << "\n";
	}		
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLServerThread::WriteMsg()" << endl;		
	}	
}

bool ookSSLServerThread::DoHandshake()
{
	try
	{
		system::error_code error;	

		_sock->handshake(boost::asio::ssl::stream_base::server, error);

		if(error)
		{
			cout << "SSL handshake error: " << error.message() << endl;
			return false;
		}

		return true;
	}
	catch (system::error_code& e) 
	{
		std::cerr << "Something bad happened in ookSSLServerThread::DoHandshake(): " << e.message() << endl;		
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLServerThread::DoHandshake()" << endl;		
	}

	return false;
}

void ookSSLServerThread::Run()
{
	try
	{
		if(this->DoHandshake())
		{
			cout << "Starting server thread..." << endl;

			while(this->IsRunning())
			{
				this->HandleMsg(this->Read());
			}
		}

		_sock->shutdown();
	}
	catch (system::error_code& e)
	{
		std::cerr << "Connection Closed: " << e.message() << "\n";
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSSLServerThread::Run()" << endl;		
	}		
}