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
 \class ookTextMsgHandler
 \headerfile ookTextMsgHandler.h "ookLibs/ookCore/ookTextMsgHandler.h"
 \brief Derived ookMessageHandler which handles an ookTextMessage.
 */
#include "ookLibs/ookCore/ookTextMsgHandler.h"

/*! 
 \brief Default constructor.
 */
ookTextMsgHandler::ookTextMsgHandler()
{
	
}

/*! 
 \brief Copy constructor.
 */
ookTextMsgHandler::ookTextMsgHandler(const ookTextMsgHandler& cpy)
{

}

/*! 
 \brief Overloaded assignment operator.
 */
ookTextMsgHandler& ookTextMsgHandler::operator= (const ookTextMsgHandler &cpy)
{
	return *this;
}

/*! 
 \brief Destructor.
 */
ookTextMsgHandler::~ookTextMsgHandler()
{
	
}

/*! 
 \brief The main method which should be overridden
 by ookMsgHandlers. This is where you would handle any message
 which has been dispatched to you.
 
 \param msg	The message to be handled.
 
 */
void ookTextMsgHandler::HandleMsg(ookTextMessagePtr msg)
{
	cout << "The message is: " << msg->GetMsg() << endl;
}