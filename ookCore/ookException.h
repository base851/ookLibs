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
#ifndef OOK_EXCEPTION_H_
#define OOK_EXCEPTION_H_

/*! 
 \class ookException
 \headerfile ookException.h "ookLibs/ookCore/ookException.h"
 \brief Derived std::exception which allows one to specify the
 exception message and an optional numeric code.
 */
#include "ookLibs/ookCore/typedefs.h"

class ookException : public std::exception
{
public:
	
	/*! 
	 \brief Initialization constructor.
	 */
	ookException(const char* msg, long errcode=0)
	: _msg(msg), _errcode(errcode)
	{
		
	}
	
	/*! 
	 \brief Destructor.
	 */	
	virtual ~ookException() throw()
	{
		
	}
	
	/*! 
	 \brief Returns the error message.
	 
	 \return The error message.
	 */		
	virtual const char* what() const throw()
	{
		return _msg;
	}

	/*! 
	 \brief Returns the error code.
	 
	 \return The error code.
	 */			
	virtual long errcode() const throw()
	{
		return _errcode;
	}
	
protected:
	
private:
	
	const char* _msg;
	long _errcode;
	
};

#endif