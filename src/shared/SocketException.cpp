/*
 * SocketException.cpp
 *
 *  Created on: 29-Sep-2016
 *      Author: reubenjohn
 */

#include "shared/SocketException.h"

namespace shared {

SocketException::SocketException(int socket) {
	this->socket = socket;
}

SocketException::~SocketException() {
	// TODO Auto-generated destructor stub
}

int SocketException::getSocketDescriptor() {
	return socket;
}

const char * SocketException::what() const throw () {
	return (std::string("Invalid socket exception with socket: ")
			+ std::to_string(this->socket)).c_str();
}

} /* namespace shared */
