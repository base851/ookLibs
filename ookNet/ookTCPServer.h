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
#ifndef OOK_TCP_SERVER_H_
#define OOK_TCP_SERVER_H_

#include "ookLibs/ookThread/ookThread.h"
#include "ookLibs/ookCore/ookTextMsgHandler.h"
#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookMsgDispatcher.h"

#include "boost/asio.hpp"

class ookTCPServerThread;

typedef boost::shared_ptr<ookTCPServerThread> tcp_thread_ptr;

#ifndef socket_ptr
/*!
 boost::shared_ptr<tcp::socket>
 */
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
#endif

class ookTCPServer : public ookThread, public ookTextMsgHandler
{
public:

	ookTCPServer(int iPort);	
	ookTCPServer(const ookTCPServer& cpy);
	virtual ookTCPServer& operator= (const ookTCPServer &cpy);			
	virtual ~ookTCPServer();
	
	virtual void HandleMsg(ookTextMessagePtr msg);
	virtual void Run();
	
protected:
	
	virtual tcp_thread_ptr GetServerThread(socket_ptr sock);
	vector<tcp_thread_ptr>& GetServerThreads();
	void CleanServerThreads();
	
private:
	
	int			_iPort;	
	asio::io_service _ioService;	
	vector<tcp_thread_ptr> _vServerThreads;
	ookMsgDispatcher _dispatcher;
	
};

#ifndef ookTCPServerPtr
typedef boost::shared_ptr<ookTCPServer> ookTCPServerPtr;
#endif

#endif