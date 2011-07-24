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
#ifndef OOK_DB_STATEMENT_H_
#define OOK_DB_STATEMENT_H_

#include "ookLibs/ookDB/ookDB.h"
#include "ookLibs/ookDB/ookDBRowSet.h"
#include "ookLibs/ookUtil/ookDate.h"

class ookDBStatement
{
public:
	
	ookDBStatement(ookDBPtr db);		
	ookDBStatement(ookDBPtr db, string sql);	

	virtual ~ookDBStatement();
	
	/*! 
		\brief Prepares a statement for execution. This should be 
		called before setting any statement parameters. Pure virtual method 
		which must be overriden by implementing classes.
 
		\return true if successful, false otherwise.
 */
	virtual bool PrepareStatement() = 0;

	/*! 
		\brief Prepares a statement for execution. This should be 
		called before setting any statement parameters. Pure virtual method 
		which must be overriden by implementing classes.
 
		\param sql The SQL statement to be executed. 

		\return true if successful, false otherwise.
 */
	virtual bool PrepareStatement(string sql) = 0;

	/*! 
		\brief Sets a boolean value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetBoolParameter(int index, bool val) = 0;

	/*! 
		\brief Sets an int value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetIntParameter(int index, int val) = 0;

	/*! 
		\brief Sets a long value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetLongParameter(int index, long val) = 0;

	/*! 
		\brief Sets a float value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetFloatParameter(int index, float val) = 0;

	/*! 
		\brief Sets a double value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetDoubleParameter(int index, double val) = 0;

	/*! 
		\brief Sets a text value for a SQl statement parameter. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
 */
	virtual void SetTextParameter(int index, string val) = 0;

	/*! 
		\brief Sets a date value for a SQl statement parameter. Dates are 
		represented as strings with accompanying format specifiers in order 
		to permit a platform-independent implementation. Pure 
		virtual method which must be overriden by implementing classes.
 
		\param index The 0-based index for the parameter in the order as 
		it appears in the statement. 
		\param val The value being set. 
		\param datefmt The string format of the date.
 */
	virtual void SetDateParameter(int index, ookDate val) = 0;

	/*! 
		\brief Executes a database query. Pure virtual method
	 which must be overriden by implementing classes.
 
		\return An ookDBRowSet.
 */
	virtual ookDBRowSetPtr ExecuteQuery() = 0;

	/*! 
		\brief Executes a database non-query. Pure virtual method 
		which must be overriden by implementing classes.
 
		\return true if successful, false otherwise.
 */
	virtual bool ExecuteNonQuery() = 0;

	void SetDB(ookDBPtr db);
	ookDBPtr GetDB();
	void SetSQL(string sql);
	string GetSQL();

protected:
	
	
private:

	ookDBPtr _db;
	string _sql;

};



#endif