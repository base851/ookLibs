/*
 Copyright (C) 2011, Ted Biggs
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
/*! 
 \class ookMsgObserver
 \headerfile ookMsgObserver.h "ookLibs/ookCore/ookMsgObserver.h"
 \brief Message observer implementation.
 
 The message observer is the intermediary between the dispatcher
 and the handler. The observer's job is to determine for a handler
 whether a given message is one which the handler would be interested in, 
 and if so, invoke the callback which the handler registered to it. The 
 handler will generally create an observer for each message type that it 
 is interested in. Observers are maintained by the dispatcher.
 */
#ifndef OOK_MESSAGE_OBSERVER_H_
#define OOK_MESSAGE_OBSERVER_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookMsgObserverAbs.h"
#include "ookLibs/ookCore/ookMessage.h"
#include "boost/shared_ptr.hpp"

template <class H, class M>
class ookMsgObserver : public ookMsgObserverAbs
{
	
#ifndef FP_OOK_MSG
//	typedef void (H::*FP_OOK_MSG)(M*);
	typedef void (H::*FP_OOK_MSG)(boost::shared_ptr<M>);
#endif		
	
public:
	
	/*! 
	 \brief Initialization constructor.
	 */
	ookMsgObserver(H* handler, FP_OOK_MSG func)
		: _handler(handler), _handlerFunc(func)
	{
		
	}
	
	/*! 
	 \brief Default constructor.
	 */
	virtual ~ookMsgObserver()
	{
		
	}

	/*! 
	 \brief Overloaded assignment operator.
	 */
	ookMsgObserver& operator = (const ookMsgObserver& observer)
	{
		if (&observer != this)
		{
			_handler = observer._handler;
			_handlerFunc  = observer._handlerFunc;
		}
		return *this;
	}	
	
	/*! 
	 \brief Receives a message from the message dispatcher and
	 invokes the registered handler's callback.
	 
	 \param pNf The message to be handled.
	 */		
	void SendMessage(ookMessagePtr msg)
	{
/*		
		M* pCastNf = dynamic_cast<M*>(msg.get());
		if (pCastNf)
		{	
			(_handler->*_handlerFunc)(pCastNf);
		}
*/
		boost::shared_ptr<M> pCastNf = boost::dynamic_pointer_cast<M>(msg);
		if (pCastNf)
		{	
			(_handler->*_handlerFunc)(pCastNf);
		}
	}
	
	/*! 
	 \brief Informs the message dispatcher whether the observer
	 accepts a particular message or not. Pure virtual method
	 which must be overriden by implementing classes.
	 
	 \param observer The message to be accepted.
	 
	 \return True if the observer accepts the message type, false if not.
	 */		
	bool Accepts(ookMessagePtr msg) 
	{
//		return dynamic_cast<M*>(msg.get()) != 0;
		return boost::dynamic_pointer_cast<M>(msg) != 0;
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