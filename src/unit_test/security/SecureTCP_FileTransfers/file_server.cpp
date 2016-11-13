#include "security/securefiletransfer.hpp"
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