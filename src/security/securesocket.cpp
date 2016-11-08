#include "security/securesocket.hpp"

SecureSocket::SecureSocket() {
	setValidity(false);
	LOG_DEBUG << "Creating a new, empty SecureSocket() #"
			  << getSocketDescriptor() << " assigned to "
			  << getTargetAddrFromSockDesc() << ":"
			  << getTargetPortFromSockDesc();
}

bool SecureSocket::getValidity() const {
	return valid;
}

void SecureSocket::setValidity(bool newValidity) {
	valid = newValidity;
}

int SecureSocket::getSocketDescriptor() const {
	return socketDescriptor;
}

void SecureSocket::setSocketDescriptor(int newSocketDescriptor) {
	socketDescriptor = newSocketDescriptor;
}

std::string SecureSocket::getTargetIPAddress() const {
	return targetIPAddress;
}

void SecureSocket::setTargetIPAddress(std::string newTargetIPAddress) {
	targetIPAddress = newTargetIPAddress;
}

std::string SecureSocket::getTargetPortNumber() const {
	return targetPortNumber;
}

void SecureSocket::setTargetPortNumber(std::string newTargetPortNumber) {
	targetPortNumber = newTargetPortNumber;
}

std::string SecureSocket::getSourceIPAddress() const {
	return sourceIPAddress;
}

void SecureSocket::setSourceIPAddress(std::string newSourceIPAddress) {
	sourceIPAddress = newSourceIPAddress;
}

std::string SecureSocket::getSourcePortNumber() const {
	return sourcePortNumber;
}

void SecureSocket::setSourcePortNumber(std::string newSourcePortNumber) {
	sourcePortNumber = newSourcePortNumber;
}

std::string SecureSocket::getBuffer() const {
	return buffer;
}

void SecureSocket::setBuffer(std::string newBuffer) {
	buffer = newBuffer;
}

int SecureSocket::initSecureSocket() {
	LOG_DEBUG << "Attempting to create the socket.";
	setSocketDescriptor(socket(PF_INET, SOCK_STREAM, 0));
	LOG_DEBUG << "Made the socket.";
	if (getSocketDescriptor() < 0) {
		setValidity(false);
		LOG_ERROR << "The socket failed to create.";
		throw SecureSocketException(SOCK_CREATE_EXC);
	} else {
		LOG_DEBUG << "The socket was successfully created.";
		setValidity(true);
	}
	int force_reuse_socket_port__yes = 1;
	if (setsockopt(getSocketDescriptor(), SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes,
				   sizeof(force_reuse_socket_port__yes)) == -1) {
		setValidity(false);
		LOG_ERROR << "The socket couldn't be reused.";
		throw SecureSocketException(SOCK_REUSE_EXC);

	} else {
		LOG_DEBUG << "The socket is being used successfully.";
		setValidity(true);
	}
	return getSocketDescriptor();
}

int SecureSocket::destroySecureSocket() {
	int result = close(getSocketDescriptor());
	if (result < 0)
		throw SecureSocketException(SOCK_CLOSE_EXC, std::to_string(result));
	setValidity(false);
	return result;
}

std::string SecureSocket::getSourceAddrFromSockDesc() const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getsockname(getSocketDescriptor(), &tempSocketAddress, &tempLen);
	return charArray_to_string(inet_ntoa(((struct sockaddr_in *) &tempSocketAddress)->sin_addr));
}

std::string SecureSocket::getSourcePortFromSockDesc() const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getsockname(getSocketDescriptor(), &tempSocketAddress, &tempLen);
	return long_to_string(ntohs(((struct sockaddr_in *) &tempSocketAddress)->sin_port));
}

std::string SecureSocket::getTargetAddrFromSockDesc() const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getpeername(getSocketDescriptor(), &tempSocketAddress, &tempLen);
	std::string result = charArray_to_string(inet_ntoa(((struct sockaddr_in *) &tempSocketAddress)->sin_addr));
	return result;
}

std::string SecureSocket::getTargetPortFromSockDesc() const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getpeername(getSocketDescriptor(), &tempSocketAddress, &tempLen);
	std::string result = long_to_string(ntohs(((struct sockaddr_in *) &tempSocketAddress)->sin_port));
	return result;
}

