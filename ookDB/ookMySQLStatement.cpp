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
 \class ookMySQLStatement
 \headerfile ookMySQLStatement.h "ookLibs/ookDB/ookMySQLStatement.h"
 \brief Implementation of ookDBStatement for MySQL databases.
 */

#include "ookLibs/ookDB/ookMySQLStatement.h"
#include "ookLibs/ookDB/ookMySQLDB.h"

/*! 
 \brief Initialization constructor.
 
 \param db	The originating database object.
 */
ookMySQLStatement::ookMySQLStatement(ookDBPtr  db)
: ::ookDBStatement(db)
{
		_mysqldb = ((ookMySQLDB*) db.get())->GetMySQLObj();
}

/*! 
 \brief Initialization constructor.
 
 \param db	The originating database object.
 \param sql The statements SQL command.
 */
ookMySQLStatement::ookMySQLStatement(ookDBPtr  db, string sql)
: ::ookDBStatement(db, sql)
{
		_mysqldb = ((ookMySQLDB*) db.get())->GetMySQLObj();	
}

/**
 \brief Destructor.
 */	
ookMySQLStatement::~ookMySQLStatement()
{
	
}

/**
 \brief Prepares a statement for execution. This should be 
 called before setting any statement parameters.
 
 \return true if successful, false otherwise.
 */
bool ookMySQLStatement::PrepareStatement()
{
		_stmt = mysql_stmt_init((MYSQL*) _mysqldb);
		
		if(_stmt == NULL)
			return false;
	
		int ret = mysql_stmt_prepare(_stmt, this->GetSQL().data(), this->GetSQL().length());
		
		if(ret == 0)
			return true;
	
	return false;
}

/** 
 \brief Prepares a statement for execution. This should be 
 called before setting any statement parameters.
 
 \param sql The SQL statement to be executed. 
 
 \return true if successful, false otherwise.
 */
bool ookMySQLStatement::PrepareStatement(string sql)
{
	this->SetSQL(sql);
	return this->PrepareStatement();
}



/**
 \brief Sets a boolean value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetBoolParameter(int index, bool val)
{	
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());
	
	bind->_field_type = MYSQL_TYPE_LONG;
	bind->_buf_int = (val ? 1 : 0);
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = ((val == NULL) ? true : false);
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);
}

/**
 \brief Sets an int value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetIntParameter(int index, int val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	bind->_field_type = MYSQL_TYPE_LONG;
	bind->_buf_int = val;
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = ((val == NULL) ? true : false);
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);	
}

/** 
 \brief Sets a long value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetLongParameter(int index, long val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	bind->_field_type = MYSQL_TYPE_LONGLONG;
	bind->_buf_llint = val;
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = ((val == NULL) ? true : false);
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);		
}

/** 
 \brief Sets a float value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetFloatParameter(int index, float val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	bind->_field_type = MYSQL_TYPE_FLOAT;
	bind->_buf_float = val;
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = ((val == NULL) ? true : false);
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);		
}

/** 
 \brief Sets a double value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetDoubleParameter(int index, double val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	bind->_field_type = MYSQL_TYPE_DOUBLE;
	bind->_buf_double = val;
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = ((val == NULL) ? true : false);
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);		
}

/**
 \brief Sets a text value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookMySQLStatement::SetTextParameter(int index, string val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	boost::shared_ptr<char> ptr(new char[val.length()]);

	bind->_field_type = MYSQL_TYPE_DOUBLE;
	bind->_buf_char = ptr.get();
	bind->_buffer_length = val.length();
	bind->_length = val.length();
	bind->_is_null = false;
	bind->_is_unsigned = false;
	bind->_error = false;
	
	_bindlist.push_back(bind);	
}

/**
 \brief Sets a date value for a SQl statement parameter. Dates are 
 represented as strings with accompanying format specifiers in order 
 to permit a platform-independent implementation.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 \param datefmt The string format of the date.
 */
