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
 \class ookTCPServer
 \headerfile ookTCPServer.h "ookLibs/ookNet/ookTCPServer.h"
 \brief Base class for implementing an TCP server. This class simply 
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
#include "ookLibs/ookNet/ookTCPServer.h"
#include "ookLibs/ookNet/ookTCPServerThread.h"
#include "ookLibs/ookCore/ookMsgObserver.h"

/*! 
 \brief Initialization constructor.

 \param iPort	The server port.
 */
ookTCPServer::ookTCPServer(int iPort)
	: _iPort(iPort)
{
	_dispatcher.RegisterObserver(new ookMsgObserver<ookTCPServer, ookTextMessage>(this, &ookTCPServer::HandleMsg));
}

/*! 
 \brief Destructor.
 */
ookTCPServer::~ookTCPServer()
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
 \brief Instantiates a new server thread for a socket connection.

 \return A new ookSSLServerThread.
 */
tcp_thread_ptr ookTCPServer::GetServerThread(socket_ptr sock)
{
	tcp_thread_ptr thrd(new ookTCPServerThread(sock, &_dispatcher));

	//Save off the server thread to our list
	_vServerThreads.push_back(thrd);
	
	return thrd;
}

/*! 
 \brief Returns the current list of server threads.

 \return A list of ookSSLServerThreads.
 */
vector<tcp_thread_ptr>& ookTCPServer::GetServerThreads()
{
	return _vServerThreads;
}

/*! 
 \brief Iterates through the server thread list and removes any
 which are no longer running.
 */
void ookTCPServer::CleanServerThreads()
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
			
			cout << "Removed expired thread from server list." << endl;
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
//void ookTCPServer::HandleMsg(ookTextMessage* msg)
void ookTCPServer::HandleMsg(ookTextMessagePtr msg)

{
	cout << "Received message: " << msg->GetMsg() << endl;
}

/*! 
 \brief The socket accept loop. Incoming socket connection requests are accepted
 and, if valid, forwarded to a new server thread for handling.
 */
void ookTCPServer::Run()
{
	try
	{
		boost::asio::ip::tcp::acceptor accptr(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _iPort));

		while(this->IsRunning())
		{
			//Get a new socket_ptr and accept a new connection
			socket_ptr sock = boost::shared_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(_ioService));
			accptr.accept(*sock);
	
			boost::asio::ip::tcp::endpoint remote_ep = sock->remote_endpoint();
			
			cout << "Accepted new client from " << remote_ep.address().to_string() << endl;
			
			//Declare a server thread and start it up
			tcp_thread_ptr thrd = this->GetServerThread(sock);
			thrd->Start();	

			//Do some cleanup on teh thread vector
			this->CleanServerThreads();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Something bad happened in ookTCPServer::Run: " << e.what() << "\n";
	}		
	
}
