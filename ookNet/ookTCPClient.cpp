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
#include "ookLibs/ookNet/ookTCPClient.h"

ookTCPClient::ookTCPClient(string ipaddr, int iPort)
	: _ipaddr(ipaddr), _iPort(iPort)
{
	
}

ookTCPClient::~ookTCPClient()
{
	try
	{
		this->Stop();		
	}
	catch(...)
	{
	}
}

string ookTCPClient::Read()
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

void ookTCPClient::HandleMsg(string msg)
{
	cout << "Received: " << msg << endl;
}

void ookTCPClient::WriteMsg(string msg)
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
		std::cerr << "Connection Closed: " << e.message() << "\n";
	}	
}

void ookTCPClient::Run()
{
	tcp::resolver resolver(_ioService);
	tcp::resolver::query query(tcp::v4(), _ipaddr, ookString::ConvertInt2String(_iPort));
	tcp::resolver::iterator iterator = resolver.resolve(query);
	
	_sock = auto_ptr<tcp::socket>(new tcp::socket(_ioService));	
	_sock->connect(*iterator);	
	
	try
	{
		while(this->IsRunning()  && _sock->is_open())
		{
			this->HandleMsg(this->Read());
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Connection Closed: " << e.what() << "\n";
	}		
}