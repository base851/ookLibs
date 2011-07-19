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
#ifndef OOK_SSL_SERVER_H_
#define OOK_SSL_SERVER_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookTextMsgHandler.h"
#include "ookLibs/ookCore/ookMsgDispatcher.h"
#include "ookLibs/ookCore/ookMsgObserver.h"
//#include "ookLibs/ookCrypt/ookSSLContext.h"
#include "ookLibs/ookThread/ookThread.h"
#include "ookLibs/ookNet/ookSSLServerThread.h"

typedef boost::shared_ptr<ookSSLServerThread> ssl_thread_ptr;

typedef boost::function<std::string(std::size_t,
																		asio::ssl::context_base::password_purpose)> password_callback_type;

class ookSSLServer : public ookThread, public ookTextMsgHandler
{
public:

	ookSSLServer(int iPort, base_method mthd = asio::ssl::context_base::sslv23);
	virtual ~ookSSLServer();

	virtual void HandleMsg(ookTextMessage* msg);
	virtual void Run();

	//The plethora of options available to initialize the context
	void AddVerifyPath(string path);
	void LoadVerifyFile(string filename);
	void SetOptions(int opt);
	
	virtual void SetPasswordCallback();
	virtual string PasswordCB() const;	
	
	void SetVerifyMode(int mode);
	void UseCertificateChainFile(string filename);
	void UseCertificateFile(string filename, base_file_format frmt);
	void UsePrivateKeyFile(string filename, base_file_format frmt);
	void UseRSAPrivateKeyFile(string filename, base_file_format frmt);
	void UseTmpDHFile(string filename);

protected:

	virtual ssl_thread_ptr GetServerThread(ssl_socket_ptr sock);
	vector<ssl_thread_ptr>& GetServerThreads();
	void CleanServerThreads();

	int			_iPort;	
	vector<ssl_thread_ptr> _vServerThreads;
	ookMsgDispatcher _dispatcher;
	
  asio::io_service _io_service;
  asio::ssl::context _context;	
	
private:


};


#endif