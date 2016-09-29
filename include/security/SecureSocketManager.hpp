/*
 * SecureDescriptor.hpp
 *
 *  Created on: 27-Sep-2016
 *      Author: reubenjohn
 */

#ifndef SECURESOCKETMANAGER_HPP_
#define SECURESOCKETMANAGER_HPP_

#include <iostream>
#include <exception>
#include <unistd.h>

#include <shared/logger.hpp>
#include <shared/InvalidSocketException.hpp>
#include <shared/SocketIOException.hpp>
#include <shared/SocketBufferEmptyException.h>

namespace security {

using namespace shared;

class SecureSocketManager {
private:
	int s;
public:
	SecureSocketManager(int);
	virtual ~SecureSocketManager();

	ssize_t readBuffer(void*, size_t);
	ssize_t writeBuffer(const void *buffer, size_t size);
	int getSocketDescriptor();
};

} /* namespace shared */

#endif /* SECURESOCKETMANAGER_HPP_ */
