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
 \class ookCipher
 \headerfile ookCipher.h "ookLibs/ookCrypt/ookCipher.h"
 \brief Base class for cipher implementations.
 */
#include "ookLibs/ookCrypt/ookCipher.h"

/*! 
 \brief Default constructor.
 */
ookCipher::ookCipher()
{
	
}

/*! 
 \brief Initialization constructor.

 \param key	The encryption/decryption password.
 */
ookCipher::ookCipher(string key)
: _key(key)
{
	
}

/*! 
 \brief Copy constructor.
 */
ookCipher::ookCipher(const ookCipher& cpy)
{
	_key = cpy._key;
	_keybytes = cpy._keybytes;
}

/*! 
 \brief Overloaded assignment operator.
 */
ookCipher& ookCipher::operator= (const ookCipher &cpy)
{
	if (&cpy != this)
	{
		_key = cpy._key;
		_keybytes = cpy._keybytes;
	}
	
	return *this;
}

/*! 
 \brief Destructor.
 */
ookCipher::~ookCipher()
{
	
}

/*! 
 \brief Returns the encryption/decryption password.

 \return The encryption/decryption password.
 */
string ookCipher::GetKey()
{
	return _key;
}

/*! 
 \brief Sets the encryption/decryption password.

 \param key The encryption/decryption password.
 */
void ookCipher::SetKey(string key)
{
	_key = key;
}
