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
#ifndef OOK_RC5_CIPHER_H_
#define OOK_RC5_CIPHER_H_

#include "ookLibs/ookCore/typedefs.h"
#include "ookLibs/ookCrypt/ookCipher.h"
#include "cryptopp/rc5.h"
#include "cryptopp/modes.h"      // xxx_Mode< >
#include "cryptopp/filters.h"    // StringSource and

class ookRC5Cipher : public ookCipher
{
public:
	
	ookRC5Cipher();
	ookRC5Cipher(string key);
	
	virtual ~ookRC5Cipher();
	
	virtual string Encrypt(string msg);
	virtual string Decrypt(string crypt);
	
	void Initialize();
	
protected:
	

	
private:


};

#ifndef ookRC5CipherPtr
typedef boost::shared_ptr<ookRC5Cipher> ookRC5CipherPtr;
#endif

#endif
