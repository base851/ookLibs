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

#ifndef OOK_SQLITE_STATEMENT_H_
#define OOK_SQLITE_STATEMENT_H_

#include "ookLibs/ookCore/typedefs.h"
#include "my_global.h"
#include "mysql.h"

/*
 
 See	http://dev.mysql.com/doc/refman/5.0/en/c-api-prepared-statement-data-structures.html
			http://dev.mysql.com/doc/refman/5.0/en/mysql-stmt-execute.html
 
 Input Variable C Type 	buffer_type Value 	SQL Type of Destination Value
 signed char						MYSQL_TYPE_TINY			TINYINT
 short int							MYSQL_TYPE_SHORT		SMALLINT
 int										MYSQL_TYPE_LONG			INT
 long long int					MYSQL_TYPE_LONGLONG BIGINT
 float									MYSQL_TYPE_FLOAT		FLOAT
 double									MYSQL_TYPE_DOUBLE 	DOUBLE
 MYSQL_TIME							MYSQL_TYPE_TIME			TIME
 MYSQL_TIME							MYSQL_TYPE_DATE			DATE
 MYSQL_TIME							MYSQL_TYPE_DATETIME DATETIME
 MYSQL_TIME							MYSQL_TYPE_TIMESTAMP TIMESTAMP
 char[]									MYSQL_TYPE_STRING 	TEXT, CHAR, VARCHAR
 char[]									MYSQL_TYPE_BLOB			BLOB, BINARY, VARBINARY
												MYSQL_TYPE_NULL			NULL
 
 SQL Type of Received Value 	buffer_type Value			Output Variable C Type
 TINYINT											MYSQL_TYPE_TINY				signed char
 SMALLINT											MYSQL_TYPE_SHORT			short int
 MEDIUMINT										MYSQL_TYPE_INT24			int
 INT													MYSQL_TYPE_LONG				int
 BIGINT												MYSQL_TYPE_LONGLONG		long long int
 FLOAT												MYSQL_TYPE_FLOAT			float
 DOUBLE												MYSQL_TYPE_DOUBLE			double
 DECIMAL											MYSQL_TYPE_NEWDECIMAL char[]
 YEAR													MYSQL_TYPE_SHORT			short int
 TIME													MYSQL_TYPE_TIME				MYSQL_TIME
 DATE													MYSQL_TYPE_DATE				MYSQL_TIME
 DATETIME											MYSQL_TYPE_DATETIME 	MYSQL_TIME
 TIMESTAMP										MYSQL_TYPE_TIMESTAMP 	MYSQL_TIME
 CHAR, BINARY									MYSQL_TYPE_STRING			char[]
 VARCHAR, VARBINARY						MYSQL_TYPE_VAR_STRING char[]
 TINYBLOB, TINYTEXT						MYSQL_TYPE_TINY_BLOB 	char[]
 BLOB, TEXT										MYSQL_TYPE_BLOB				char[]
 MEDIUMBLOB, MEDIUMTEXT				MYSQL_TYPE_MEDIUM_BLOB char[]
 LONGBLOB, LONGTEXT						MYSQL_TYPE_LONG_BLOB 	char[]
 BIT													MYSQL_TYPE_BIT				char[] 
 
 The MYSQL_TIME structure contains the members listed in the following table.
 Member											Description
 unsigned int year					The year
 unsigned int month					The month of the year
 unsigned int day						The day of the month
 unsigned int hour					The hour of the day
 unsigned int minute				The minute of the hour
 unsigned int second				The second of the minute
 my_bool neg								A boolean flag indicating whether the time is negative
 unsigned long second_part 	The fractional part of the second in microseconds; currently unused
 
 */

class ookMySQLBindParam
{
public:
	
	ookMySQLBindParam() {}
	
	virtual ~ookMySQLBindParam() {}
	
	enum_field_types _field_type;	
	
	//Different buffer value possibilities
	signed char		_buf_schar;
	short int			_buf_sint;
	int						_buf_int;
	long long int	_buf_llint;
	float					_buf_float;
	double				_buf_double;
	string				_buf_char;
	MYSQL_TIME		_buf_date;
	
	unsigned long _buffer_length;
	unsigned long _length;
	bool					_is_null;
	bool					_is_unsigned;
	bool					_error;
	
protected:	
	
private:
	
	
};

#ifndef ookMySQLBindParamPtr
typedef boost::shared_ptr<ookMySQLBindParam> ookMySQLBindParamPtr;
#endif

#endif