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
 \class ookDB
 \headerfile ookDB.h "ookLibs/ookDB/ookDB.h"
 \brief Abstract base class for database interface implementations.
 */
#include "ookLibs/ookDB/ookDB.h"

/*! 
 \brief Default constructor.
 */	
ookDB::ookDB()
{

}

/*! 
 \brief Initialization constructor.

 \param connstr	The database connection string.
 */
ookDB::ookDB(string connstr)
	: _connstr(connstr)
{

}

/*! 
 \brief Initialization constructor.

 \param server	The server name.
 \param schema	The schema name.
 \param username The connection username.
 \param password The connection password.
 */
ookDB::ookDB(string server, string schema, string username, string password)
	: _server(server), _schema(schema), _username(username), _password(password)
{

}

/*! 
 \brief Destructor.
 */	
ookDB::~ookDB()
{

}

/*! 
 \brief Sets the connection string.
 
 \param connstr	The connection string.
 */
void ookDB::SetConnectionString(string connstr)
{
	_connstr = connstr;
}

/*! 
 \brief Returns the connection string.
 
	\return The connection string.
 */
string ookDB::GetConnectionString()
{
	return _connstr;
}

/*! 
 \brief Sets the server name.
 
 \param server	The server name.
 */
void ookDB::SetServer(string server)
{
	_server = server;
}

/*! 
 \brief Returns the server name.
 
	\return The server name.
 */
string ookDB::GetServer()
{
	return _server;
}

/*! 
 \brief Sets the schema name.
 
 \param schema	The schema name.
 */
void ookDB::SetSchema(string schema)
{
	_schema = schema;
}

/*! 
 \brief Returns the schema name.
 
	\return The schema name.
 */
string ookDB::GetSchema()
{
	return _schema;
}

/*! 
 \brief Sets the connection user name.
 
 \param username	The connection user name.
 */
void ookDB::SetUsername(string username)
{
	_username = username;
}

/*! 
 \brief Returns the connection user name.
 
	\return The connection user name.
 */
string ookDB::GetUsername()
{
	return _username;
}

/*! 
 \brief Sets the connection password.
 
 \param password	The connection password.
 */
void ookDB::SetPassword(string password)
{
	_password = password;
}

/*! 
 \brief Returns the connection password.
 
	\return The connection password.
 */
string ookDB::GetPassword()
{
	return _password;
}