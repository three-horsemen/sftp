/*
 * SocketBufferEmptyException.h
 *
 *  Created on: 29-Sep-2016
 *      Author: reubenjohn
 */

#ifndef SOCKETBUFFEREMPTYEXCEPTION_H_
#define SOCKETBUFFEREMPTYEXCEPTION_H_

#include <string>

#include <shared/SocketException.h>

namespace shared {

using namespace std;

class SocketBufferEmptyException: public SocketException {
public:
	SocketBufferEmptyException(int);
	virtual ~SocketBufferEmptyException();

	const char * what() const throw ();
};

} /* namespace shared */

#endif /* SOCKETBUFFEREMPTYEXCEPTION_H_ */
