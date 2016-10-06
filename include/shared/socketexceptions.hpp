#include "security/securesocket.hpp"
#include <exception>

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
