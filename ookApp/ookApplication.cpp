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
 \class ookApplication
 \headerfile ookApplication.h "ookLibs/ookApp/ookApplication.h"
 \brief Base class for applications based upon the ookLibs library.
 
 Applications do not need to have an ookApplication object in order to use
 ookLibs. However, what the ookApplication framework provides is a mechanism
 to initialize and store application configuration information. When using an
 ookApplication, simply initialize an app object in the program's main() function
 and then call Init() and AppMain().
 
 \code
 
 int main (int argc, const char** argv)
 {
 DerivedApplication app(argc, argv, 1313);
 app.Init();
 app.AppMain();
 
 return 0;
 }
 
 \endcode
 
 While ookApplications will subclass off of ookApplication, this class' Init( ) method
 should still be called, as it collects some basic information on the app's
 runtime environment.
 
 \code
 
 void DerivedApplication::Init()
 {
 ookApplication::Init();
 
 //Do any other initialization you may want to do
 } 
 
 \endcode
 
 */
#include "ookLibs/ookApp/ookApplication.h"
#include "ookLibs/ookUtil/ookString.h"
#include <vector>

#ifdef __GNUC__
#include <sys/utsname.h>
#endif

/*! 
 \brief Initialization constructor. This should be used by derived
 classes.
 
 \param argc	The argc value passed into the program's main() function.
 \param	argv	The argv value passed into the program's main() function.
 */
ookApplication::ookApplication(int argc, const char** argv)
	: _argc(argc), _argv(argv)
{
	
}

/*! 
 \brief Copy constructor.
 */
ookApplication::ookApplication(const ookApplication& cpy)
{
	_argc = cpy._argc;
	_argv = cpy._argv;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookApplication& ookApplication::operator= (const ookApplication& cpy)
{
	if(&cpy != this)
	{
		_argc = cpy._argc;
		_argv = cpy._argv;
	}
		
	return *this;
}

/*! 
 \brief Destructor.
 */
ookApplication::~ookApplication()
{
	
}

/*! 
 \brief Main initialization routine.
 
 This, along with AppMain() should be called in the program's
 main() function immediately after instantiation of the application
 object:
 
 \code
 
 int main (int argc, const char** argv)
 {
 DerivedApplication app(argc, argv, 1313);
 app.Init();
 app.AppMain();
 
 return 0;
 }
 
 \endcode
 
 Derived classes should call this base routine before performing their
 own operations:
 
 \code
 
 void DerivedApplication::Init()
 {
 ookApplication::Init();
 
 //Do any other initialization you may want to do
 } 
 
 \endcode
 
 */
void ookApplication::Init()
{
	//uname is a *NIX call
	#ifdef __GNUC__
		struct utsname unameData;
		if(uname(&unameData) >= 0)
		{
			this->SetConfigValue(SYSTEM_INFO_SYSNAME, unameData.sysname);
			this->SetConfigValue(SYSTEM_INFO_NODENAME, unameData.nodename); 
			this->SetConfigValue(SYSTEM_INFO_RELEASE, unameData.release);
			this->SetConfigValue(SYSTEM_INFO_VERSION, unameData.version);
			this->SetConfigValue(SYSTEM_INFO_MACHINE, unameData.machine);
		}
	#endif

	//Add argc
	this->SetConfigValue(APP_INFO_ARGC, ookString::ConvertInt2String(_argc));
	
	
	//This sets up a listing of each argv value as its own config entry
	for(int i = 0 ; i < _argc; i++)
		this->SetConfigValue(APP_INFO_ARGV + "." + ookString::ConvertInt2String(i), _argv[i]);
	
	//Now add the app full path, app path and app name
	this->SetConfigValue(APP_INFO_APP_FULL_PATH, _argv[0]);
	
//TODO: Make this Windoze path friendly as well	
	vector<string> toks = ookString::Split(_argv[0], "/");
	unsigned long iNumToks = toks.size();
	
	//Set the app name
	this->SetConfigValue(APP_INFO_APP_NAME, toks[(iNumToks - 1)]);
	
	//Reconstruct the front of the path
	string appDir = "/";
	for(int i = 0; i < (iNumToks - 1); i++)
	{
		appDir += toks[i] + "/";
	}
	
	this->SetConfigValue(APP_INFO_APP_DIR, appDir);
	
}

/*! 
 \brief Main application work routine.
 
 This is the function in which the program's primary functional
 code should be placed.
 
 This, along with Init() should be called in the program's
 main() function immediately after instantiation of the application
 object:
 
 \code
 
 int main (int argc, const char** argv)
 {
 DerivedApplication app(argc, argv, 1313);
 app.Init();
 app.AppMain();
 
 return 0;
 }
 
 \endcode
 */
void ookApplication::AppMain()
{
	
}

/*! 
 \brief Returns the specified configuration value.
 
 \param key	The key correspoinding to a configuration value.
 
 \return The requested configuration value.

 */
string ookApplication::GetConfigValue(string key)
{
	return _appConfigVals[key];
}

/*! 
 \brief Sets a value in the configuration list by the key provided.
 
 If the key already exists in the list, the value will be replaced.
 
 \param key	The key correspoinding to a configuration value.
 
 \param value The configuration value corresponding with the key.
 
 */
void ookApplication::SetConfigValue(string key, string value)
{
	_appConfigVals[key] = value;
}

/*! 
 \brief Returns all configuration keys.
 
 \return	All configuration keys.
 
 */
vector<string> ookApplication::GetConfigKeys()
{
	vector<string> key_list;
	
	for(StringMapIterator it = _appConfigVals.begin(); it != _appConfigVals.end(); ++it) 
    key_list.push_back(it->first);

	return key_list;
}

