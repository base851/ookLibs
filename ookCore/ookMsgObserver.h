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
////////////////////////////////////////////////////////////////
// This class a derived work of the Poco Notifier framework.
////////////////////////////////////////////////////////////////
#ifndef OOK_MESSAGE_OBSERVER_H_
#define OOK_MESSAGE_OBSERVER_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookMsgObserverAbs.h"
#include "ookLibs/ookCore/ookMessage.h"

template <class H, class M>
class ookMsgObserver : public ookMsgObserverAbs
{
	
#ifndef FP_OOK_MSG
	typedef void (H::*FP_OOK_MSG)(M*);
#endif		
	
public:
	
	ookMsgObserver(H* handler, FP_OOK_MSG func)
		: _handler(handler), _handlerFunc(func)
	{
		
	}
	
	virtual ~ookMsgObserver()
	{
		
	}

	ookMsgObserver& operator = (const ookMsgObserver& observer)
	{
		if (&observer != this)
		{
			_handler = observer._handler;
			_handlerFunc  = observer._handlerFunc;
		}
		return *this;
	}	
	
	void SendMessage(ookMessage* msg)
	{
		M* pCastNf = dynamic_cast<M*>(msg);
		if (pCastNf)
		{	
			(_handler->*_handlerFunc)(pCastNf);
		}
	}
	
	bool Accepts(ookMessage* msg) 
	{
		return dynamic_cast<M*>(msg) != 0;
	}	

protected:
	

private:

	ookMsgObserver()
	{

	}
	
	H* _handler;
	FP_OOK_MSG _handlerFunc;
	
	
};


#endif