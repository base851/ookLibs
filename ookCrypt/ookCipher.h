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
#ifndef OOK_CIPHER_H_
#define OOK_CIPHER_H_

/*! 
 \class ookCipher
 \headerfile ookCipher.h "ookLibs/ookCrypt/ookCipher.h"
 \brief Abstract base class for Ciphers.
 */
#include "ookLibs/ookCore/typedefs.h"
#include "cryptopp/cryptlib.h"
#include "boost/shared_ptr.hpp"

class ookCipher
{
public:
	
	virtual ~ookCipher();
	
	string GetKey();
	void SetKey(string key);
	
/*! 
 \brief Encrypts a string. Pure virtual method
	 which must be overriden by implementing classes.
 
 \param msg	The string to be encrypted.
 
 \return The encrypted string.
 */
	virtual string Encrypt(string msg) = 0;

/*! 
 \brief Decrypts a string. Pure virtual method
	 which must be overriden by implementing classes.
 
 \param msg	The string to be decrypted.
 
 \return The decrypted string.
 */
	virtual string Decrypt(string crypt) = 0;

/*! 
 \brief Initializes the cipher. Pure virtual method
	 which must be overriden by implementing classes.
 */
	virtual void Initialize() = 0;
	
protected:
	
	ookCipher();
	ookCipher(string key);	
	ookCipher(const ookCipher& cpy);
	virtual ookCipher& operator= (const ookCipher &cpy);	
	
	string _key;
	byte* _keybytes;
	
private:
	
};

#ifndef ookCipherPtr
typedef boost::shared_ptr<ookCipher> ookCipherPtr;
#endif

#endif