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
 \class ookAESCipher
 \headerfile ookAESCipher.h "ookLibs/ookCrypt/ookAESCipher.h"
 \brief Derived ookCipher implementing the AES (Rijndael) algorithm.
 */
#include "ookLibs/ookCrypt/ookAESCipher.h"

/*! 
 \brief Default constructor.
 */
ookAESCipher::ookAESCipher()
{
	
}

/*! 
 \brief Initialization constructor.
 */
ookAESCipher::ookAESCipher(string key)
: ::ookCipher(key)
{
	
}

/*! 
 \brief Destructor.
 */
ookAESCipher::~ookAESCipher()
{
	
}

void ookAESCipher::Initialize()
{
	_keybytes = new byte[CryptoPP::AES::DEFAULT_KEYLENGTH];
//	memset( _keybytes, 0x01, CryptoPP::AES::DEFAULT_KEYLENGTH );
	memset(_keybytes, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	for(int i=0; (i < _key.length()) && (i < CryptoPP::AES::DEFAULT_KEYLENGTH); i++)
	{
		_keybytes[i] = _key[i];
	}
}

string ookAESCipher::Encrypt(string msg)
{	
	// Cipher Text Sink
	std::string CipherText;
		
	// Encryptor
	CryptoPP::CFB_Mode< CryptoPP::AES >::Encryption Encryptor(_keybytes, CryptoPP::AES::DEFAULT_KEYLENGTH);	
	
	// Encryption
	CryptoPP::StringSource(msg, true,
												 new CryptoPP::StreamTransformationFilter( Encryptor,
																																	new CryptoPP::StringSink( CipherText )
																																	) // StreamTransformationFilter
												 ); // StringSource
	
	return CipherText;
}

string ookAESCipher::Decrypt(string msg)
{	
	// Recovered Text Sink
	std::string RecoveredText;
	
	// Decryptor
	CryptoPP::CFB_Mode< CryptoPP::AES >::Decryption Decryptor( _keybytes, CryptoPP::AES::DEFAULT_KEYLENGTH );
	
	// Decryption
	CryptoPP::StringSource( msg, true,
												 new CryptoPP::StreamTransformationFilter( Decryptor,
																																	new CryptoPP::StringSink( RecoveredText )
																																	) // StreamTransformationFilter
												 ); // StringSource		

	return RecoveredText;
}