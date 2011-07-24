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
 \class ookDBRow
 \headerfile ookDBRow.h "ookLibs/ookDB/ookDBRow.h"
 \brief Platform-independent representation of a database row. A collection 
 of these rows constitutes an ookDBRowSet. When a row is constructed, each column
 is pushed on sequentially and by type. When no column name is provided, columns are 
 named in a "COL" + index convention. Column values may be retrieved by either 
 specifying the column name or index.

 */
#include "ookLibs/ookDB/ookDBRow.h"
#include "ookLibs/ookCore/ookException.h"

/*! 
 \brief Default constructor.
 */	
ookDBRow::ookDBRow()
{
	
}

/*! 
 \brief Destructor.
 */	
ookDBRow::~ookDBRow()
{
	
}

/*! 
 \brief Returns the number of columns in the row.
 
	\return The column count.
 */
int ookDBRow::GetColumnCount()
{
	return _valsBool.size();
}

void ookDBRow::AddBlankColumn(string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());

	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));	
}
/*! 
 \brief Pushes a new column onto the row as a boolean value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddBoolValue(bool value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());

	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, value)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));	
}

/*! 
 \brief Pushes a new column onto the row as an int value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddIntValue(int value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());	

	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, value)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));	
}

/*! 
 \brief Pushes a new column onto the row as a long value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddLongValue(long value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());	
	
	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, value)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));			
}

/*! 
 \brief Pushes a new column onto the row as a float value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddFloatValue(float value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());	
	
	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, value)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));				
}

/*! 
 \brief Pushes a new column onto the row as a double value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddDoubleValue(double value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());	
	
	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, value)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));	
}

/*! 
 \brief Pushes a new column onto the row as a text value.
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddTextValue(string value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());
	
	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, value)));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, ookDatePtr(new ookDate()))));		
}

/*! 
 \brief Pushes a new column onto the row as a date value. 
 
 \param value	The column's value.
 \param colname	The column's name. (optional)
 */
void ookDBRow::AddDateValue(ookDatePtr value, string colname)
{
	if(colname == "")
		colname = ("COL" + _valsBool.size());
	
	_valsBool.push_back(kvp_bool_ptr(new ookKeyValuePair<string, bool>(colname, false)));
	_valsInt.push_back(kvp_int_ptr(new ookKeyValuePair<string, int>(colname, 0)));
	_valsLong.push_back(kvp_long_ptr(new ookKeyValuePair<string, long>(colname, 0)));
	_valsFloat.push_back(kvp_float_ptr(new ookKeyValuePair<string, float>(colname, 0)));
	_valsDouble.push_back(kvp_double_ptr(new ookKeyValuePair<string, double>(colname, 0)));
	_valsText.push_back(kvp_string_ptr(new ookKeyValuePair<string, string>(colname, "")));
	_valsDate.push_back(kvp_date_ptr(new ookKeyValuePair<string, ookDatePtr>(colname, value)));		
}


/*! 
 \brief Sets a column's boolean value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetBoolValue(int index, bool value)
{
	if(_valsBool.size() >= (index + 1))
		_valsBool[index]->SetValue(value);
}

/*! 
 \brief Sets a column's int value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetIntValue(int index, int value)
{
	if(_valsInt.size() >= (index + 1))
		_valsInt[index]->SetValue(value);
}

/*! 
 \brief Sets a column's long value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetLongValue(int index, long value)
{
	if(_valsLong.size() >= (index + 1))
		_valsLong[index]->SetValue(value);
}

/*! 
 \brief Sets a column's float value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetFloatValue(int index, float value)
{
	if(_valsFloat.size() >= (index + 1))
		_valsFloat[index]->SetValue(value);
}

/*! 
 \brief Sets a column's double value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetDoubleValue(int index, double value)
{
	if(_valsDouble.size() >= (index + 1))
		_valsDouble[index]->SetValue(value);
}

/*! 
 \brief Sets a column's string value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetTextValue(int index, std::string value)
{
	if(_valsText.size() >= (index + 1))
		_valsText[index]->SetValue(value);
}

/*! 
 \brief Sets a column's date value.
 
 \param index	The column's 0-based index.
 \param value	The column's value.
 */
void ookDBRow::SetDateValue(int index, ookDatePtr value)
{
	if(_valsDate.size() >= (index + 1))
		_valsDate[index]->SetValue(value);
}