std::string SecureSocket::getSourceAddrFromSockDesc(int s) const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getsockname(s, &tempSocketAddress, &tempLen);
	return charArray_to_string(inet_ntoa(((struct sockaddr_in *) &tempSocketAddress)->sin_addr));
}

std::string SecureSocket::getSourcePortFromSockDesc(int s) const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getsockname(s, &tempSocketAddress, &tempLen);
	return long_to_string(ntohs(((struct sockaddr_in *) &tempSocketAddress)->sin_port));
}

std::string SecureSocket::getTargetAddrFromSockDesc(int s) const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getpeername(s, &tempSocketAddress, &tempLen);
	std::string result = charArray_to_string(inet_ntoa(((struct sockaddr_in *) &tempSocketAddress)->sin_addr));
	return result;
}

std::string SecureSocket::getTargetPortFromSockDesc(int s) const {
	struct sockaddr tempSocketAddress;
	socklen_t tempLen = sizeof(tempSocketAddress);
	getpeername(s, &tempSocketAddress, &tempLen);
	std::string result = long_to_string(ntohs(((struct sockaddr_in *) &tempSocketAddress)->sin_port));
	return result;
}

// SecureSocket::~SecureSocket()
// {
//		LOG_DEBUG << "Calling the SecureSocket destructor.";
//     if(getValidity() == true)
//     {
//         LOG_INFO << "Closing socket #"
//             << getSocketDescriptor() << " assigned to "
//             << getTargetAddrFromSockDesc() << ":"
//             << getTargetPortFromSockDesc();
//         LOG_INFO << "getValidity: " << getValidity();
//         destroySecureSocket();
//         setValidity(false);
//     }
// }

int SecureDataSocket::getTimeoutSecValue() const {
	return timeoutSecValue;
}

void SecureDataSocket::setTimeoutSecValue(int newTimeoutSecValue) {
	timeoutSecValue = newTimeoutSecValue;
}

SecureDataSocket::SecureDataSocket() {
	setTimeoutSecValue(DEFAULT_TIMEOUT_VALUE);
	LOG_WARNING << "Calling the constructor SecureDataSocket() wasn't supposed to happen.";
}

// SecureDataSocket::SecureDataSocket(const SecureDataSocket &secureDataSocket)
// {
//     LOG_DEBUG << "Calling the copy constructor.";
//     setValidity(secureDataSocket.getValidity());
//     setSocketDescriptor(secureDataSocket.getSocketDescriptor());
//     setTargetIPAddress(secureDataSocket.getTargetIPAddress());
//     setTargetPortNumber(secureDataSocket.getTargetPortNumber());
//     setSourceIPAddress(secureDataSocket.getSourceIPAddress());
//     setSourcePortNumber(secureDataSocket.getSourcePortNumber());
//     setBuffer(secureDataSocket.getBuffer());
// }

SecureDataSocket::SecureDataSocket(int socketDescriptor) {
	setTimeoutSecValue(DEFAULT_TIMEOUT_VALUE);
	setValidity(true);
	setSocketDescriptor(socketDescriptor);
	setSourceIPAddress(getSourceAddrFromSockDesc(socketDescriptor));
	setSourcePortNumber(getSourcePortFromSockDesc(socketDescriptor));
	setTargetIPAddress(getTargetAddrFromSockDesc(socketDescriptor));
	setTargetPortNumber(getTargetPortFromSockDesc(socketDescriptor));
	setValidity(true);
}

SecureDataSocket::SecureDataSocket(std::string targetIPAddress, std::string targetPortNumber, int hostMode) {
	try {
		setTimeoutSecValue(DEFAULT_TIMEOUT_VALUE);
		initSecureSocket();
		setTargetIPAddress(targetIPAddress);
		setTargetPortNumber(targetPortNumber);
		connectSecureSocket();
		if (hostMode == HOST_MODE_CLIENT)
			performDHExchange_asClient();
		else if (hostMode == HOST_MODE_SERVER)
			performDHExchange_asServer();
		else
			throw SecureSocketException(DATA_SOCK_BADHOST);
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_EXC,
									charArray_to_string(e.what()) + "{" + std::to_string(e.errorCode) + "}\n");
	}
}

DHKeyContainer SecureDataSocket::getKeyContainer() const {
	return keyContainer;
}

