/*
 * SocketException.cpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#include <string>
#include <shared/SocketIOException.hpp>

namespace shared {

SocketIOException::SocketIOException(int socket, size_t attemptSize,
		ssize_t resultSize) {
	this->s = socket;
	this->attemptSize = attemptSize;
	this->resultSize = resultSize;
}

int SocketIOException::getSocketDescriptor() const {
	return s;
}

size_t SocketIOException::getAttemptSize() {
	return attemptSize;
}

ssize_t SocketIOException::getResultSize() {
	return resultSize;
}

const char * SocketIOException::what() const throw () {
	return (std::string("Invalid socket exception with socket: ")
			+ std::to_string(attemptSize)).c_str();
}

void SocketIOException::log() {
	LOG_ERROR<<what();
}

}
/* namespace shared */
