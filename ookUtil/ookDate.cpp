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

/**
 \class ookDate
 \headerfile ookDate.h "ookLibs/ookUtil/ookDate.h"
 \brief Basic class for storage of date and time information.
 */

#include "ookLibs/ookUtil/ookDate.h"

/*! 
 \brief Default constructor. Sets the date to the current local time.
*/
ookDate::ookDate()
{
	_date = boost::posix_time::microsec_clock::local_time();
}

/*!
\brief Initialization constructor. Sets the date and time based upon 
the contents of the string passed in. The date string must be in the 
format of "YYYY-MM-DD HH24:MI:SS.MCS". For example...

\code
ookDate date("2002-01-20 23:59:59.000");
\endcode

\param date The date string in YYYY-MM-DD HH24:MI:SS.MCS format.
*/
ookDate::ookDate(string date)
{
	_date = boost::posix_time::time_from_string(date);
}

/*! 
 \brief Destructor.
*/
ookDate::~ookDate()
{

}

/*!
\brief Indicates whether a date is or is not valid.

\return true if the date is valid, false otherwise.
*/
bool ookDate::IsValidDate()
{
	return !_date.is_not_a_date_time();
}

/*!
\brief Returns the date and time in the format of 
"YYYY-MM-DD HH24:MI:SS.MCS".

\return The date and time in string format.
*/
string ookDate::GetDateString()
{
	return boost::posix_time::to_simple_string(_date);
}

/*!
\brief Sets the date and time based upon 
the contents of the string passed in. The date string must be in the 
format of "YYYY-MM-DD HH24:MI:SS.MCS". For example...

\code
ookDate date("2002-01-20 23:59:59.000");
\endcode

\param date The date string in YYYY-MM-DD HH24:MI:SS.MCS format.
*/
void ookDate::SetDate(string date)
{
	_date = boost::posix_time::time_from_string(date);
}

/*!
\brief Returns the year component of the date.

\return The year component of the date.
*/
long ookDate::GetYear()
{
	return _date.date().year();
}

/*!
\brief Sets the year component of the date.

\param year The year component of the date.
*/
void ookDate::SetYear(long year)
{
	string strDate = year + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the month component of the date.

\return The month component of the date.
*/
long ookDate::GetMonth()
{
	return _date.date().month();
}

/*!
\brief Sets the month component of the date.

\param month The month component of the date.
*/
void ookDate::SetMonth(long month)
{
	string strDate = this->GetYear() + "-";
				 strDate += month + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the day component of the date.

\return The day component of the date.
*/
long ookDate::GetDay()
{
	return _date.date().day();
}

/*!
\brief Sets the day component of the date.

\param day The day component of the date.
*/
void ookDate::SetDay(long day)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += day + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the hour component of the date.

\return The hour component of the date.
*/
long ookDate::GetHour()
{
	return _date.time_of_day().hours();
}

/*!
\brief Sets the hour component of the date.

\param hour The hour component of the date.
*/
void ookDate::SetHour(long hour)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += hour + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the minute component of the date.

\return The minute component of the date.
*/
long ookDate::GetMinute()
{
	return _date.time_of_day().minutes();
}

/*!
\brief Sets the minute component of the date.

\param minute The minute component of the date.
*/
void ookDate::SetMinute(long minute)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += minute + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the second component of the date.

\return The second component of the date.
*/
long ookDate::GetSecond()
{
	return _date.time_of_day().seconds();
}

/*!
\brief Sets the second component of the date.

\param second The second component of the date.
*/
void ookDate::SetSecond(long second)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += second + ".";
				 strDate += this->GetMicrosecond();

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the millisecond component of the date.

\return The millisecond component of the date.
*/
long ookDate::GetMillisecond()
{
	return _date.time_of_day().total_milliseconds();
}

/*!
\brief Sets the millisecond component of the date.

\param millisecond The millisecond component of the date.
*/
void ookDate::SetMillisecond(long millisecond)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += millisecond * 1000000;

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the nanosecond component of the date.

\return The nanosecond component of the date.
*/
long ookDate::GetNanosecond()
{
	return _date.time_of_day().total_nanoseconds();
}

/*!
\brief Sets the nanosecond component of the date.

\param nanosecond The nanosecond component of the date.
*/
void ookDate::SetNanosecond(long nanosecond)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += nanosecond * 1000;

	_date = boost::posix_time::time_from_string(strDate);
}

/*!
\brief Returns the microsecond component of the date.

\return The microsecond component of the date.
*/
long ookDate::GetMicrosecond()
{
	return _date.time_of_day().total_microseconds();
}

/*!
\brief Sets the microsecond component of the date.

\param year The microsecond component of the date.
*/
void ookDate::SetMicrosecond(long microsecond)
{
	string strDate = this->GetYear() + "-";
				 strDate += this->GetMonth() + "-";
				 strDate += this->GetDay() + " ";
				 strDate += this->GetHour() + ":";
				 strDate += this->GetMinute() + ":";
				 strDate += this->GetSecond() + ".";
				 strDate += microsecond;

	_date = boost::posix_time::time_from_string(strDate);
}