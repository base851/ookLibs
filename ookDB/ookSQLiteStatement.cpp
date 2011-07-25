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
 \class ookSQLiteStatement
 \headerfile ookSQLiteStatement.h "ookLibs/ookDB/ookSQLiteStatement.h"
 \brief Implementation of ookDBStatement for SQLite databases.
 */

#include "ookLibs/ookDB/ookSQLiteStatement.h"
#include "ookLibs/ookDB/ookSQLiteDB.h"

/*! 
 \brief Initialization constructor.
 
 \param db	The originating database object.
 */
ookSQLiteStatement::ookSQLiteStatement(ookDBPtr  db)
: ::ookDBStatement(db)
{
	_sqlitedb = ((ookSQLiteDB*) db.get())->GetSQLiteObj();	
}

/*! 
 \brief Initialization constructor.
 
 \param db	The originating database object.
 \param sql The statements SQL command.
 */
ookSQLiteStatement::ookSQLiteStatement(ookDBPtr  db, string sql)
: ::ookDBStatement(db, sql)
{
	_sqlitedb = ((ookSQLiteDB*) db.get())->GetSQLiteObj();	
}

/*! 
 \brief Copy constructor.
 */
ookSQLiteStatement::ookSQLiteStatement(const ookSQLiteStatement& cpy)
: ::ookDBStatement(cpy._db, cpy._sql)
{
	_sqlitedb = cpy._sqlitedb;
	_stmt = cpy._stmt;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookSQLiteStatement& ookSQLiteStatement::operator= (const ookSQLiteStatement &cpy)
{
	if (&cpy != this)
	{
		_db = cpy._db;
		_sql = cpy._sql;
		_sqlitedb = cpy._sqlitedb;
		_stmt = cpy._stmt;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */	
ookSQLiteStatement::~ookSQLiteStatement()
{
	
}

/*! 
 \brief Prepares a statement for execution. This should be 
 called before setting any statement parameters.
 
 \return true if successful, false otherwise.
 */
bool ookSQLiteStatement::PrepareStatement()
{
	int ret = sqlite3_prepare((sqlite3*)_sqlitedb, this->GetSQL().data(), 0, &_stmt, NULL);
	
	if(ret == SQLITE_OK)
		return true;
	
	return false;
}

/*! 
 \brief Prepares a statement for execution. This should be 
 called before setting any statement parameters.
 
 \param sql The SQL statement to be executed. 
 
 \return true if successful, false otherwise.
 */
bool ookSQLiteStatement::PrepareStatement(string sql)
{
	this->SetSQL(sql);
	return this->PrepareStatement();	
}

/*! 
 \brief Sets a boolean value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetBoolParameter(int index, bool val)
{
	sqlite3_bind_int(_stmt, (index + 1), (val ? 1 : 0));
}

/*! 
 \brief Sets an int value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetIntParameter(int index, int val)
{
	sqlite3_bind_int(_stmt, (index + 1), val);
}

/*! 
 \brief Sets a long value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetLongParameter(int index, long val)
{
	sqlite3_bind_int64(_stmt, (index + 1), val);
}

/*! 
 \brief Sets a float value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetFloatParameter(int index, float val)
{
	sqlite3_bind_double(_stmt, (index + 1), val);
}

/*! 
 \brief Sets a double value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetDoubleParameter(int index, double val)
{
	sqlite3_bind_double(_stmt, (index + 1), val);
}

/*! 
 \brief Sets a text value for a SQl statement parameter.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 */
void ookSQLiteStatement::SetTextParameter(int index, string val)
{
	sqlite3_bind_text(_stmt, (index + 1), val.data(), -1, NULL);
}

/*! 
 \brief Sets a date value for a SQl statement parameter. Dates are 
 represented as strings with accompanying format specifiers in order 
 to permit a platform-independent implementation.
 
 \param index The 0-based index for the parameter in the order as 
 it appears in the statement. 
 \param val The value being set. 
 \param datefmt The string format of the date.
 */
void ookSQLiteStatement::SetDateParameter(int index, ookDate val)
{
	sqlite3_bind_text(_stmt, (index + 1), val.GetDateString().data(), -1, NULL);
}

/*! 
 \brief Executes a database query.
 
 \return An ookDBRowSet.
 */
ookDBRowSetPtr ookSQLiteStatement::ExecuteQuery()
{
	ookDBRowSetPtr results(new ookDBRowSet());	
	
	int irow = 0;
	while(sqlite3_step(_stmt) == SQLITE_ROW)
	{
		//Push a blank row onto the result set
		results->AddBlankRow();

		for(int i = 0; i < sqlite3_column_count(_stmt); i++)
		{
			results->GetRow(irow)->AddBlankColumn(sqlite3_column_name(_stmt, i));

			switch(sqlite3_column_type(_stmt, i))
			{
				case SQLITE_INTEGER:
					results->GetRow(irow)->SetIntValue(i, sqlite3_column_int(_stmt, i));
					results->GetRow(irow)->SetLongValue(i, sqlite3_column_int(_stmt, i));
					break;
				case SQLITE_FLOAT:
					results->GetRow(irow)->SetFloatValue(i, sqlite3_column_double(_stmt, i));
					results->GetRow(irow)->SetDoubleValue(i, sqlite3_column_double(_stmt, i));
					break;
				case SQLITE_BLOB:
					break;
				case SQLITE_NULL:
					break;
				case SQLITE_TEXT:
					{
						string text = (char*)sqlite3_column_text(_stmt, i);
						results->GetRow(irow)->SetTextValue(i, text);
						ookDatePtr date(new ookDate(text));
						if(date->IsValidDate()) 
							results->GetRow(irow)->SetDateValue(i, date);
					}
					break;
				default: break;
			}
		}

		irow++;
	}

	return results;
}

/*! 
 \brief Executes a database non-query.
 
 \return true if successful, false otherwise.
 */
bool ookSQLiteStatement::ExecuteNonQuery()
{
	if(sqlite3_step(_stmt) == SQLITE_DONE)
		return true;

	return false;
}
