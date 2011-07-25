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
 \class ookSingleton
 \headerfile ookSingleton.h "ookLibs/ookCore/ookSingleton.h"
 \brief Implementation of the singleton pattern. Singleton objects
 are not directly instantiated. Rather, a pointer to the current 
 instance is obtained via a call to GetInstance().
 
 Derived classes will need to declare ookSingleton a friend class in 
 order for GetInstance to function correctly.
 */
#ifndef OOK_SINGLETON_H_
#define OOK_SINGLETON_H_

#include "boost/shared_ptr.hpp"

template <class T>
class ookSingleton
{
public:
	
	/*! 
	 \brief Destructor.
	 */		
	virtual ~ookSingleton(){}
	
	/*! 
	 \brief Fetches the pointer to the single instance. If the pointer
	 is null, constructs a new object.
	 
	 \return The singleton's instance.
	 */		
	static boost::shared_ptr<T> GetInstance()
	{
		if(_instance == NULL)
			_instance = boost::shared_ptr<T>(new T());
		
		return _instance;
	}
	
	
protected:
	
	/*! 
	 \brief Default constructor.
	 */	
	ookSingleton(){}
	
private:
	
	/*! 
	 \brief Copy constructor.
	 */	
	ookSingleton(const ookSingleton& cpy);
	
	/*! 
	 \brief Overloaded assignment operator.
	 */	
	virtual ookSingleton& operator= (const ookSingleton& cpy);	

	static boost::shared_ptr<T> _instance;
	
};

#endif