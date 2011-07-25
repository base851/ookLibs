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
#ifndef OOK_STRING_H_
#define OOK_STRING_H_

#include "ookLibs/ookCore/typedefs.h"
#include "boost/shared_ptr.hpp"
#include <vector>

class ookString
{
public:

	ookString();
	ookString(const ookString& cpy);
	virtual ookString& operator= (const ookString &cpy);		
	virtual ~ookString();
	
	static string ConvertInt2String (int i);	
	static string LeftPad(string str, char padchar, int length);
	static vector<string> Split(string str, string delims);
	static vector<ucstring> UCSplit(ucstring str, ucstring delims);
	
	static ulong UCharsToULong(uchar* chars);
	static void ULongToUChars(ulong longint, uchar* outchars);
	
	static bool IsBase64(unsigned char c);
	static ucstring UCBase64Encode(ucstring bytes_to_encode);
	static ucstring UCBase64Decode(ucstring const& encoded_string);

protected:
	
private:
	
	
};

#ifndef ookStringPtr
typedef boost::shared_ptr<ookString> ookStringPtr;
#endif

#endif