void ookMySQLStatement::SetDateParameter(int index, ookDate val)
{
	ookMySQLBindParamPtr bind(new ookMySQLBindParam());

	bind->_field_type = MYSQL_TYPE_DATETIME;
	bind->_buf_date.year = val.GetYear();
	bind->_buf_date.month = val.GetMonth();
	bind->_buf_date.day = val.GetDay();
	bind->_buf_date.hour = val.GetHour();
	bind->_buf_date.minute = val.GetMinute();
	bind->_buf_date.second = val.GetSecond();
	bind->_buf_date.second_part = val.GetMicrosecond();
	bind->_buffer_length = 0;
	bind->_length = 0;
	bind->_is_null = false;
	bind->_is_unsigned = false;
	bind->_error = false;

	_bindlist.push_back(bind);	
}

/**
 \brief Converts our bind list into a MYSQL_BIND array and then binds it to the
 statement.
 */
bool ookMySQLStatement::MySQLBindParams()
{
	if(_bindlist.size() > 0)
	{
		boost::shared_ptr<MYSQL_BIND> bindptr(new MYSQL_BIND[_bindlist.size()]);
		memset(bindptr.get(), 0, (sizeof(MYSQL_BIND) * _bindlist.size()));

		for(int i = 0; i < _bindlist.size(); i++)
		{
			bindptr.get()[i].buffer_type = _bindlist[i]->_field_type;
			
			switch(_bindlist[i]->_field_type)
			{
				case MYSQL_TYPE_TINY: 
					break;
				case MYSQL_TYPE_SHORT: 
					break;
				case MYSQL_TYPE_LONG: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_int;
					break;
				case MYSQL_TYPE_LONGLONG: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_llint;
					break;
				case MYSQL_TYPE_FLOAT: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_float;
					break;
				case MYSQL_TYPE_DOUBLE: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_double;
					break;
				case MYSQL_TYPE_TIME: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_date;
					break;
				case MYSQL_TYPE_DATE: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_date;
					break;
				case MYSQL_TYPE_DATETIME: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_date;
					break;
				case MYSQL_TYPE_TIMESTAMP: 
					bindptr.get()[i].buffer = &_bindlist[i]->_buf_date;
					break;
				case MYSQL_TYPE_STRING: 
					bindptr.get()[i].buffer = (void*) _bindlist[i]->_buf_char.data();
					break;
				case MYSQL_TYPE_BLOB: 
					break;
				case MYSQL_TYPE_NULL: 
					break;
					
				default: break;
			}
			
			bindptr.get()[i].buffer_length = _bindlist[i]->_buffer_length;
			bindptr.get()[i].length = &_bindlist[i]->_length;
			bindptr.get()[i].is_null = (my_bool*) &_bindlist[i]->_is_null;
			bindptr.get()[i].is_unsigned = _bindlist[i]->_is_unsigned;
			bindptr.get()[i].error = (my_bool*) &_bindlist[i]->_error;
		}

		return mysql_stmt_bind_param(_stmt, bindptr.get());
	}
	
	return true;	
}

/** 
 \brief Executes a database query.
 
The type value may be one of the MYSQL_TYPE_ symbols shown in the following table. 
Type													Value Type Description 
MYSQL_TYPE_TINY								TINYINT field 
MYSQL_TYPE_SHORT							SMALLINT field 
MYSQL_TYPE_LONG								INTEGER field 
MYSQL_TYPE_INT24							MEDIUMINT field 
MYSQL_TYPE_LONGLONG						BIGINT field 
MYSQL_TYPE_DECIMAL						DECIMAL or NUMERIC field 
MYSQL_TYPE_NEWDECIMAL					Precision math DECIMAL or NUMERIC  
MYSQL_TYPE_FLOAT							FLOAT field 
MYSQL_TYPE_DOUBLE							DOUBLE or REAL field 
MYSQL_TYPE_BIT								BIT field 
MYSQL_TYPE_TIMESTAMP					TIMESTAMP field 
MYSQL_TYPE_DATE								DATE field 
MYSQL_TYPE_TIME								TIME field 
MYSQL_TYPE_DATETIME						DATETIME field 
MYSQL_TYPE_YEAR								YEAR field 
MYSQL_TYPE_STRING							CHAR or BINARY field 
MYSQL_TYPE_VAR_STRING					VARCHAR or VARBINARY field 
MYSQL_TYPE_BLOB								BLOB or TEXT field (use max_length to determine the maximum length) 
MYSQL_TYPE_SET								SET field 
MYSQL_TYPE_ENUM								ENUM field 
MYSQL_TYPE_GEOMETRY						Spatial field 
MYSQL_TYPE_NULL								NULL-type field 


 \return An ookDBRowSet.
 */
