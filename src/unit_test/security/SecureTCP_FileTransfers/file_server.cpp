#include <fcntl.h>
#include <iostream>
#include "security/securesocket.hpp"

int receiveFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string targetFilePath) {
	std::string bufferString;
	FILE *fileHandler;
	unsigned long long lengthOfFileToReceive, numberOfReceivedBytes, currentlyReadByteCount;
	fileHandler = fopen(targetFilePath.c_str(), "w");
	if (fileHandler == NULL) {
		LOG_ERROR << "Error with opening the file.";
		return -1;
	}
	try {
		//Receive the size of the file to receive.
		bufferString = secureDataSocket.receiveAndDecrypt();
		lengthOfFileToReceive = string_to_unsigned_long_long(bufferString);
		secureDataSocket.encryptAndSend(bufferString);
		numberOfReceivedBytes = 0;
		while (secureDataSocket.getValidity() && numberOfReceivedBytes < lengthOfFileToReceive) {
			bufferString = secureDataSocket.receiveAndDecrypt();
			if ((currentlyReadByteCount = fwrite(bufferString.c_str(), sizeof(char), bufferString.size(),
												 fileHandler)) == 0) {
				LOG_ERROR << "Error with writing to the destination file.";
				return -2;
			}
			numberOfReceivedBytes += currentlyReadByteCount;
		}
	}
	catch (std::exception &e) {
		LOG_ERROR << "Exception caught in receiveFileOverSecureDataSocket: " << e.what();
		throw e;
	}
	fclose(fileHandler);
	return 0;
}

int main() {
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "8081");
	if (!serverSecureListenSocket.getValidity()) {
		std::cout << "Something went wrong!" << std::endl;
		return -1;
	}
	SecureDataSocket serverSecureDataSocket = serverSecureListenSocket.acceptSecureSocket();
	receiveFileOverSecureDataSocket(serverSecureDataSocket, "serverSide.txt");
	serverSecureListenSocket.destroySecureSocket();
	return 0;
}