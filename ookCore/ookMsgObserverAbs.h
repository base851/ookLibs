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
// This class is a derived work of the Poco Notifier framework.
////////////////////////////////////////////////////////////////

/*! 
 \class ookMsgObserverAbs
 \headerfile ookMsgObserverAbs.h "ookLibs/ookCore/ookMsgObserverAbs.h"
 \brief Abstract base class for message observers.
 */
#ifndef OOK_MESSAGE_OBSERVER_ABS_H_
#define OOK_MESSAGE_OBSERVER_ABS_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCore/ookMessage.h"
#include "boost/shared_ptr.hpp"

class ookMsgObserverAbs
{
public:
	
	/*! 
	 \brief Default constructor.
	 */
	ookMsgObserverAbs() {}
	
	/*! 
	 \brief Destructor.
	 */
	virtual ~ookMsgObserverAbs(){}
	
	/*! 
	 \brief Copy constructor.
	 */
	ookMsgObserverAbs(const ookMsgObserverAbs& cpy){}
	
	/*! 
	 \brief Overloaded assignment operator.
	 */
	virtual ookMsgObserverAbs& operator= (const ookMsgObserverAbs& observer){}
	
	/*! 
	 \brief Receives a message from the message dispatcher. Pure virtual method
	 which must be overriden by implementing classes.
	 
	 \param pNf The message to be handled.
	 */	
	virtual void SendMessage(ookMessagePtr pNf) = 0;
	
	/*! 
	 \brief Informs the message dispatcher whether the observer
	 accepts a particular message or not. Pure virtual method
	 which must be overriden by implementing classes.
	 
	 \param observer The message to be accepted.
	 
	 \return True if the observer accepts the message type, false if not.
	 */	
	virtual bool Accepts(ookMessagePtr pNf) = 0;
	
	
protected:
	
private:
	
};

#ifndef ookMsgObserverAbsPtr
typedef boost::shared_ptr<ookMsgObserverAbs> ookMsgObserverAbsPtr;
#endif

#endif