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
#include "ookLibs/ookNet/ookTCPServer.h"

ookTCPServer::ookTCPServer(int iPort)
	: _iPort(iPort)
{
	_dispatcher.RegisterObserver(new ookMsgObserver<ookTCPServer, ookTextMessage>(this, &ookTCPServer::HandleMsg));
}

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

tcp_thread_ptr ookTCPServer::GetServerThread(socket_ptr sock)
{
	tcp_thread_ptr thrd(new ookTCPServerThread(sock, &_dispatcher));

	//Save off the server thread to our list
	_vServerThreads.push_back(thrd);
	
	return thrd;
}

vector<tcp_thread_ptr>& ookTCPServer::GetServerThreads()
{
	return _vServerThreads;
}

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

void ookTCPServer::HandleMsg(ookTextMessage* msg)
{
	cout << "Received message: " << msg->GetMsg() << endl;
}

void ookTCPServer::Run()
{
	try
	{
		tcp::acceptor accptr(_ioService, tcp::endpoint(tcp::v4(), _iPort));

		while(this->IsRunning())
		{
			//Get a new socket_ptr and accept a new connection
			socket_ptr sock = boost::shared_ptr<tcp::socket>(new tcp::socket(_ioService));
			accptr.accept(*sock);
	
			asio::ip::tcp::endpoint remote_ep = sock->remote_endpoint();
			
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
