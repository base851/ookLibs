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
 \class ookThread
 \headerfile ookMutex.h "ookLibs/ookThread/ookThread.h"
 \brief Simple base thread class. Derived classes should override
 Run(), which is the worker function for the thread.
 */
#include "ookLibs/ookThread/ookThread.h"

ookThread::ookThread()
{
	
}

ookThread::~ookThread()
{
	try
	{
		this->Stop();
	}
	catch (...)
	{
	}	
}

void ookThread::Start()
{
	_bKeepRunning = true;
	_pThread = boost::shared_ptr<thread>(new thread(&ookThread::Run, this));
}

void ookThread::Stop()
{
	_bKeepRunning = false;
}

bool ookThread::IsRunning()
{
	return _bKeepRunning; 
}

void ookThread::Sleep(int lTimeSec)
{
	boost::xtime xt;
	boost::xtime_get(&xt, boost::TIME_UTC);
	xt.sec += lTimeSec;	
	
	_pThread->sleep(xt);
}

void ookThread::NanoSleep(long lTimeNanos)
{
	boost::xtime xt;
	boost::xtime_get(&xt, boost::TIME_UTC);
	xt.nsec += lTimeNanos;	
	
	_pThread->sleep(xt);
}

void ookThread::Run()
{
	//Do your stuff here	
	cout << "Running!" << endl;	
}