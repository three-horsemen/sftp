#include <fcntl.h>
#include <iostream>
#include "security/securesocket.hpp"

int sendFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string sourceFilePath) {
	char buffer[secureDataSocket.getBufferSendSize() + 1];
	FILE *fileHandler;
	ssize_t read_return;
	std::string bufferString;
	fileHandler = fopen(sourceFilePath.c_str(), "r");
	long int fileSize;
	if (fileHandler == NULL) {
		LOG_ERROR << "Error with opening the file.";
		return -1;
	}
	try {
		fseek(fileHandler, 0, SEEK_END);
		fileSize = ftell(fileHandler);
		secureDataSocket.encryptAndSend(std::to_string(fileSize));
		fseek(fileHandler, 0, SEEK_SET);
		bufferString = secureDataSocket.receiveAndDecrypt();
		if (bufferString != std::to_string(fileSize))
			LOG_ERROR << "The echo was incorrect.";
		while (secureDataSocket.getValidity()) {
			read_return = fread(buffer, sizeof(char), secureDataSocket.getBufferSendSize(), fileHandler);
			if (read_return == 0)
				break;
			secureDataSocket.encryptAndSend(std::string(buffer, (unsigned long) read_return));
		}
	}
	catch (std::exception &e) {
		LOG_ERROR << "Exception caught in sendFileOverSecureDataSocket: " << e.what();
		throw e;
	}
	fclose(fileHandler);
	return 0;
}

int main() {
	std::string sourceFileName;
	SecureDataSocket clientSecureDataSocket("127.0.0.1", "8081", HOST_MODE_CLIENT);
	std::cout << "Which file to send across the network? ";
	std::cin >> sourceFileName;
	sendFileOverSecureDataSocket(clientSecureDataSocket, sourceFileName);
	clientSecureDataSocket.destroySecureSocket();
	return 0;
}