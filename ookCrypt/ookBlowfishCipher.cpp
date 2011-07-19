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

// blowfish.cpp   C++ class implementation of the BLOWFISH encryption algorithm
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

/*! 
 \class ookBlowfishCipher
 \headerfile ookBlowfishCipher.h "ookLibs/ookCrypt/ookBlowfishCipher.h"
 \brief Performs Blowfish encryption/decryption.
 */
#include "ookLibs/ookCrypt/ookBlowfishCipher.h"

ookBlowfishCipher::ookBlowfishCipher()
{
//	_PArray = new ulong[18];
//	_SBoxes = new ulong[4][256];
}

ookBlowfishCipher::ookBlowfishCipher(string key)
: ::ookCipher(key)
{
//	_PArray = new ulong[18];
//	_SBoxes = new ulong[4][256];
}

ookBlowfishCipher::~ookBlowfishCipher()
{
//	delete _PArray;
//	delete [] _SBoxes;	
}

void ookBlowfishCipher::Initialize()
{
	_keybytes = new byte[CryptoPP::Blowfish::DEFAULT_KEYLENGTH];
	memset(_keybytes, 0, CryptoPP::Blowfish::DEFAULT_KEYLENGTH);
	for(int i=0; (i < _key.length()) && (i < CryptoPP::Blowfish::DEFAULT_KEYLENGTH); i++)
	{
		_keybytes[i] = _key[i];
	}		
	
/*	
	int  		i, j ;
	int keybytes = _key.length();
	ulong  		data, datal, datar ;
	aword temp ;
	
	// first fill arrays from data tables
	for (i = 0 ; i < 18 ; i++)
		_PArray [i] = bf_P [i] ;
	
	for (i = 0 ; i < 4 ; i++)
	{
	 	for (j = 0 ; j < 256 ; j++)
	 		_SBoxes [i][j] = bf_S [i][j] ;
	}
	
	j = 0 ;
	for (i = 0 ; i < 18 ; ++i)
	{
		temp.dword = 0 ;
		temp.w.byte0 = _key[j];
		temp.w.byte1 = _key[(j+1) % keybytes] ;
		temp.w.byte2 = _key[(j+2) % keybytes] ;
		temp.w.byte3 = _key[(j+3) % keybytes] ;
		data = temp.dword ;
		_PArray [i] ^= data ;
		j = (j + 4) % keybytes ;
	}
	
	datal = 0 ;
	datar = 0 ;
	
	for (i = 0 ; i < 18 ; i += 2)
	{
		Blowfish_encipher (&datal, &datar) ;
		_PArray [i] = datal ;
		_PArray [i + 1] = datar ;
	}
	
	for (i = 0 ; i < 4 ; ++i)
	{
		for (j = 0 ; j < 256 ; j += 2)
		{
		  Blowfish_encipher (&datal, &datar) ;
		  _SBoxes [i][j] = datal ;
		  _SBoxes [i][j + 1] = datar ;
		}
	}	
*/ 
}

string ookBlowfishCipher::Encrypt(string msg)
{
	// Cipher Text Sink
	std::string CipherText;
	
	// Encryptor
	CryptoPP::CFB_Mode< CryptoPP::Blowfish >::Encryption Encryptor(_keybytes, CryptoPP::Blowfish::DEFAULT_KEYLENGTH);	
	
	// Encryption
	CryptoPP::StringSource(msg, true,
												 new CryptoPP::StreamTransformationFilter( Encryptor,
																																	new CryptoPP::StringSink( CipherText )
																																	) // StreamTransformationFilter
												 ); // StringSource
	
	return CipherText;	
/*	
	vector<uchar> rRet;
	for(int i = 0; i < msg.length(); i += _BLOCK_SIZE)
	{
		vector<uchar> vchunk;
		vector<uchar> rchunk;

		//Fetch a block size chunk off the message string
		ucstring chunk = msg.substr(i, _BLOCK_SIZE);

		//Push message chunk characters onto our vector
		for(int j=0; j < chunk.length(); j++)
			vchunk.push_back(chunk[j]);

		//null pad any short chunks. Should only be the last one
		for(int l = vchunk.size(); l < _BLOCK_SIZE; l++)
			vchunk.push_back('\0');

		//Encode the chunk
		rchunk = Encode(vchunk);

		//Push the encrypted text onto our return vector
		for(int k=0; k < _BLOCK_SIZE; k++)
			rRet.push_back(rchunk[k]);
	}
		
	return rRet;
*/
	
//	return "";
}

string ookBlowfishCipher::Decrypt(string msg)
{
	// Recovered Text Sink
	std::string RecoveredText;
	
	// Decryptor
	CryptoPP::CFB_Mode< CryptoPP::Blowfish >::Decryption Decryptor( _keybytes, CryptoPP::Blowfish::DEFAULT_KEYLENGTH );
	
	// Decryption
	CryptoPP::StringSource( msg, true,
												 new CryptoPP::StreamTransformationFilter( Decryptor,
																																	new CryptoPP::StringSink( RecoveredText )
																																	) // StreamTransformationFilter
												 ); // StringSource		
	
	return RecoveredText;	
	
/*	
	ucstring rRet;

	for(int i = 0; i < msg.size(); i += _BLOCK_SIZE)
	{
		vector<uchar> vchunk;
		vector<uchar> rchunk;

		//Pull a block size chunk off of our input vector
		for(int j=i; (j - i) < _BLOCK_SIZE; j++)
			vchunk.push_back(msg[j]);

		//Decrypt the chunk
		rchunk = Decode(vchunk);

		//Push the results onto our return vector
		for(int k=0; k < _BLOCK_SIZE; k++)
			rRet += rchunk[k];
	}

	return rRet;
*/
	
//	return "";
}

