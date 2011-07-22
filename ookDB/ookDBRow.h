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
#ifndef OOK_DB_ROW_H_
#define OOK_DB_ROW_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookUtil/ookKeyValuePair.h"
#include "ookLibs/ookUtil/ookDate.h"

using namespace std;
using namespace boost;

#ifndef kvp_bool_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, bool> > kvp_bool_ptr;
#endif

#ifndef kvp_int_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, int> > kvp_int_ptr;
#endif

#ifndef kvp_long_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, long> > kvp_long_ptr;
#endif

#ifndef kvp_float_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, float> > kvp_float_ptr;
#endif

#ifndef kvp_double_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, double> > kvp_double_ptr;
#endif

#ifndef kvp_string_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, string> > kvp_string_ptr;
#endif

#ifndef kvp_date_ptr
typedef boost::shared_ptr<ookKeyValuePair<string, ookDatePtr> > kvp_date_ptr;
#endif

class ookDBRow
{
public:
			
	ookDBRow();		
	virtual ~ookDBRow();
	
	virtual int GetColumnCount();

	virtual void AddBlankColumn(string colname="");

	virtual void AddBoolValue(bool value, string colname="");
	virtual void AddIntValue(int value, string colname="");
	virtual void AddLongValue(long value, string colname="");
	virtual void AddFloatValue(float value, string colname="");
	virtual void AddDoubleValue(double value, string colname="");
	virtual void AddTextValue(std::string value, string colname="");
	virtual void AddDateValue(ookDatePtr value, string colname="");

	virtual void SetBoolValue(int index, bool value);
	virtual void SetIntValue(int index, int value);
	virtual void SetLongValue(int index, long value);
	virtual void SetFloatValue(int index, float value);
	virtual void SetDoubleValue(int index, double value);
	virtual void SetTextValue(int index, std::string value);
	virtual void SetDateValue(int index, ookDatePtr value);

	virtual bool GetBoolValue(int index);
	virtual bool GetBoolValue(string colname);
	virtual int GetIntValue(int index);
	virtual int GetIntValue(string colname);
	virtual long GetLongValue(int index);
	virtual long GetLongValue(string colname);
	virtual float GetFloatValue(int index);
	virtual float GetFloatValue(string colname);
	virtual double GetDoubleValue(int index);
	virtual double GetDoubleValue(string colname);
	virtual string GetTextValue(int index);
	virtual string GetTextValue(string colname);
	virtual ookDatePtr GetDateValue(int index);
	virtual ookDatePtr GetDateValue(string colname);

protected:
	
	
private:

	vector<kvp_bool_ptr>_valsBool;
	vector<kvp_int_ptr> _valsInt;
	vector<kvp_long_ptr> _valsLong;
	vector<kvp_float_ptr> _valsFloat;
	vector<kvp_double_ptr> _valsDouble;
	vector<kvp_string_ptr> _valsText;
	vector<kvp_date_ptr> _valsDate;
};

#ifndef ookDBRowPtr
typedef boost::shared_ptr<ookDBRow> ookDBRowPtr;
#endif

#endif