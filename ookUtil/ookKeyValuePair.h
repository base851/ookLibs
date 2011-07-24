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

template<class T, class U>
class ookKeyValuePair
{
public:

	ookKeyValuePair();
	ookKeyValuePair(T key, U value);
	virtual ~ookKeyValuePair();

	T GetKey();
	U GetValue();

	void SetKey(T key);
	void SetValue(U value);

protected:


private:

	T _key;
	U _value;

};

//#ifndef ookKeyValuePairPtr
//typedef boost::shared_ptr<ookKeyValuePair> ookKeyValuePairPtr;
//#endif

/*! 
 \brief Default constructor.
 */
template<class T, class U>
ookKeyValuePair<T, U>::ookKeyValuePair()
{

}

/*! 
 \brief Initialization constructor.

 \param key The lookup key.
 \param value The value associated with the key.
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

/*! 
	 \brief Returns the key component of the pair.
	 
	 \return The key component of the pair.
*/	
template<class T, class U>
T ookKeyValuePair<T, U>::GetKey()
{
	return _key;
}

/*! 
	 \brief Returns the value component of the pair.
	 
	 \return The value component of the pair.
*/
template<class T, class U>
U ookKeyValuePair<T, U>::GetValue()
{
	return _value;
}

/*! 
	 \brief Sets the key component of the pair.
	 
	 \param key The key component of the pair.
*/
template<class T, class U>
void ookKeyValuePair<T, U>::SetKey(T key)
{
	_key = key;
}

/*! 
	 \brief Sets the value component of the pair.
	 
	 \param value The value component of the pair.
*/
template<class T, class U>
void ookKeyValuePair<T, U>::SetValue(U value)
{
	_value = value;
}

#endif