int SecureDataSocket::connectSecureSocket() {
	int result;
	if (getValidity()) {
		struct sockaddr_in server_address;
		memset(&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons((uint16_t) string_to_long(getTargetPortNumber()));
		char *targetIPAddress_charArray = string_to_charArray(getTargetIPAddress());
		server_address.sin_addr.s_addr = inet_addr(targetIPAddress_charArray);
		free(targetIPAddress_charArray);

		if (isTimeout(getTimeoutSecValue(), getSocketDescriptor()) <= 0) {
			LOG_WARNING << "The server has timed out!";
			throw SecureSocketException(DATA_SOCK_CONNECT_TIMEOUT);
		}
		result = connect(getSocketDescriptor(), (struct sockaddr *) &server_address, sizeof(server_address));
		if (result < 0) {
			setValidity(false);
			LOG_ERROR << "Something went wrong with connect()";
			throw SecureSocketException(DATA_SOCK_CONN_EXC);
		} else {
			LOG_DEBUG << "Connect was successful!";
			setValidity(true);
		}
	} else {
		throw SecureSocketException(DATA_SOCK_INVALID_EXC);
	}
	return result;
}

int SecureDataSocket::isTimeout(int timeoutSec, int socket) {
	struct timeval tv;
	tv.tv_sec = timeoutSec;
	tv.tv_usec = 0;
	fd_set sock;
	FD_ZERO(&sock);
	FD_SET(socket, &sock);
	return select(socket + 1, &sock, NULL, NULL, &tv);
}

ssize_t SecureDataSocket::readSecureSocket() {
	ssize_t len;
	if (getValidity()) {
		setBuffer("");
		char buffer_char[256];
		bzero(buffer_char, 256);
		std::string temp_str = "";

		//Get to know the size of the string to receive.
		len = read(getSocketDescriptor(), buffer_char, 16);
		if (len <= 0) {
			setValidity(false);
			LOG_WARNING << "Perhaps, the client was disconnected forcefully by the server?";
			throw SecureSocketException(DATA_SOCK_READ_EMPTY_EXC);
		}
		long sizeOfIncomingMessage = string_to_long(buffer_char);
		long numberOfReadBytes = 0;
		size_t bufferReceiveSize = 255;
		while (numberOfReadBytes < sizeOfIncomingMessage) {
			bzero(buffer_char, 256);
			if (isTimeout(getTimeoutSecValue(), getSocketDescriptor()) <= 0) {
				LOG_WARNING << "The server has timed out!";
				throw SecureSocketException(DATA_SOCK_READ_TIMEOUT);
			}
			len = read(getSocketDescriptor(), buffer_char, bufferReceiveSize);
			if (len <= 0) {
				break;
			}
			temp_str += charArray_to_string(buffer_char);
			numberOfReadBytes += len;
			// LOG_TRACE << "Read byte count: " << (len) << ". temp_str.size():" << temp_str.size();
		}
		if (temp_str.size() <= 0) {
			setValidity(false);
			LOG_WARNING << "Perhaps, the client was disconnected forcefully by the server?";
			throw SecureSocketException(DATA_SOCK_READ_EMPTY_EXC);
		}
		setBuffer(temp_str);
	} else {
		LOG_ERROR << "While trying to read, the socket was invalid.";
		throw SecureSocketException(DATA_SOCK_INVALID_EXC);
	}
	return len;
}

ssize_t SecureDataSocket::writeSecureSocket() {
	ssize_t len;
	//Send the length of the message.
	len = write(getSocketDescriptor(), string_to_charArray(std::to_string(getBuffer().length())), 16);

	if (getValidity()) {
		if (getBuffer().length() <= 0)
			throw SecureSocketException(DATA_SOCK_WRITE_EMPTYBUFFER_EXC, "The buffer is empty.");
		unsigned long bufferSendSize = 255;
		for (unsigned i = 0; i < getBuffer().length(); i += bufferSendSize) {
			char *buffer_char = string_to_charArray(getBuffer().substr(i, bufferSendSize));
			len = write(getSocketDescriptor(), buffer_char, strlen(buffer_char));
			// sleep(7); //Just for testing the timeout on the reading side.
			if (len <= 0) {
				setValidity(false);
				throw SecureSocketException(DATA_SOCK_WRITE_EMPTY_EXC, "Perhaps, the server went offline?");
			}
			// LOG_DEBUG << "Sent byte count: " << (len);
			free(buffer_char);
		}
		// LOG_DEBUG << "Out of the for-loop.";
	} else {
		throw SecureSocketException(DATA_SOCK_INVALID_EXC, "During writeSecureSocket(), getValidity() was false.");
	}
	return len;
}

void SecureDataSocket::setAndEncryptBuffer(std::string message) {
	if (!getKeyContainer().getValidity())
		throw SecureSocketException(DH_CONT_INVALID_EXC,
									"The key container was found invalid, while trying to encrypt the buffer.");
/*
    if(message.length() <= 0)
        throw SecureDataSocketIOException(*this, "The message length to write is zero.");
*/
	try {
		setBuffer(encrypt(message, (char) string_to_long(getKeyContainer().getSharedSecret())));
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_ENCR_EXC,
									"Could not set and encrypt the buffer.\n" + charArray_to_string(e.what()) + "{" +
									std::to_string(e.errorCode) + "}\n");
	}
}

