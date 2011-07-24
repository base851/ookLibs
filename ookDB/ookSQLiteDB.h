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
#ifndef OOK_SQLITE_DB_H_
#define OOK_SQLITE_DB_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookDB/ookDB.h"
#include "sqlite3.h"

class ookSQLiteDB : public ookDB
{
public:
	
	ookSQLiteDB();
	ookSQLiteDB(string connstr);
	
	virtual ~ookSQLiteDB();
	
	virtual bool Connect();
	virtual bool Disconnect();	
	
	virtual ookDBRowSetPtr ExecuteQuery(string sql);
	virtual ookDBRowSetPtr ExecuteQuery(ookDBStatementPtr stmt);
	
	virtual bool ExecuteStatement(string sql);
	virtual bool ExecuteStatement(ookDBStatementPtr stmt);	
	
	const sqlite3* GetSQLiteObj();

protected:
	
	
private:
	
	sqlite3* _sqlitedb;

};

#ifndef ookSQLiteDBPtr
typedef boost::shared_ptr<ookSQLiteDB> ookSQLiteDBPtr;
#endif

#endif