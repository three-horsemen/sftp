#ifndef INCLUDE_SECURITY_SECURESOCKET_HPP_
#define INCLUDE_SECURITY_SECURESOCKET_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "security/cryptmath.hpp"
#include "security/cryptstr.hpp"
#include "security/encrypt.hpp"
//#include "shared/socketexceptions.hpp"
#include <exception>

#define HOST_MODE_SERVER 100
#define HOST_MODE_CLIENT 101

class DHKeyContainer
{
private:
    static const int goodPrimePThreshold;
    static const int goodPrimeQThreshold;
    static const std::string goodLocalPrivateThreshold;
    static const std::string goodLocalPublicThreshold;
    static const std::string goodRemotePublicThreshold;
    static const std::string goodSharedSecretThreshold;

    bool valid;
    int primeP;
    int primeQ;
    std::string localPrivate;
    std::string localPublic;
    std::string remotePublic;
    std::string sharedSecret;
public:
    DHKeyContainer();
    bool isGoodPrimeP();
    bool isGoodPrimeQ();
    bool isGoodLocalPrivate();
    bool isGoodLocalPublic();
    bool isGoodRemotePublic();
    bool isGoodSharedSecret();
    void setValidity(bool newValidity);
    bool getValidity();
    int getPrimeP();
    void setPrimeP(int p);
    int getPrimeQ();
    void setPrimeQ(int q);
    std::string getLocalPrivate();
    void setLocalPrivate(std::string newLocalPrivate);
    std::string getLocalPublic();
    void setLocalPublic(std::string newLocalPublic);
    std::string getRemotePublic();
    void setRemotePublic(std::string newRemotePublic);
    std::string getSharedSecret();
    void setSharedSecret(std::string newSharedSecret);
};

class SecureSocket
{
private:
    bool valid;
    int socketDescriptor;
    std::string targetIPAddress;
    std::string targetPortNumber;

    std::string sourceIPAddress;
    std::string sourcePortNumber;

    std::string buffer;
public:
    SecureSocket();
    void setValidity(bool newValidity);
    bool getValidity();
    int getSocketDescriptor();
    void setSocketDescriptor(int newSocketDescriptor);
    std::string getTargetIPAddress();
    void setTargetIPAddress(std::string newTargetIPAddress);
    std::string getTargetPortNumber();
    void setTargetPortNumber(std::string newTargetPortNumber);

    std::string getSourceIPAddress();
    void setSourceIPAddress(std::string newSourceIPAddress);
    std::string getSourcePortNumber();
    void setSourcePortNumber(std::string newSourcePortNumber);

    std::string getBuffer();
    void setBuffer(std::string newBuffer);

    int initSecureSocket();
    int destroySecureSocket();

    std::string getTargetAddrFromSockDesc();
    std::string getTargetPortFromSockDesc();
    std::string getSourceAddrFromSockDesc();
    std::string getSourcePortFromSockDesc();

    //~SecureSocket();
};

class SecureDataSocket : public SecureSocket
{
private:
    DHKeyContainer keyContainer;
public:
    SecureDataSocket();
    SecureDataSocket(std::string targetIPAddress, std::string targetPortNumber, int hostMode);
    DHKeyContainer getKeyContainer();
    int connectSecureSocket();
    int readSecureSocket();
    int writeSecureSocket();

    void setAndEncryptBuffer(std::string message);
    std::string getAndDecryptBuffer();
    void encryptAndSendSecureSocket(std::string message);
    void encryptAndSendSecureSocket();
    std::string decryptAndReceiveSecureSocket();

    int performDHExchange_asClient();
    int performDHExchange_asServer();
};

class SecureListenSocket : public SecureSocket
{
private:
    static const int queueSize;
public:
    SecureListenSocket();
    SecureListenSocket(std::string serverIPAddress, std::string serverPortNumber);
    int bindSecureSocket();
    int listenSecureSocket();
    SecureDataSocket acceptSecureSocket();
};



/////Exceptions, defined in socketexceptions.hpp

class SecureSocketException : public std::exception
{
private:
	SecureSocket secureSocket;
	std::string message;
public:
	SecureSocketException(SecureSocket newSecureSocket);
	SecureSocketException(SecureSocket newSecureSocket, std::string message);
	std::string getMessage();
	virtual const char* what() const throw()
	{
		return string_to_charArray("Exception: SecureSocketException. " + message + "\n");
	}
};

class SecureDataSocketException : public SecureSocketException
{
private:
	SecureDataSocket secureDataSocket;
public:
	SecureDataSocketException(SecureDataSocket newSecureDataSocket);
	SecureDataSocketException(SecureDataSocket newSecureDataSocket, std::string message);
};

class SecureListenSocketException : public SecureSocketException
{
private:
	SecureListenSocket secureListenSocket;
public:
	SecureListenSocketException(SecureListenSocket newSecureListenSocket);
	SecureListenSocketException(SecureListenSocket newSecureListenSocket, std::string message);
};

class SecureDataSocketIOException : public SecureDataSocketException
{
private:
public:
	SecureDataSocketIOException(SecureDataSocket newSecureDataSocket);
	SecureDataSocketIOException(SecureDataSocket newSecureDataSocket, std::string message);
};

class SecureDataSocketConnectException : public SecureDataSocketException
{
private:
public:
	SecureDataSocketConnectException(SecureDataSocket newSecureDataSocket);
	SecureDataSocketConnectException(SecureDataSocket newSecureDataSocket, std::string message);
};

class SecureDataSocketDHException : public SecureDataSocketException
{
private:
public:
	SecureDataSocketDHException(SecureDataSocket newSecureDataSocket);
	SecureDataSocketDHException(SecureDataSocket newSecureDataSocket, std::string message);
};

class SecureListenSocketBindException : public SecureListenSocketException
{
private:
public:
	SecureListenSocketBindException(SecureListenSocket newSecureListenSocket);
	SecureListenSocketBindException(SecureListenSocket newSecureListenSocket, std::string message);
};

class SecureListenSocketListenException : public SecureListenSocketException
{
private:
public:
	SecureListenSocketListenException(SecureListenSocket newSecureListenSocket);
	SecureListenSocketListenException(SecureListenSocket newSecureListenSocket, std::string message);
};

class SecureListenSocketAcceptException : public SecureListenSocketException
{
private:
public:
	SecureListenSocketAcceptException(SecureListenSocket newSecureListenSocket);
	SecureListenSocketAcceptException(SecureListenSocket newSecureListenSocket, std::string message);
};

class DHKeyContainerException : public std::exception
{
private:
	DHKeyContainer key_container;
	std::string message;
public:
	DHKeyContainerException(DHKeyContainer new_key_container);
	DHKeyContainerException(DHKeyContainer new_key_container, std::string newMessage);
	virtual const char* what() const throw()
	{
		return string_to_charArray("Exception: DHKeyContainerException. " + message + "\n");
	}
};

#endif /* INCLUDE_SECURITY_SECURESOCKET_HPP_ */