/*
vector<uchar> ookBlowfishCipher::Encode(vector<uchar> msg)
{
	ulong lSize = (ulong) _BLOCK_SIZE;
	vector<uchar> vRet;
	uchar* pInput = new uchar[lSize];
	
	for(int z = 0; z < lSize; z++)
		pInput[z] = msg[z];

	pInput[lSize] = 0;

	for (int lCount = 0 ; lCount < lSize ; lCount += 8)
	{
		Blowfish_encipher ((ulong *) pInput,
			  								 (ulong *) (pInput + 4));	

		vRet.push_back(pInput[0]);
		vRet.push_back(pInput[1]);
		vRet.push_back(pInput[2]);
		vRet.push_back(pInput[3]);
		vRet.push_back(pInput[4]);
		vRet.push_back(pInput[5]);
		vRet.push_back(pInput[6]);
		vRet.push_back(pInput[7]);
			
		pInput += 8 ;			
	}

	return  vRet;
}

vector<uchar> ookBlowfishCipher::Decode(vector<uchar> crypt)
{
	ulong lSize = (ulong) _BLOCK_SIZE;
	vector<uchar> vRet;
	uchar* pInput = new uchar[lSize];
	
	for(int z = 0; z < lSize; z++)
		pInput[z] = crypt[z];

	pInput[lSize] = 0;

	for (int lCount = 0 ; lCount < lSize ; lCount += 8)
	{
		Blowfish_decipher ((ulong *) pInput,
			  								 (ulong *) (pInput + 4));	
												 
		vRet.push_back(pInput[0]);
		vRet.push_back(pInput[1]);
		vRet.push_back(pInput[2]);
		vRet.push_back(pInput[3]);
		vRet.push_back(pInput[4]);
		vRet.push_back(pInput[5]);
		vRet.push_back(pInput[6]);
		vRet.push_back(pInput[7]);	 
		
		pInput += 8 ;			
	}

	return  vRet;	
}

void ookBlowfishCipher::Blowfish_encipher(ulong* xl, ulong* xr)
{
	aword  Xl, Xr ;
	
	Xl.dword = *xl ;
	Xr.dword = *xr ;

	Xl.dword ^= _PArray [0];
	BF_ROUND (Xr, Xl, 1) ;  BF_ROUND (Xl, Xr, 2) ;
	BF_ROUND (Xr, Xl, 3) ;  BF_ROUND (Xl, Xr, 4) ;
	BF_ROUND (Xr, Xl, 5) ;  BF_ROUND (Xl, Xr, 6) ;
	BF_ROUND (Xr, Xl, 7) ;  BF_ROUND (Xl, Xr, 8) ;
	BF_ROUND (Xr, Xl, 9) ;  BF_ROUND (Xl, Xr, 10) ;
	BF_ROUND (Xr, Xl, 11) ; BF_ROUND (Xl, Xr, 12) ;
	BF_ROUND (Xr, Xl, 13) ; BF_ROUND (Xl, Xr, 14) ;
	BF_ROUND (Xr, Xl, 15) ; BF_ROUND (Xl, Xr, 16) ;
	Xr.dword ^= _PArray [17] ;

	*xr = Xl.dword ;
	*xl = Xr.dword ;

}

void ookBlowfishCipher::Blowfish_decipher(ulong* xl, ulong* xr)
{
	aword  Xl ;
	aword  Xr ;
	
	Xl.dword = *xl ;
	Xr.dword = *xr ;
	
	Xl.dword ^= _PArray [17] ;
	BF_ROUND (Xr, Xl, 16) ;  BF_ROUND (Xl, Xr, 15) ;
	BF_ROUND (Xr, Xl, 14) ;  BF_ROUND (Xl, Xr, 13) ;
	BF_ROUND (Xr, Xl, 12) ;  BF_ROUND (Xl, Xr, 11) ;
	BF_ROUND (Xr, Xl, 10) ;  BF_ROUND (Xl, Xr, 9) ;
	BF_ROUND (Xr, Xl, 8) ;   BF_ROUND (Xl, Xr, 7) ;
	BF_ROUND (Xr, Xl, 6) ;   BF_ROUND (Xl, Xr, 5) ;
	BF_ROUND (Xr, Xl, 4) ;   BF_ROUND (Xl, Xr, 3) ;
	BF_ROUND (Xr, Xl, 2) ;   BF_ROUND (Xl, Xr, 1) ;
	Xr.dword ^= _PArray [0];
	
	*xl = Xr.dword;
	*xr = Xl.dword;	
}
*/