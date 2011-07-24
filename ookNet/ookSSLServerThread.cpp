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
 \class ookSSLServerThread
 \headerfile ookSSLServerThread.h "ookLibs/ookNet/ookSSLServerThread.h"
 \brief Worker thread for SSL connections.

 The Server and ServerThreads communicate via the Observer/Dispatcher/Handler
 framework found in ookCore. Servers derive from the ookTextMessageHandler class
 and maintain ookMsgDispatcher which is passed to the individual server threads.
 Both the server and server thread register interest in a particualr message type
 with the dispatcher. They also post messages to the dispatcher for handling. In
 this manner both the server and server thread can intercommunicate and only receive
 messages which they are interested in.
 */
#include "ookLibs/ookNet/ookSSLServerThread.h"

/*! 
 \brief Initialization constructor.

 \param sock The thread's ssl_socket.
 \param dispatcher	The thread's message dispatcher.
 */
ookSSLServerThread::ookSSLServerThread(ssl_socket_ptr sock, ookMsgDispatcher* dispatcher) 
: _sock(sock), _dispatcher(dispatcher)
{
	
}

/*! 
 \brief Destructor.
 */
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

/*! 
 \brief Reads in a message from the socket. This particular implementation uses
 a numeric header to permit variable-length messaging. Thus, ookClients should
 communicate with ookServers and vice-versa.

 \return The message on the socket.
 */
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

/*! 
 \brief Handles a message read in by the server thread. This is the primary
 worker method that should be overriden and customized by implementing 
 classes. For example, if the message read in is in XML format, this is 
 the method where the message could be parsed and then dealt with accordingly.

 \return The message to be handled.
 */
void ookSSLServerThread::HandleMsg(string msg)
{
//	ookTextMessage message(msg);
//	_dispatcher->PostMsg(&message);
	_dispatcher->PostMsg(ookTextMessagePtr(new ookTextMessage(msg)));
}

/*! 
 \brief Writes a message to the socket. This particular implementation uses
 a numeric header to permit variable-length messaging. Thus, ookClients should
 communicate with ookServers and vice-versa.

 \param msg The message to be written on the socket.
 */
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

/*! 
 \brief Performs an SSL handshake with the client.

 \return true if the handshake succeeded, false otherwise.
 */
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

/*! 
 \brief The socket read loop. Incoming messages are read and forwarded to HandleMsg().
 */
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