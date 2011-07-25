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
 \class ookDBRowSet
 \headerfile ookDBRowSet.h "ookLibs/ookDB/ookDBRowSet.h"
 \brief Platform-independent representation of a collection database rows. 
 */
#include "ookLibs/ookDB/ookDBRowSet.h"
#include "ookLibs/ookCore/ookException.h"
/*! 
 \brief Default constructor.
 */	
ookDBRowSet::ookDBRowSet()
{
	
}

/*! 
 \brief Copy constructor.
 */
ookDBRowSet::ookDBRowSet(const ookDBRowSet& cpy)
{
	_rows = cpy._rows;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookDBRowSet& ookDBRowSet::operator= (const ookDBRowSet &cpy)
{
	if (&cpy != this)
	{
		_rows = cpy._rows;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */	
ookDBRowSet::~ookDBRowSet()
{
	
}

/*! 
 \brief Pushes a blank row onto our row collection. Used mainly by
 database implementation objects when processing query results.
 */
void ookDBRowSet::AddBlankRow()
{
	_rows.push_back(ookDBRowPtr(new ookDBRow()));
}

/*! 
 \brief Pushes a new row onto our row collection.
 
 \param row	The row being added.
 */
void ookDBRowSet::AddRow(ookDBRowPtr row)
{
	_rows.push_back(row);
}

/*! 
 \brief Returns the collection of database rows.
 
	\return A vector containing individual ookDBRows.
*/
const vector<ookDBRowPtr> ookDBRowSet::GetRows()
{
	return _rows;
}

/*! 
 \brief Returns an individual row by 0-based index.
 
	\return An individual ookDBRow.
*/
ookDBRowPtr ookDBRowSet::GetRow(int index)
{
	if(_rows.size() >= (index + 1))
		return _rows[index];
	
	throw ookException("Row does not exist at index " + index);
}

/*! 
 \brief Returns the number of database rows in the collection.
 
	\return The row count.
 */
int ookDBRowSet::GetRowCount()
{
	return _rows.size();
}