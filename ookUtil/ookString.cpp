/*
 Copyright © 2011, Ted Biggs
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
 \class ookString
 \headerfile ookString.h "ookLibs/ookUtil/ookString.h"
 \brief Utility class which provides string manipulation and 
 conversion.
 */
#include "ookLibs/ookUtil/ookString.h"
#include "boost/algorithm/string.hpp"
#include <sstream>

/*! 
 \brief Default constructor.
 */
ookString::ookString()
{
	
}

/*! 
 \brief Destructor.
 */
ookString::~ookString()
{
	
}


/*! 
 \brief Converts an integer to its string representation.
 
 \param i	The integer to be converted.
 \return The integer's string representation.
 */
string ookString::ConvertInt2String (int i)
{
	string s;
	stringstream out;
	out << i;
	s = out.str();
	
	return s;
}

/*! 
 \brief Indicates whether a given unsigned character is a valid
 BASE64 character.
 
 \return true if the character is valid BASE64, false otherwise.
 */
bool ookString::IsBase64(unsigned char c) 
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/*! 
 \brief Converts a string of unsigned characters into BASE64 format.
 
 \param msg	The string to be converted.
 \return	The converted string.
 */
ucstring ookString::UCBase64Encode(ucstring msg) 
{
  ucstring ret;
	unsigned int in_len = msg.length();
	unsigned char const* bytes_to_encode = msg.data();
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) 
	{
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) 
		{
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i < 4) ; i++)
        ret += BASE64_CHARS[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += BASE64_CHARS[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

/*! 
 \brief Converts a BASE64 string to a string of unsigned characters.
 
 \param msg	The string to be converted.
 \return	The converted string.
 */
ucstring ookString::UCBase64Decode(ucstring const& encoded_string) 
{
  int in_len = encoded_string.length();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  ucstring ret;

  while (in_len-- && ( encoded_string[in_] != '=') && IsBase64(encoded_string[in_])) 
	{
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i == 4) 
		{
      for (i = 0; i < 4; i++)
        char_array_4[i] = BASE64_CHARS.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if(i) 
	{
    for (j = i; j < 4; j++)
      char_array_4[j] = 0;

    for (j = 0; j < 4; j++)
      char_array_4[j] = BASE64_CHARS.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) 
			ret += char_array_3[j];
  }

  return ret;
}

/*! 
 \brief Splits a string by a set of delimiters.
 
 \param str	The string to be split.
 \param delims	The delimiters by which to perform the split.
 \return	A vector containing the individual tokens following the split.
 */
vector<string> ookString::Split(string str, string delims)
{
	vector<string> ret;
	
	split(ret, str, boost::is_any_of(delims));	
	
	return ret;
}

/*! 
 \brief Splits an unsigned character string by a set of delimiters.
 
 \param str	The string to be split.
 \param delims	The delimiters by which to perform the split.
 \return	A vector containing the individual tokens following the split.
 */
vector<ucstring> ookString::UCSplit(ucstring str, ucstring delims)
{
	vector<ucstring> ret;
	
	split(ret, str, boost::is_any_of(delims));	
	
	return ret;
}

/*! 
 \brief Left pads a string by the specified character. Padding will only be
 performed up to the specified string length.
 
 \param str	The string to be padded.

 \return	A string, left padded with the specified character at the specified length.
 */
string ookString::LeftPad(string str, char padchar, int length)
{
	if(str.length() > 0)
	{
		if(str.length() < length)
		{
			for(int i=0; i <= (length - str.length()); i++)
				str = padchar + str;
		}
	}
	
	return str;
}

/*! 
 \brief Converts an array of 4 unsigned characters to its unsigned long
 representation. 
 
 \param chars	The array to be transformed into an unsigned long.
 \return	The unsigned long representation of the characters.
 */
ulong ookString::UCharsToULong(uchar* chars)
{
	ulong a;
	char hexchars[4];
	
	a = (unsigned long)0;
	
	sprintf(hexchars, "%X%X%X%X", chars[0], chars[1], chars[2], chars[3]);
	sscanf(hexchars, "%X", &a);
	
	return a;

}

/*! 
 \brief Converts an unsigned long into an array of 4 unsigned characters.
 
 \param longint	The unsigned long value to be converted.
 \param outchars	The array which the converted characters will be placed into.
 */
void ookString::ULongToUChars(ulong longint, uchar* outchars)
{
	// convert from an unsigned long int to a 4-byte array
	outchars[0] = (unsigned char)((longint >> 24) & 0xFF) ;
	outchars[1] = (unsigned char)((longint >> 16) & 0xFF) ;
	outchars[2] = (unsigned char)((longint >> 8) & 0XFF);
	outchars[3] = (unsigned char)((longint & 0XFF));

}