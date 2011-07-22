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
 \class ookDBStatement
 \headerfile ookDBStatement.h "ookLibs/ookDB/ookDBStatement.h"
 \brief Abstract base class for SQL statement (query & non-query) implementations.
 */
#include "ookLibs/ookDB/ookDBStatement.h"
#include "ookLibs/ookDB/ookDB.h"

/*! 
 \brief Initialization constructor.

 \param db	The originating database object.
 */
ookDBStatement::ookDBStatement(ookDB* db)
	: _db(db)
{
	
}

/*! 
 \brief Initialization constructor.

 \param db	The originating database object.
 \param sql The statement's SQL command.
 */
ookDBStatement::ookDBStatement(ookDB* db, string sql)
	: _db(db), _sql(sql)
{
	
}

/*! 
 \brief Destructor.
 */	
ookDBStatement::~ookDBStatement()
{
	
}

/*! 
 \brief Sets the statement's SQL command.
 
 \param sql	The statement's SQL command.
 */
void ookDBStatement::SetSQL(string sql)
{
	_sql = sql;
}

/*! 
 \brief Returns the statement's SQL command.
 
	\return The statement's SQL command.
 */
string ookDBStatement::GetSQL()
{
	return _sql;
}

/*! 
 \brief Sets the originating database object.
 
 \param db The originating database object.
 */
void ookDBStatement::SetDB(ookDB*  db)
{
	_db = db;
}

/*! 
 \brief Returns the originating database object.
 
	\return The originating database object.
 */
ookDB* ookDBStatement::GetDB()
{
	return _db;
}