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
#ifndef OOK_MYSQL_STATEMENT_H_
#define OOK_MYSQL_STATEMENT_H_

#include "ookLibs/ookDB/ookDBStatement.h"
#include "ookLibs/ookDB/ookDB.h"
#include "ookLibs/ookDB/ookDBRowSet.h"
#include "ookLibs/ookDB/ookMySQLBindParam.h"
#include "my_global.h"
#include "mysql.h"

class ookMySQLStatement : public ookDBStatement
{
public:
	
	ookMySQLStatement(ookDBPtr  db);		
	ookMySQLStatement(ookDBPtr  db, string sql);	
	
	virtual ~ookMySQLStatement();
	
	virtual bool PrepareStatement();
	virtual bool PrepareStatement(string sql);
	virtual void SetBoolParameter(int index, bool val);
	virtual void SetIntParameter(int index, int val);
	virtual void SetLongParameter(int index, long val);
	virtual void SetFloatParameter(int index, float val);
	virtual void SetDoubleParameter(int index, double val);
	virtual void SetTextParameter(int index, string val);
	virtual void SetDateParameter(int index, ookDate val);
	
	virtual ookDBRowSetPtr ExecuteQuery();
	virtual bool ExecuteNonQuery();
	
protected:
	
	virtual bool MySQLBindParams();
	
private:
	
	const MYSQL*	_mysqldb;
	MYSQL_STMT*		_stmt;
	vector<ookMySQLBindParamPtr> _bindlist;
};

#ifndef ookMySQLStatementPtr
typedef boost::shared_ptr<ookMySQLStatement> ookMySQLStatementPtr;
#endif

#endif
