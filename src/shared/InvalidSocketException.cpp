/*
 * SocketException.cpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#include <string>
#include <shared/InvalidSocketException.hpp>

namespace shared {

InvalidSocketException::InvalidSocketException(int socketDescriptor) {
	this->socketDescriptor = socketDescriptor;
}

int InvalidSocketException::getSocketDescriptor() const {
	return socketDescriptor;
}

void InvalidSocketException::setSocketDescriptor(int s) {
	this->socketDescriptor = s;
}

const char * InvalidSocketException::what() const throw () {
	return (std::string("Invalid socket exception with socket: ") + std::to_string(socketDescriptor)).c_str();
}

void InvalidSocketException::log() {
	LOG_ERROR<<what();
}

}
/* namespace shared */
