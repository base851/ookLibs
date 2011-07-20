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
 \class ookKeyValuePair
 \headerfile ookKeyValuePair.h "ookLibs/ookUtil/ookKeyValuePair.h"
 \brief Simple template class encapsulating a key/value pair.
 */
#ifndef OOK_KEY_VALUE_PAIR_H_
#define OOK_KEY_VALUE_PAIR_H_

#include "ookLibs/ookCore/typedefs.h"

template<class T, class U>
class ookKeyValuePair
{
public:

	ookKeyValuePair();
	ookKeyValuePair(T key, U value);
	virtual ~ookKeyValuePair();

	T GetKey();
	U GetValue();

protected:


private:

	T _key;
	U _value;

};

/*! 
 \brief Default constructor.
 */
template<class T, class U>
ookKeyValuePair<T, U>::ookKeyValuePair()
{

}

/*! 
 \brief Initialization constructor.
 */
template<class T, class U>
ookKeyValuePair<T, U>::ookKeyValuePair(T key, U value)
	: _key(key), _value(value)
{

}

/*! 
 \brief Destructor.
 */
template<class T, class U>
ookKeyValuePair<T, U>::~ookKeyValuePair()
{

}

template<class T, class U>
T ookKeyValuePair<T, U>::GetKey()
{
	return _key;
}

template<class T, class U>
U ookKeyValuePair<T, U>::GetValue()
{
	return _value;
}

#endif