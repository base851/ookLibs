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
 \class ookFile
 \headerfile ookFile.h "ookLibs/ookIO/ookFile.h"
 \brief Provides basic file read/write functionality. Files can be opened
 in any valid iostream mode and can be plaintext or binary.
 */
#include "ookLibs/ookIO/ookFile.h"

/*! 
 \brief Initialization constructor.

 \param filepath	The full path and filename.
 */
ookFile::ookFile(string filepath)
{
	
}

/*! 
 \brief Copy constructor.
 */
ookFile::ookFile(const ookFile& cpy)
{
	_filepath = cpy._filepath;
//	_filestream = cpy._filestream;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookFile& ookFile::operator= (const ookFile &cpy)
{
	if (&cpy != this)
	{
		_filepath = cpy._filepath;
//		_filestream = cpy._filestream;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */
ookFile::~ookFile()
{
	this->Close();
}

/*! 
 \brief Opens the file for reading & writing in default mode. 
 */
void ookFile::Open()
{
	_filestream.open(_filepath.data());
}

/*
 \brief Opens the file for reading and/or writing in specified mode(s). 

 \param modes	The mode(s) to open the file in. 

 Setting the open mode consists of bitwise OR-ing any combination of the below modes:
 
 ios::in - Open for input operations.
 ios::out - Open for output operations.
 ios::binary - Open in binary mode.
 ios::ate - Set the initial position at the end of the file. If this flag is not set to any value, the initial position is the beginning of the file.
 ios::app - All output operations are performed at the end of the file, appending the content to the current content of the file. This flag can only be used in streams open for output-only operations.
 ios::trunc - If the file opened for output operations already existed before, its previous content is deleted and replaced by the new one. 
 
 For example, if one wanted to open the file in binary mode for writing and truncate existing contents, the call would be:
 
 \code
 somefile.Open(ios::out | ios::binary | ios::trunc);
 \endcode

 */
void ookFile::Open(ios_base::openmode modes)
{
	if(!_filestream.is_open())
		_filestream.open(_filepath.data(), modes);	
}

/*! 
 \brief Closes the file. This should be performed after
 file reading/writing is complete in order to ensure data 
 integrity.
 */
void ookFile::Close()
{
	if(_filestream.is_open())
		_filestream.close();
}

/*! 
 \brief Fully reads in a file and returns its contents as a string. 

 \return The file's contents.
 */
string ookFile::Read()
{
	string input;
	
	if(_filestream.is_open())
		if(_filestream.good())
			_filestream >> input;
	
	return input;
}

/*! 
 \brief Fully reads in a file and returns its contents as a vector of strings. 

 \return The file's contents. Each string in the vector represents a line in the file.
 */
vector<string> ookFile::ReadLines()
{
	string line;
	vector<string> vRet;
	
	if(_filestream.is_open())
		while(_filestream.good())
		{
			getline(_filestream, line);
			vRet.push_back(line);
		}
	
	return vRet;
}

/*! 
 \brief Writes to a file. 

 \param content The content to be written to the file.
 */
void ookFile::Write(string content)
{
	if(_filestream.is_open())
		_filestream << content;
}

/*! 
 \brief Writes to a file & appends a "\n" line terminator. 

 \param content The content to be written to the file.
 */
void ookFile::WriteLine(string content)
{
	if(_filestream.is_open())
		_filestream << (content + "\n");
}