//Client program to keep talking to a server until a "quit" message is sent.
#include "security/securesocket.hpp"
#include <iostream>

int main()
{
	SecureDataSocket clientSecureDataSocket;
	clientSecureDataSocket.initSecureSocket();
	clientSecureDataSocket.setTargetIPAddress("127.0.0.1");
	clientSecureDataSocket.setTargetPortNumber("8889");
	clientSecureDataSocket.connectSecureSocket();
	std::string buffer;
	while(buffer!="quit" && clientSecureDataSocket.getValidity() == true)
	{
		std::cout << "Client -->: ";
		std::getline(std::cin, buffer); //This form accepts whitespaces,
		clientSecureDataSocket.setBuffer(buffer);
		clientSecureDataSocket.writeSecureSocket();
		clientSecureDataSocket.setBuffer("");
		clientSecureDataSocket.readSecureSocket();
		std::cout << "Client <--: " << clientSecureDataSocket.getBuffer() << std::endl;
	}
	clientSecureDataSocket.destroySecureSocket();
	std::cout << "Client program ending." << std::endl;
	return 0;
}
