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
 \class ookSQLiteDB
 \headerfile ookSQLiteDB.h "ookLibs/ookDB/ookSQLiteDB.h"
 \brief Handles SQLite database connections.
 */
#include "ookLibs/ookDB/ookSQLiteDB.h"
#include "ookLibs/ookDB/ookSQLiteStatement.h"

/*! 
 \brief Default constructor.
 */
ookSQLiteDB::ookSQLiteDB()
{

}

/*! 
 \brief Initialization constructor.

 \param connstr	The database connection string.
 */
ookSQLiteDB::ookSQLiteDB(string connstr)
	: ::ookDB(connstr)
{

}

/*! 
 \brief Destructor.
 */
ookSQLiteDB::~ookSQLiteDB()
{

}

/*! 
		\brief Returns the sqlite3 object. Called by ookSQLiteStatement
		to obtain the database-specific object necessary to perform
		its work.
 
		\return A sqlite3 object.
*/
const sqlite3* ookSQLiteDB::GetSQLiteObj()
{
	return _sqlitedb;
}

/*
 Test database is ookTest.sqlite. Test table is TestTable1. Cols are
 INT_COL, BOOL_COL, DOUBLE_COL, FLOAT_COL, REAL_COL, CHAR_COL,
 TEXT_COL, VARCHAR_COL, NUMERIC_COL, DATETIME_COL.
 */
/*! 
		\brief Establishes a database connection.
 
		\return true if successful, false otherwise.
*/
bool ookSQLiteDB::Connect()
{
	try
	{
		int ret = sqlite3_open(this->GetConnectionString().data(), &_sqlitedb);
		if(ret == SQLITE_OK)
			return true;

	}
	catch (std::exception& e)
	{
		std::cerr << "Something bad happened in ookSQLiteDB::Connect: " << e.what() << "\n";
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSQLiteDB::Connect()" << endl;		
	}

	return false;
}

	/*! 
		\brief Closes a database connection.
 
		\return true if successful, false otherwise.
 */
bool ookSQLiteDB::Disconnect()
{
	try
	{
		int ret = sqlite3_close(_sqlitedb);
		if(ret == SQLITE_OK)
			return true;		
	}
	catch (std::exception& e)
	{
		std::cerr << "Something bad happened in ookSQLiteDB::Disconnect: " << e.what() << "\n";
	}	
	catch(...)
	{
		std::cerr << "Oh noes! Unknown error in ookSQLiteDB::Disconnect()" << endl;		
	}

	return false;
}

/*! 
		\brief Executes a database query.

		\param sql The SQL query to be executed. Normally used when sending
		a non-parameterized query. 
 
		\return An ookDBRowSet.
*/
ookDBRowSetPtr ookSQLiteDB::ExecuteQuery(string sql)
{
	ookSQLiteStatement stmt(this, sql);
	return this->ExecuteQuery(&stmt);
//	return this->ExecuteQuery(ookSQLiteStatementPtr(new ookSQLiteStatement(ookSQLiteDBPtr(this), sql)));
}

/*! 
		\brief Executes a database query.

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized query. 
 
		\return An ookDBRowSet.
*/
ookDBRowSetPtr ookSQLiteDB::ExecuteQuery(ookDBStatement* stmt)
{
	stmt->PrepareStatement();
	return stmt->ExecuteQuery();
}

/*! 
		\brief Executes a database statement (i.e. any statement which does not return a
		rowset).

		\param sql The SQL query to be executed. Normally used when sending
		a non-parameterized statement. 
 
		\return true if successful, false otherwise.
*/
bool ookSQLiteDB::ExecuteStatement(string sql)
{
	ookSQLiteStatement stmt(this, sql);
	return this->ExecuteStatement(&stmt);	
//	return this->ExecuteStatement(ookSQLiteStatementPtr(new ookSQLiteStatement(ookSQLiteDBPtr(this), sql)));
}

/*! 
		\brief Executes a database statement (i.e. any statement which does not return a
		rowset).

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized statement. 
 
		\return true if successful, false otherwise.
*/
bool ookSQLiteDB::ExecuteStatement(ookDBStatement* stmt)
{
	stmt->PrepareStatement();	
	return stmt->ExecuteNonQuery();
}