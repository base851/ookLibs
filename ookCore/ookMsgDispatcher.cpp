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
// This class is a derived work from the Poco Notifier framework.
////////////////////////////////////////////////////////////////

/*! 
 \class ookMsgDispatcher
 \headerfile ookMsgDispatcher.h "ookLibs/ookCore/ookMsgDispatcher.h"
 \brief Manages ookMessagObservers and forwards any messages which they
 register an interest in.
 */
#include "ookLibs/ookCore/ookMsgDispatcher.h"

/*! 
 \brief Default constructor.
 */
ookMsgDispatcher::ookMsgDispatcher()
{
	
}

/*! 
 \brief Destructor.
 */
ookMsgDispatcher::~ookMsgDispatcher()
{
	
}

/*! 
 \brief Adds a new observer to the list of observers.
 
 \param obs	The observer to be added to the list of observers.
 
 */
void ookMsgDispatcher::RegisterObserver(ookMsgObserverAbs* obs)
{
	_vObservers.push_back(obs);
}

/*! 
 \brief Relays a message to those observers which have registered 
 an interest in that message type. 
 
 \param msg	The message to be relayed to its observers.
 
 */
void ookMsgDispatcher::PostMsg(ookMessage* msg)
{
	for(int i = 0; i < _vObservers.size(); i++)
	{
		if(_vObservers[i]->Accepts(msg))
		{
			_vObservers[i]->SendMessage(msg);
		}		
	}
}