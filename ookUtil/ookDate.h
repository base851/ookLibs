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
#ifndef OOK_DATE_H_
#define OOK_DATE_H_

#include "ookLibs/ookCore/typedefs.h"
#include "boost/date_time/posix_time/posix_time.hpp"

class ookDate
{
public:

	ookDate();
	ookDate(string date);

	virtual ~ookDate();
	
	virtual bool IsValidDate();

	virtual string GetDateString();
	virtual void SetDate(string date);

	virtual long GetYear();
	virtual void SetYear(long year);

	virtual long GetMonth();
	virtual void SetMonth(long month);

	virtual long GetDay();
	virtual void SetDay(long day);

	virtual long GetHour();
	virtual void SetHour(long hour);

	virtual long GetMinute();
	virtual void SetMinute(long minute);

	virtual long GetSecond();
	virtual void SetSecond(long second);

	virtual long GetMillisecond();
	virtual void SetMillisecond(long millisecond);

	virtual long GetNanosecond();
	virtual void SetNanosecond(long nanosecond);

	virtual long GetMicrosecond();
	virtual void SetMicrosecond(long microsecond);

protected:
	
private:
	
	boost::posix_time::ptime _date;
	
};

#ifndef ookDatePtr
typedef boost::shared_ptr<ookDate> ookDatePtr;
#endif

#endif
