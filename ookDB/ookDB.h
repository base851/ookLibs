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
#ifndef OOK_DB_H_
#define OOK_DB_H_

#include "ookLibs/ookCore/typedefs.h"
//#include "ookLibs/ookDB/ookDBStatement.h"
#include "ookLibs/ookDB/ookDBRowSet.h"

class ookDBStatement;

#ifndef ookDBStatementPtr
typedef boost::shared_ptr<ookDBStatement> ookDBStatementPtr;
#endif

class ookDB
{
public:
		
	virtual ~ookDB();

	/*! 
		\brief Establishes a database connection. Pure virtual method
	 which must be overriden by implementing classes
 
		\return true if successful, false otherwise.
 */
	virtual bool Connect() = 0;

	/*! 
		\brief Closes a database connection. Pure virtual method
	 which must be overriden by implementing classes
 
		\return true if successful, false otherwise.
 */
	virtual bool Disconnect() = 0;

	/*! 
		\brief Executes a database query. Pure virtual method which must be overriden 
		by implementing classes

		\param sql The SQL query to be executed. Normally used when sending
		a non-parameterized query. 
 
		\return An ookDBRowSet.
 */
	virtual ookDBRowSetPtr ExecuteQuery(string sql) = 0;

	/*! 
		\brief Executes a database query. Pure virtual method
	 which must be overriden by implementing classes

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized query. 
 
		\return An ookDBRowSet.
 */
	virtual ookDBRowSetPtr ExecuteQuery(ookDBStatementPtr stmt) = 0;

	/*! 
		\brief Executes a database statement (i.e. any statement which does not return a
		rowset). Pure virtual method which must be overriden by implementing classes

		\param sql The SQL query to be executed. Normally used when sending
		a non-parameterized statement. 
 
		\return true if successful, false otherwise.
 */
	virtual bool ExecuteStatement(string sql) = 0;

	/*! 
		\brief Executes a database statement (i.e. any statement which does not return a
		rowset). Pure virtual method which must be overriden by implementing classes.

		\param stmt An ookDBStatement. Normally used when sending
		a parameterized statement. 
 
		\return true if successful, false otherwise.
 */
	virtual bool ExecuteStatement(ookDBStatementPtr stmt) = 0;

	void SetConnectionString(string connstr);
	string GetConnectionString();
	void SetServer(string server);
	string GetServer();
	void SetSchema(string schema);
	string GetSchema();
	void SetUsername(string username);
	string GetUsername();
	void SetPassword(string password);
	string GetPassword();

protected:
	
	ookDB();
	ookDB(string connstr);
	ookDB(string server, string schema, string username, string password);

private:

	string _connstr;
	string _server; 
	string _schema;
	string _username; 
	string _password;
	
};

#ifndef ookDBPtr
typedef boost::shared_ptr<ookDB> ookDBPtr;
#endif

#endif