/*
 * SocketException.hpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#ifndef SOCKETIOEXCEPTION_HPP_
#define SOCKETIOEXCEPTION_HPP_

#include <string>
#include <exception>

#include <shared/logger.hpp>

namespace shared {

using namespace std;

class SocketIOException: public exception {
private:
	int s;
	size_t attemptSize;
	ssize_t resultSize;
public:
	SocketIOException(int, size_t, ssize_t);
	const char * what() const throw ();

	int getSocketDescriptor() const;
	size_t getAttemptSize();
	ssize_t getResultSize();

	void log();
};

} /* namespace shared */

#endif /* SOCKETIOEXCEPTION_HPP_ */
