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
 \class ookXMLParser
 \headerfile ookXMLParser.h "ookLibs/ookXML/ookXMLParser.h"
 \brief Wrapper class around the tinyXML library.
 */
#include "ookLibs/ookXML/ookXMLParser.h"




/*! 
 \brief Default constructor.
 */
ookXMLParser::ookXMLParser()
{
	_doc = TiXmlDocumentPtr(new TiXmlDocument());
}

/*! 
 \brief Destructor.
 */
ookXMLParser::~ookXMLParser()
{
	
}

/*! 
 \brief Parses an XML string and places it into a document.
 */
void ookXMLParser::ParseXMLString(string xml)
{
	try
	{
		_doc->Parse(xml.data());
	}
	catch(...)
	{
	}
}

/*! 
 \brief Parses XML from a file and places it into a document.
 
 \param filename	The full path to the file to be parsed.
 \return	true if successful, false otherwise.
 */
bool ookXMLParser::LoadXMLFile(string filename)
{
	return _doc->LoadFile(filename.data());
}

/*! 
 \brief Saves XML data to a file.
 
 \param source	The full path to the XML file.
 \return	true if successful, false otherwise.
 */
bool ookXMLParser::SaveXMLFile(string filename)
{
	return _doc->SaveFile(filename.data());
}

/*! 
 \brief Returns the XML document containing the parsed XML.
 
 \return	The XML document.
 */
TiXmlDocumentPtr ookXMLParser::GetDocument()
{
	return _doc;
}

/*! 
 \brief Returns the XML document's root element.
 
 \return	The XML document's root element.
 */
TiXmlElementPtr ookXMLParser::GetRootElement()
{
	return TiXmlElementPtr(_doc->RootElement());
}

/*! 
 \brief Returns the XML document's first child element by name.
 
 \param tagname	The tag name.
 \return	The first XML element corresponding to the tag name.
 */
TiXmlElementPtr ookXMLParser::GetFirstChild(string tagname)
{
	return TiXmlElementPtr(_doc->FirstChildElement(tagname.data()));
}

/*! 
 \brief Returns a document handle object. Used to chain a query for
 a specific element in the document.
 
 \return	The document handle.
 */
TiXmlHandle ookXMLParser::GetDocumentHandle()
{
	return TiXmlHandle(_doc.get());
}