/*! 
	\brief Returns the value of a boolean column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
bool ookDBRow::GetBoolValue(int index)
{
	for(int i=0; i < _valsBool.size(); i++)
	{
		if(i == index)
			if(_valsBool[i] != NULL)
				return _valsBool[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);
}

/*! 
	\brief Returns the value of a boolean column.
 
	\param colname The column name. 

	\return The column's value.
*/
bool ookDBRow::GetBoolValue(string colname)
{
	for(int i=0; i < _valsBool.size(); i++)
	{
		if(_valsBool[i] != NULL)
			if(_valsBool[i]->GetKey() == colname)
				return _valsBool[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");	
}

/*! 
	\brief Returns the value of an int column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
int ookDBRow::GetIntValue(int index)
{
	for(int i=0; i < _valsInt.size(); i++)
	{
		if(i == index)
			if(_valsInt[i] != NULL)
				return _valsInt[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of an int column.
 
	\param colname The column name. 

	\return The column's value.
*/
int ookDBRow::GetIntValue(string colname)
{
	for(int i=0; i < _valsInt.size(); i++)
	{
		if(_valsInt[i] != NULL)
			if(_valsInt[i]->GetKey() == colname)
				return _valsInt[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");		
}

/*! 
	\brief Returns the value of a long column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
long ookDBRow::GetLongValue(int index)
{
	for(int i=0; i < _valsLong.size(); i++)
	{
		if(i == index)
			if(_valsLong[i] != NULL)
				return _valsLong[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of a long column.
 
	\param colname The column name. 

	\return The column's value.
*/
long ookDBRow::GetLongValue(string colname)
{
	for(int i=0; i < _valsLong.size(); i++)
	{
		if(_valsLong[i] != NULL)
			if(_valsLong[i]->GetKey() == colname)
				return _valsLong[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");		
}

/*! 
	\brief Returns the value of a float column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
float ookDBRow::GetFloatValue(int index)
{
	for(int i=0; i < _valsFloat.size(); i++)
	{
		if(i == index)
			if(_valsFloat[i] != NULL)
				return _valsFloat[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of a float column.
 
	\param colname The column name. 

	\return The column's value.
*/
float ookDBRow::GetFloatValue(string colname)
{
	for(int i=0; i < _valsFloat.size(); i++)
	{
		if(_valsFloat[i] != NULL)
			if(_valsFloat[i]->GetKey() == colname)
				return _valsFloat[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");		
}

/*! 
	\brief Returns the value of a double column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
double ookDBRow::GetDoubleValue(int index)
{
	for(int i=0; i < _valsDouble.size(); i++)
	{
		if(i == index)
			if(_valsDouble[i] != NULL)
				return _valsDouble[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of a double column.
 
	\param colname The column name. 

	\return The column's value.
*/
double ookDBRow::GetDoubleValue(string colname)
{
	for(int i=0; i < _valsDouble.size(); i++)
	{
		if(_valsDouble[i] != NULL)
			if(_valsDouble[i]->GetKey() == colname)
				return _valsDouble[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");		
}

/*! 
	\brief Returns the value of a text column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
string ookDBRow::GetTextValue(int index)
{
	for(int i=0; i < _valsText.size(); i++)
	{
		if(i == index)
			if(_valsText[i] != NULL)
				return _valsText[i]->GetValue();
	}	
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of a text column.
 
	\param colname The column name. 

	\return The column's value.
*/
string ookDBRow::GetTextValue(string colname)
{
	for(int i=0; i < _valsText.size(); i++)
	{
		if(_valsText[i] != NULL)
			if(_valsText[i]->GetKey() == colname)
				return _valsText[i]->GetValue();
	}	
	
	throw ookException("No value exists for column ");		
}

/*! 
	\brief Returns the value of a date column.
 
	\param index The 0-based index for the column. 

	\return The column's value.
*/
ookDatePtr ookDBRow::GetDateValue(int index)
{
	for(int i=0; i < _valsDate.size(); i++)
	{
		if(i == index)
			if(_valsDate[i] != NULL)
				return _valsDate[i]->GetValue();
	}
	
	throw ookException("No value exists at column index " + index);	
}

/*! 
	\brief Returns the value of a date column.
 
	\param colname The column name. 

	\return The column's value.
*/
ookDatePtr ookDBRow::GetDateValue(string colname)
{
	for(int i=0; i < _valsDate.size(); i++)
	{
		if(_valsDate[i] != NULL)
			if(_valsDate[i]->GetKey() == colname)
				return _valsDate[i]->GetValue();
	}		
	
	throw ookException("No value exists for column ");		
}