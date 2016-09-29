/*
 * SocketBufferEmptyException.cpp
 *
 *  Created on: 29-Sep-2016
 *      Author: reubenjohn
 */

#include "shared/SocketBufferEmptyException.h"

namespace shared {

SocketBufferEmptyException::SocketBufferEmptyException(int socket) :
		SocketException(socket) {
}

SocketBufferEmptyException::~SocketBufferEmptyException() {
	// TODO Auto-generated destructor stub
}

const char * SocketBufferEmptyException::what() const throw () {
	return (std::string("Invalid socket buffer empty exception with socket: ")
			+ std::to_string(this->socket)).c_str();
}

} /* namespace shared */
