#include "security/securesocket.hpp"
SecureSocketException::SecureSocketException(SecureSocket newSecureSocket)
{
	secureSocket = newSecureSocket;
	message = "";
}
SecureSocketException::SecureSocketException(SecureSocket newSecureSocket, std::string newMessage)
{
	secureSocket = newSecureSocket;
	message = newMessage;
}
SecureDataSocketException::SecureDataSocketException(SecureDataSocket newSecureDataSocket) : SecureSocketException::SecureSocketException((SecureSocket)newSecureDataSocket)
{
	secureDataSocket = newSecureDataSocket;
}
SecureDataSocketException::SecureDataSocketException(SecureDataSocket newSecureDataSocket, std::string msg) : SecureSocketException::SecureSocketException((SecureSocket)newSecureDataSocket, msg)
{
	secureDataSocket = newSecureDataSocket;
}

SecureListenSocketException::SecureListenSocketException(SecureListenSocket newSecureListenSocket) : SecureSocketException::SecureSocketException((SecureSocket)newSecureListenSocket)
{
	secureListenSocket = newSecureListenSocket;
}
SecureListenSocketException::SecureListenSocketException(SecureListenSocket newSecureListenSocket, std::string msg) : SecureSocketException::SecureSocketException((SecureSocket)newSecureListenSocket, msg)
{
	secureListenSocket = newSecureListenSocket;
}

SecureDataSocketIOException::SecureDataSocketIOException(SecureDataSocket newSecureDataSocket) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket){}
SecureDataSocketIOException::SecureDataSocketIOException(SecureDataSocket newSecureDataSocket, std::string msg) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket, msg){}

SecureDataSocketConnectException::SecureDataSocketConnectException(SecureDataSocket newSecureDataSocket) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket){}
SecureDataSocketConnectException::SecureDataSocketConnectException(SecureDataSocket newSecureDataSocket, std::string msg) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket, msg){}

SecureDataSocketDHException::SecureDataSocketDHException(SecureDataSocket newSecureDataSocket) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket){}
SecureDataSocketDHException::SecureDataSocketDHException(SecureDataSocket newSecureDataSocket, std::string msg) : SecureDataSocketException::SecureDataSocketException((SecureDataSocket)newSecureDataSocket, msg){}


SecureListenSocketBindException::SecureListenSocketBindException(SecureListenSocket newSecureListenSocket) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket){}
SecureListenSocketBindException::SecureListenSocketBindException(SecureListenSocket newSecureListenSocket, std::string msg) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket, msg){}

SecureListenSocketListenException::SecureListenSocketListenException(SecureListenSocket newSecureListenSocket) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket){}
SecureListenSocketListenException::SecureListenSocketListenException(SecureListenSocket newSecureListenSocket, std::string msg) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket, msg){}

SecureListenSocketAcceptException::SecureListenSocketAcceptException(SecureListenSocket newSecureListenSocket) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket){}
SecureListenSocketAcceptException::SecureListenSocketAcceptException(SecureListenSocket newSecureListenSocket, std::string msg) : SecureListenSocketException::SecureListenSocketException((SecureListenSocket)newSecureListenSocket, msg){}
