#include "security/securefiletransfer.hpp"

int main() {
	std::string sourceFileName;
	SecureDataSocket clientSecureDataSocket("127.0.0.1", "8081", HOST_MODE_CLIENT);
	std::cout << "Which file to send across the network? ";
	std::cin >> sourceFileName;
	sendFileOverSecureDataSocket(clientSecureDataSocket, sourceFileName);
	clientSecureDataSocket.destroySecureSocket();
	return 0;
}