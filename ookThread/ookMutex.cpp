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
 /*! 
 \class ookMutex
 \headerfile ookMutex.h "ookLibs/ookThread/ookMutex.h"
 \brief Simple mutex class for implementing thread safety.
 */
#include "ookLibs/ookThread/ookMutex.h"

/*! 
 \brief Default constructor.
 */
ookMutex::ookMutex()
{
	
}

/*! 
 \brief Destructor.
 */
ookMutex::~ookMutex()
{
	
}

/*! 
 \brief Sets a mutex lock. If a lock already exists, this call blocks
 until the lock is obtained.
 */
void ookMutex::Lock()
{
	_mut.lock();
}

/*! 
 \brief Attempts to obtain a mutex lock. Nonblocking.

 \return	true if the lock was successfully obtained, false otherwise.
 */
bool ookMutex::TryLock()
{
	return _mut.try_lock();
}

/*! 
 \brief Releases a mutex lock.
 */
void ookMutex::Unlock()
{
	_mut.unlock();
}