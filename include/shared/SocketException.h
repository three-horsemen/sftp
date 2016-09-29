/*
 * SocketException.h
 *
 *  Created on: 29-Sep-2016
 *      Author: reubenjohn
 */

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include <exception>
#include <string>

namespace shared {

class SocketException: public std::exception {
protected:
	int socket;
public:
	SocketException(int);
	virtual ~SocketException();

	int getSocketDescriptor();

	const char * what() const throw ();
};

} /* namespace shared */

#endif /* SOCKETEXCEPTION_H_ */
