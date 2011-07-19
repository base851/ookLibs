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

#ifndef OOK_TYPEDEFS_H_
#define OOK_TYPEDEFS_H_

#ifdef _WIN32
#include <winsock2.h>
#endif

#include "openssl/aes.h"
#include "openssl/bio.h"
#include "openssl/blowfish.h"
#include "openssl/conf.h"
#include "openssl/des.h"
#include "openssl/engine.h"
#include "openssl/err.h"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/rand.h"
#include "openssl/rsa.h"
#include "openssl/ssl.h"

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/scoped_array.hpp"
#include "boost/unordered_map.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/asio/error.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/asio/ssl/context_base.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "ookLibs/ookCore/ookException.h"
#include "ookLibs/ookXml/tinyxml.h"

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace boost;
using asio::ip::tcp;

//==========================================================
// Typedefs
//==========================================================

#ifndef ulong
/*!
 Unsigned long.
 */
typedef unsigned long ulong;
#endif

#ifndef uint
/*!
 Unsigned int.
 */
typedef unsigned int uint;
#endif

#ifndef ushort
/*!
 Unsigned short.
 */
typedef unsigned short ushort;
#endif

#ifndef uchar
/*!
 Unsigned char.
 */
typedef unsigned char uchar;
#endif

#ifndef ucstring
/*!
 std::basic_string <unsigned char>
 */
typedef std::basic_string <unsigned char> ucstring;
#endif

//==========================================================
// Constants
//==========================================================
const static string BASE64_CHARS("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

/*!
 The OS name.
 */
static const string SYSTEM_INFO_SYSNAME = "system.info.sysname";
/*!
 The node name.
 */
static const string SYSTEM_INFO_NODENAME = "system.info.nodename";
/*!
 Release number for the OS.
 */
static const string SYSTEM_INFO_RELEASE = "system.info.release";
/*!
 The OS version.
 */
static const string SYSTEM_INFO_VERSION = "system.info.version";
/*!
 The machine on which the OS is running.
 */
static const string SYSTEM_INFO_MACHINE = "system.info.machine";
/*!
 The argc value passed into main().
 */
static const string APP_INFO_ARGC = "app.info.argc";
/*!
 The argv value passed into main().
 */
static const string APP_INFO_ARGV = "app.info.argv";
/*!
 The full path for the application that is running.
 */
static const string APP_INFO_APP_FULL_PATH = "app.info.appFullPath";
/*!
 The directory in which the application is running.
 */
static const string APP_INFO_APP_DIR = "app.info.appDir";
/*!
 The application executable name.
 */
static const string APP_INFO_APP_NAME = "app.info.appName";

//==========================================================
// Boost Typedefs
//==========================================================
#ifndef StringMap
/*!
 std::basic_string <unsigned char>
 */
typedef unordered_map<string,string> StringMap;
#endif

#ifndef string_iterator
/*!
 boost::unordered_map<string, string>::const_iterator
 */
typedef boost::unordered_map<string, string>::const_iterator StringMapIterator;
#endif

#ifndef socket_ptr
/*!
 boost::shared_ptr<tcp::socket>
 */
typedef boost::shared_ptr<tcp::socket> socket_ptr;
#endif

#ifndef ssl_socket
/*!
 boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
 */
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
#endif

#ifndef ssl_socket_ptr
/*!
 boost::shared_ptr<ssl_socket>
 */
typedef boost::shared_ptr<ssl_socket> ssl_socket_ptr;
#endif

#ifndef base_method
/*!
 boost::asio::ssl::context_base::method
 */
typedef enum asio::ssl::context_base::method base_method;
#endif

#ifndef base_file_format
/*!
 boost::asio::ssl::context_base::file_format
 */
typedef enum asio::ssl::context_base::file_format base_file_format;
#endif

#endif