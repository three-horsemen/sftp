/*
 * SecureDescriptor.cpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#include <security/SecureSocketManager.hpp>

namespace security {

SecureSocketManager::SecureSocketManager(int socketDescriptor) {
	this->s = socketDescriptor;
	if (s < 0) {
		throw shared::InvalidSocketException(s);
		//LOG_ERROR<<"Error: Connection was not accepted: "<<s<<'\n';
		return;
	} else {
		LOG_DEBUG<<"Successfully accepted socket\n";
	}
}

SecureSocketManager::~SecureSocketManager() {
	//close(s);
}

ssize_t SecureSocketManager::readBuffer(void* buffer, size_t size) {
	ssize_t n = read(s, buffer, size);
	if (n > 0) {
		return n;
	} else if (n == 0) {
		throw shared::SocketBufferEmptyException(s);
	} else {
		throw shared::SocketIOException(s, size, n);
	}
}
ssize_t SecureSocketManager::writeBuffer(const void *buffer, size_t size) {
//ssize_t SecureSocketManager::readBuffer(void* buffer, size_t size) {
	ssize_t n = write(s, buffer, size);
	if (n == -1) {
		throw shared::SocketIOException(s, size, n);
	} else {
		return n;
	}
}

int SecureSocketManager::getSocketDescriptor() {
	return s;
}

}
/* namespace shared */
