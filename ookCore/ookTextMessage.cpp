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


/*! 
 \class ookTextMessage
 \headerfile ookTextMessage.h "ookLibs/ookCore/ookTextMessage.h"
 \brief Derived ookMessage which contains a simple string text
 message.
 */
#include "ookLibs/ookCore/ookTextMessage.h"

/*! 
 \brief Default constructor.
 */
ookTextMessage::ookTextMessage()
{
	
}

/*! 
 \brief Initialization constructor.
 */
ookTextMessage::ookTextMessage(string msg)
{
	_msg = msg;
}

/*! 
 \brief Copy constructor.
 */
ookTextMessage::ookTextMessage(const ookTextMessage& cpy)
{
	_msg = cpy._msg;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookTextMessage& ookTextMessage::operator= (const ookTextMessage &cpy)
{
	if (&cpy != this)
	{
		_msg = cpy._msg;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */
ookTextMessage::~ookTextMessage()
{
	
}

/*! 
 \brief Returns the text component of the message.
 
 \return The message string.
 */	
string ookTextMessage::GetMsg()
{
	return _msg;
}

/*! 
 \brief Sets the text component of the message.
 
 \param msg The message string.
 
 */	
void ookTextMessage::SetMessage(string msg)
{
	_msg = msg;
}