std::string SecureDataSocket::getAndDecryptBuffer() const {
	if (!getKeyContainer().getValidity())
		throw SecureSocketException(DH_CONT_INVALID_EXC,
									"The key container was found invalid, while trying to decrypt the buffer.");
	try {
		/*
		if(getBuffer().length() <= 0)
			throw SecureDataSocketIOException(*this, "The read message length was zero.");
		*/
		return (decrypt(getBuffer(), (char) string_to_long(getKeyContainer().getSharedSecret())));
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_DECR_EXC, "Could not get and decrypt the buffer.");
	}
}

void SecureDataSocket::encryptAndSend(std::string message) {
	try {
		setAndEncryptBuffer(message);
		writeSecureSocket();
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_ENCRSEND_EXC,
									"Could not encrypt and send the message.\n" + charArray_to_string(e.what()) + "{" +
									std::to_string(e.errorCode) + "}\n");
	}
}

/*
void SecureDataSocket::encryptAndSend() {
	try {
		setAndEncryptBuffer(getBuffer());
		writeSecureSocket();
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_ENCRSEND_EXC, "Could not encrypt and send the existing buffer.\n" +
															charArray_to_string(e.what()) + "{" +
															std::to_string(e.errorCode) + "}\n");
	}
}
*/
std::string SecureDataSocket::receiveAndDecrypt() {
	try {
		readSecureSocket();
		std::string message = getAndDecryptBuffer();
		return message;
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DATA_SOCK_DECRRECV_EXC,
									"Could not receive and decrypt the message.\n" + charArray_to_string(e.what()) +
									"{" + std::to_string(e.errorCode) + "}\n");
	}
}

int SecureDataSocket::performDHExchange_asClient() {
	try {
		if (this->getValidity()) {
			//First, hello to server.
			this->setBuffer("hello_exchangeDH");
			this->writeSecureSocket();
			if (!this->getValidity()) {
				throw SecureSocketException(DH_HELLOSEND_EXC, "Hello transmission failed.");
			}
			bool passFlag;
			do {
				//Second, receive the server's primes and public key.
				//Expected format: <primeP#primeQ@serverPublic>
				this->readSecureSocket();
				if (!this->getValidity()) {
					throw SecureSocketException(DH_KEYRECV_EXC, "Failed to read keys and public key from server.");
				}
				LOG_DEBUG << "Read the primes and the server public key.";
				//Format checking.
				int index = 0;
				if (this->getBuffer()[index] != '<') return -1;
				while (isdigit(this->getBuffer()[++index]));
				if (this->getBuffer()[index] != '#') return -1;
				while (isdigit(this->getBuffer()[++index]));
				if (this->getBuffer()[index] != '@') return -1;
				while (isdigit(this->getBuffer()[++index]));
				if (this->getBuffer()[index] != '>') return -1;

				std::vector<std::string> t = Tokenize(this->getBuffer(), "@#<>");
				this->keyContainer.setPrimeP(string_to_long(t[0]));
				this->keyContainer.setPrimeQ(string_to_long(t[1]));
				this->keyContainer.setRemotePublic(t[2]);

				//Third, send the client's public key.
				this->keyContainer.setLocalPrivate(long_to_string(custom_rand(100)));
				this->keyContainer.setLocalPublic(long_to_string(crtModulus(this->keyContainer.getPrimeQ(),
																			string_to_long(
																					this->keyContainer.getLocalPrivate()),
																			this->keyContainer.getPrimeP())));
				this->setBuffer(this->keyContainer.getLocalPublic());
				this->writeSecureSocket();
				if (!this->getValidity()) {
					throw SecureSocketException(DH_KEYSEND_EXC, "Failed to send public key to server.");
				}
				LOG_DEBUG << "Sent the client public key.";
				if (!(this->keyContainer.isGoodPrimeQ() &&
					  this->keyContainer.isGoodLocalPublic() &&
					  this->keyContainer.isGoodLocalPrivate() &&
					  this->getValidity())) {
					this->keyContainer.setValidity(false);
					continue;
				}

				//Finally, calculate the shared secret.
				this->keyContainer.setSharedSecret(long_to_string(
						crtModulus(string_to_long(this->keyContainer.getRemotePublic()),
								   string_to_long(this->keyContainer.getLocalPrivate()),
								   (this->keyContainer).getPrimeP()
						)
												   )
				);
				if (!this->keyContainer.isGoodSharedSecret()) {
					this->keyContainer.setValidity(false);
					continue;
				}
				LOG_DEBUG << "All client checks passed!";
				passFlag = true;
				this->keyContainer.setValidity(true);
			} while (!passFlag);
			return 1;
		} else {
			throw SecureSocketException(DATA_SOCK_INVALID_EXC,
										"During performDHExchange_asClient(), getValidity() was false.");
		}
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DH_PROC_EXC,
									"DH key exchanged failed for the client.\n" + charArray_to_string(e.what()) + "{" +
									std::to_string(e.errorCode) + "}\n");
	}
}

