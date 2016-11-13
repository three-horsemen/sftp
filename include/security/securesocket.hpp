#ifndef INCLUDE_SECURITY_SECURESOCKET_HPP_
#define INCLUDE_SECURITY_SECURESOCKET_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include "security/cryptmath.hpp"
#include "security/cryptstr.hpp"
#include "security/encrypt.hpp"
#include "security/socketexceptions.hpp"
#include "security/DHContainer.hpp"
#include "security/WELL1024a.hpp"
#include "shared/logger.hpp"

#define HOST_MODE_SERVER 100
#define HOST_MODE_CLIENT 101
#define DEFAULT_TIMEOUT_VALUE 5

class SecureSocket {
private:
	bool valid;
	int socketDescriptor;
	std::string targetIPAddress;
	std::string targetPortNumber;
	std::string sourceIPAddress;
	std::string sourcePortNumber;
	std::string buffer;

protected:

	SecureSocket();

	void setSocketDescriptor(int newSocketDescriptor);

	void setTargetIPAddress(std::string newTargetIPAddress);

	void setTargetPortNumber(std::string newTargetPortNumber);

	void setSourceIPAddress(std::string newSourceIPAddress);

	void setSourcePortNumber(std::string newSourcePortNumber);

	void setBuffer(std::string newBuffer);

	int initSecureSocket();

	std::string getTargetAddrFromSockDesc(int) const;

	std::string getTargetPortFromSockDesc(int) const;

	std::string getSourceAddrFromSockDesc(int) const;

	std::string getSourcePortFromSockDesc(int) const;

public:
	void setValidity(bool newValidity);

	bool getValidity() const;

	int getSocketDescriptor() const;

	std::string getTargetAddrFromSockDesc() const;

	std::string getTargetPortFromSockDesc() const;

	std::string getSourceAddrFromSockDesc() const;

	std::string getSourcePortFromSockDesc() const;

	std::string getTargetIPAddress() const;

	std::string getTargetPortNumber() const;

	std::string getSourceIPAddress() const;

	std::string getSourcePortNumber() const;

	std::string getBuffer() const;

	int destroySecureSocket();
};

class SecureDataSocket : public SecureSocket {
private:
	DHKeyContainer keyContainer;
	WELL1024_PRNG generator;
	int timeoutSecValue;

	int getTimeoutSecValue() const;

	void setTimeoutSecValue(int newTimeoutSecValue);

	DHKeyContainer getKeyContainer() const;

	int connectSecureSocket();

	int isTimeout(int timeoutSec, int socket);

	ssize_t readSecureSocket();

	ssize_t writeSecureSocket();

	void setAndEncryptBuffer(std::string message);

	std::string getAndDecryptBuffer();

public:
	SecureDataSocket();

	SecureDataSocket(int socketDescriptor);

	SecureDataSocket(std::string targetIPAddress, std::string targetPortNumber, int hostMode);

	void encryptAndSend(std::string message);

	std::string receiveAndDecrypt();

	int performDHExchange_asClient();

	int performDHExchange_asServer();
};

class SecureListenSocket : public SecureSocket {
private:
	static const unsigned int maxQueueSize;
public:
	SecureListenSocket();

	SecureListenSocket(std::string serverIPAddress, std::string serverPortNumber);

	int bindSecureSocket();

	int listenSecureSocket();

	SecureDataSocket acceptSecureSocket();
};

#endif