ookDBRowSetPtr ookMySQLStatement::ExecuteQuery()
{
	//Because of the way MySQL handles parameters, we have to generate
	//and bind the parameters here
	this->MySQLBindParams();
	
	//Execute the statement
	int ret = mysql_stmt_execute(_stmt);
	
	ookDBRowSetPtr results(new ookDBRowSet());	
	
	int irow = 0;

	//Fetch the result set metadata
	MYSQL_RES* rowstats = mysql_stmt_result_metadata(_stmt);	
	MYSQL_FIELD* fields = rowstats->fields;
	MYSQL_BIND bresult;
	//Fetch a row and handle it accordingly
	while(mysql_stmt_fetch(_stmt) == 0)
	{
		results->AddBlankRow();

		//iterate through the fields and fetch the data
		for(int i=0; i < rowstats->field_count; i++)
		{
			memset(&bresult, 0, sizeof(MYSQL_BIND));

			results->GetRow(irow)->AddBlankColumn(fields[i].name);
			
			mysql_stmt_fetch_column(_stmt, &bresult, i, 0);
	
			switch(fields[i].type)
			{
				case MYSQL_TYPE_TINY: 
					{
						results->GetRow(irow)->SetIntValue(i, *(int*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_SHORT: 
					{
						results->GetRow(irow)->SetIntValue(i, *(int*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_LONG: 
					{
						results->GetRow(irow)->SetIntValue(i, *(int*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_INT24:
					{
						results->GetRow(irow)->SetLongValue(i, *(long*)bresult.buffer);
					}				 
					break;
				case MYSQL_TYPE_LONGLONG: 
					{
						results->GetRow(irow)->SetLongValue(i, *(long*)bresult.buffer);
					}		
					break;
				case MYSQL_TYPE_DECIMAL: 
					{
						results->GetRow(irow)->SetDoubleValue(i, *(double*)bresult.buffer);
					}	
					break;
				case MYSQL_TYPE_NEWDECIMAL: 
					{
						results->GetRow(irow)->SetDoubleValue(i, *(double*)bresult.buffer);
					}	
					break;
				case MYSQL_TYPE_FLOAT: 
					{
						results->GetRow(irow)->SetFloatValue(i, *(float*)bresult.buffer);
					}	
					break;
				case MYSQL_TYPE_DOUBLE: 
					{
						results->GetRow(irow)->SetDoubleValue(i, *(double*)bresult.buffer);
					}	
					break;
				case MYSQL_TYPE_BIT: 
					{
						results->GetRow(irow)->SetIntValue(i, *(int*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_TIMESTAMP: 
					break;
				case MYSQL_TYPE_DATE: 
					break;
				case MYSQL_TYPE_TIME: 
					break;
				case MYSQL_TYPE_DATETIME: 
					break;
				case MYSQL_TYPE_YEAR: 
					break;
				case MYSQL_TYPE_STRING: 
					{
						results->GetRow(irow)->SetTextValue(i, (char*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_VAR_STRING: 
					{
						results->GetRow(irow)->SetTextValue(i, (char*)bresult.buffer);
					}
					break;
				case MYSQL_TYPE_BLOB: 
					break;
				case MYSQL_TYPE_SET: 
					break;
				case MYSQL_TYPE_ENUM: 
					break;
				case MYSQL_TYPE_GEOMETRY: 
					break;
				case MYSQL_TYPE_NULL: 
					break;
				default: break;
			}
		}

		irow++;
	}

	//Need to call free on this pointer
	mysql_free_result(rowstats);

	return results;
}

/**
 \brief Executes a database non-query.
 
 \return true if successful, false otherwise.
 */
bool ookMySQLStatement::ExecuteNonQuery()
{
	//Because of the way MySQL handles parameters, we have to generate
	//and bind the parameters here	
	this->MySQLBindParams();
	
	int ret = mysql_stmt_execute(_stmt);
	
	if(ret == 0)
		return true;
	
	return false;
}
