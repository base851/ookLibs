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
#ifndef OOK_TCP_CLIENT_H_
#define OOK_TCP_CLIENT_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookThread/ookThread.h"

class ookTCPClient : public ookThread
{
public:
	
	ookTCPClient(string ipaddr, int iPort);
	
	virtual ~ookTCPClient();
	
	virtual string Read();
	virtual void HandleMsg(string msg);
	
	virtual void WriteMsg(string msg);	
	
	virtual void Run();	
	
protected:
	
	
private:
	
	string	_ipaddr;
	int			_iPort;
	
	socket_ptr _sock;
	asio::io_service _ioService;
	
};

/*
 try
 {
 if (argc != 3)
 {
 std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
 return 1;
 }
 
 asio::io_service io_service;
 
 tcp::resolver resolver(io_service);
 tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
 tcp::resolver::iterator iterator = resolver.resolve(query);
 
 tcp::socket s(io_service);
 s.connect(*iterator);
 
 using namespace std; // For strlen.
 std::cout << "Enter message: ";
 char request[max_length];
 std::cin.getline(request, max_length);
 size_t request_length = strlen(request);
 asio::write(s, asio::buffer(request, request_length));
 
 char reply[max_length];
 size_t reply_length = asio::read(s,
 asio::buffer(reply, request_length));
 std::cout << "Reply is: ";
 std::cout.write(reply, reply_length);
 std::cout << "\n";
 }
 catch (std::exception& e)
 {
 std::cerr << "Exception: " << e.what() << "\n";
 }
 */



#endif