//
//  ookGzip.cpp
//  ookLibs
//
//  Created by Ted Biggs on 7/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ookLibs/ookZip/ookGzip.h"


ookGzip::ookGzip()
{
	
}

ookGzip::~ookGzip()
{
	
}

string ookGzip::Compress(string source)
{
	string ret;
	
	CryptoPP::StringSource(source, true, new CryptoPP::Gzip (new CryptoPP::StringSink (ret))); 	
	
	return ret;
}

string ookGzip::Uncompress(string source)
{
	string ret;
	
	CryptoPP::StringSource(source, true, new CryptoPP::Gunzip (new CryptoPP::StringSink (ret))); 	
	
	return ret;	
}