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
 \class ookMySQLDB
 \headerfile ookMySQLDB.h "ookLibs/ookDB/ookMySQLDB.h"
 \brief Handles MySQL database connections.
 */
#include "ookLibs/ookDB/ookMySQLDB.h"
#include "ookLibs/ookDB/ookMySQLStatement.h"

/*! 
 \brief Default constructor.
 */
	ookMySQLDB::ookMySQLDB()
		
	{

	}

/*! 
 \brief Initialization constructor.

 \param server	The server name.
 \param schema	The schema name.
 \param username The connection username.
 \param password The connection password.
 */
	ookMySQLDB::ookMySQLDB(string server, string schema, string username, string password)
		: ::ookDB(server, schema, username, password)
	{

	}

/*! 
 \brief Destructor.
 */
	ookMySQLDB::~ookMySQLDB()
	{

	}

/*! 
		\brief Returns the MYSQL object. Called by ookMySQLStatement
		to obtain the database-specific object necessary to perform
		its work.
 
		\return A MYSQL object.
*/
	const MYSQL* ookMySQLDB::GetMySQLObj()
	{
		return _mysqldb;
	}

/*
 Test database instance is mysqld@localhost. Test schema is ookTest. Test table is TestTable1. Cols are
 INT_COL, VARCHAR_COL, DECIMAL_COL, DATETIME_COL, BINARY_COL, TIMESTAMP_COL, BOOL_COL, DOUBLE_COL.
 */
/*! 
		\brief Establishes a database connection.
 
		\return true if successful, false otherwise.
*/
 bool ookMySQLDB::Connect()
{
	try
	{
		//Initialise the MySQL instance
    _mysqldb=mysql_init(NULL); 
    if(!_mysqldb)
        return false;

    //Connect to the database
    _mysqldb=mysql_real_connect(_mysqldb,
																this->GetServer().data(), this->GetUsername().data(), 
																this->GetPassword().data(), this->GetSchema().data(),
																0, NULL, 0);

		//Quick test to make sure we're connected
		if(mysql_ping(_mysqldb) == 0)
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
bool ookMySQLDB::Disconnect()
{
	try
	{
		mysql_close(_mysqldb);

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
ookDBRowSetPtr ookMySQLDB::ExecuteQuery(string sql)
{
	ookMySQLStatement stmt(this, sql);
	return this->ExecuteQuery(&stmt);
//	return this->ExecuteQuery(ookMySQLStatementPtr(new ookMySQLStatement(ookMySQLDBPtr(this), sql)));
}

/*! 
		\brief Executes a database query.

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized query. 
 
		\return An ookDBRowSet.
*/
ookDBRowSetPtr ookMySQLDB::ExecuteQuery(ookDBStatement* stmt)
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
bool ookMySQLDB::ExecuteStatement(string sql)
{
	ookMySQLStatement stmt(this, sql);
	return this->ExecuteStatement(&stmt);	
//	return this->ExecuteQuery(ookMySQLStatementPtr(new ookMySQLStatement(ookMySQLDBPtr(this), sql)));
}

/*! 
		\brief Executes a database statement (i.e. any statement which does not return a
		rowset).

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized statement. 
 
		\return true if successful, false otherwise.
*/
bool ookMySQLDB::ExecuteStatement(ookDBStatement* stmt)
{
	stmt->PrepareStatement();	
	return stmt->ExecuteNonQuery();
}