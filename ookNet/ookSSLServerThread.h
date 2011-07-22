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
#ifndef OOK_SSL_SERVER_THREAD_H_
#define OOK_SSL_SERVER_THREAD_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookMsgDispatcher.h"
#include "ookLibs/ookCore/ookTextMessage.h"
#include "ookLibs/ookThread/ookThread.h"
#include "ookLibs/ookUtil/ookString.h"

#include "boost/bind.hpp"
#include "boost/asio.hpp"
#include "boost/asio/error.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/asio/ssl/context_base.hpp"

#include <iostream>

using namespace std;
using namespace boost;
using asio::ip::tcp;

class ookSSLServerThread : public ookThread
{
public:

	ookSSLServerThread(ssl_socket_ptr sock, ookMsgDispatcher* dispatcher);
	virtual ~ookSSLServerThread();

	virtual string Read();
	virtual void WriteMsg(string msg);
	virtual void HandleMsg(string msg);		

	virtual void Run();	

protected:

	virtual bool DoHandshake();

private:

	ssl_socket_ptr _sock;
	ookMsgDispatcher* _dispatcher;
};

#ifndef ookSSLServerThreadPtr
typedef boost::shared_ptr<ookSSLServerThread> ookSSLServerThreadPtr;
#endif

#endif