int SecureDataSocket::performDHExchange_asServer() {
	try {
		if (this->getValidity()) {
			//First, hello from client.
			LOG_DEBUG << "Waiting for a hello_exchangeDH";
			this->readSecureSocket();
			if (!this->getValidity()) {
				throw SecureSocketException(DATA_SOCK_INVALID_EXC, "Could not receive message.");
			}
			if (this->getBuffer() != "hello_exchangeDH") {
				this->setValidity(false);
				throw SecureSocketException(DH_HELLORECV_EXC, "Hello reception failed.");
			}
			LOG_DEBUG << "Found a hello_exchangeDH";
			bool passFlag;
			do {
				//Second, send the server's primes and public key.
				//Predefined format: <primeP#primeQ@serverPublic>
				while (true) {
					this->keyContainer.setPrimeP(nextPrime(custom_rand(100)));
					this->keyContainer.setPrimeQ(custom_rand(this->keyContainer.getPrimeP()));
					this->keyContainer.setLocalPrivate(long_to_string(custom_rand(100)));
					this->keyContainer.setLocalPublic(long_to_string(crtModulus(this->keyContainer.getPrimeQ(),
																				string_to_long(
																						this->keyContainer.getLocalPrivate()),
																				this->keyContainer.getPrimeP())));
					if (this->keyContainer.isGoodPrimeQ() &&
						this->keyContainer.isGoodPrimeP() &&
						this->keyContainer.isGoodLocalPublic() &&
						this->keyContainer.isGoodLocalPrivate() &&
						this->getValidity()) {
						break;
					} else {
						LOG_DEBUG << "Restarting the server key calculations.";
					}
				}

				LOG_DEBUG << "Calculated the primes and the server key pair.";

				this->setBuffer("<" +
								long_to_string(this->keyContainer.getPrimeP()) +
								"#" +
								long_to_string(this->keyContainer.getPrimeQ()) +
								"@" +
								this->keyContainer.getLocalPublic() +
								">");
				this->writeSecureSocket();
				if (!this->getValidity()) {
					throw SecureSocketException(DATA_SOCK_INVALID_EXC,
												"Could not send primes and public key to client.");
				}
				LOG_DEBUG << "Sent the primes and the server key pair.";
				//Third, receive the client's public key.
				this->readSecureSocket();
				if (!this->getValidity()) {
					throw SecureSocketException(DATA_SOCK_INVALID_EXC, "Could not read client public key.");
				}
				LOG_DEBUG << "Read the client's public key.";
				this->keyContainer.setRemotePublic(this->getBuffer());

				if (!(this->keyContainer.isGoodPrimeQ() &&
					  this->keyContainer.isGoodPrimeP() &&
					  this->keyContainer.isGoodRemotePublic() &&
					  this->keyContainer.isGoodLocalPublic() &&
					  this->keyContainer.isGoodLocalPrivate() &&
					  this->getValidity())) {
					this->keyContainer.setValidity(false);
					continue;
				}

				//Finally, calculate the shared secret.
				this->keyContainer.setSharedSecret(long_to_string(
						crtModulus(string_to_long(this->keyContainer.getRemotePublic()),
								   string_to_long(this->keyContainer.getLocalPrivate()),
								   this->keyContainer.getPrimeP())));
				if (!this->keyContainer.isGoodSharedSecret()) {
					this->keyContainer.setValidity(false);
					continue;
				}
				LOG_DEBUG << "All server checks passed!";
				passFlag = true;
				this->keyContainer.setValidity(true);
			} while (!passFlag);
			return 1;
		} else {
			throw SecureSocketException(DATA_SOCK_INVALID_EXC,
										"During performDHExchange_asServer(), getValidity() was false.");
		}
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(DH_PROC_EXC,
									"DH key exchanged failed for the server.\n" + charArray_to_string(e.what()) + "{" +
									std::to_string(e.errorCode) + "}\n");
	}
}

