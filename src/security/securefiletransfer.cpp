//
// Created by Soorya Annadurai on 14/11/16.
//

#include "security/securefiletransfer.hpp"

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
