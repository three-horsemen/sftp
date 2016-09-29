/*
 * SocketException.hpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#ifndef INVALIDSOCKETEXCEPTION_HPP_
#define INVALIDSOCKETEXCEPTION_HPP_

#include <string>
#include <exception>

#include <shared/logger.hpp>

namespace shared {

using namespace std;

class InvalidSocketException: public exception {
private:
	int socketDescriptor;
public:
	InvalidSocketException(int);
	const char * what() const throw ();

	int getSocketDescriptor() const;

	void setSocketDescriptor(int s);
	void log();
};

} /* namespace shared */

#endif /* INVALIDSOCKETEXCEPTION_HPP_ */