const int SecureListenSocket::queueSize = 16;

SecureListenSocket::SecureListenSocket() {
	setValidity(false);
	LOG_WARNING << "Created an empty SecureListenSocket()";
} //Is this safe? MARK
SecureListenSocket::SecureListenSocket(std::string serverIPAddress, std::string serverPortNumber) {
	try {
		initSecureSocket();
		setSourceIPAddress(serverIPAddress);
		setSourcePortNumber(serverPortNumber);
		bindSecureSocket();
		listenSecureSocket();
	}
	catch (SecureSocketException &e) {
		throw SecureSocketException(LISTEN_SOCK_EXC,
									"Could not activate the listen socket.\n" + charArray_to_string(e.what()) + "{" +
									std::to_string(e.errorCode) + "}\n");
	}
}

int SecureListenSocket::bindSecureSocket() {
	int result;
	if (getValidity()) {
		struct sockaddr_in serverAddress;
		memset(&serverAddress, 0, sizeof(serverAddress));
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(string_to_charArray(getSourceIPAddress()));
		serverAddress.sin_port = htons((uint16_t) (string_to_long(getSourcePortNumber())));
		result = bind(getSocketDescriptor(), (struct sockaddr *) &serverAddress, sizeof(serverAddress));
		if (result < 0)
			throw SecureSocketException(LISTEN_SOCK_BIND_EXC, "Could not bind the secure socket.");
	} else {
		throw SecureSocketException(LISTEN_SOCK_INVALID_EXC, "During bindSecureSocket(), getValidity() was false.");
	}
	return result;
}

int SecureListenSocket::listenSecureSocket() {
	LOG_INFO << "Creating a new listen socket.";
	int result;
	if (getValidity()) {
		result = listen(getSocketDescriptor(), queueSize);
		if (result < 0)
			throw SecureSocketException(LISTEN_SOCK_LISTEN_EXC, "Could not make the secure socket to listen.");
	} else {
		throw SecureSocketException(LISTEN_SOCK_INVALID_EXC, "During listenSecureSocket(), getValidity() was false.");
	}
	return result;
}

SecureDataSocket SecureListenSocket::acceptSecureSocket() {
	if (getValidity()) {
		struct sockaddr_in clientAddress;
		socklen_t clientAddressLength = sizeof(clientAddress);
		int s = accept(getSocketDescriptor(), (struct sockaddr *) &clientAddress, &clientAddressLength);
		if (s < 0)
			throw SecureSocketException(LISTEN_SOCK_ACCEPT_EXC,
										"Accepted a bad connection, or failed to accept altogether.");
		LOG_TRACE << "MarkAlpha1";
		LOG_DEBUG << "Creating a new data socket.";
		SecureDataSocket newSecureDataSocket(s);
		newSecureDataSocket.performDHExchange_asServer();
		LOG_DEBUG << "Created a new valid data socket.";
		return newSecureDataSocket;
	} else {
		throw SecureSocketException(LISTEN_SOCK_INVALID_EXC, "During acceptSecureSocket(), getValidity() was false.");
	}
}
