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
	clientSecureDataSocket.performDHExchange_asClient();
	std::string buffer;
	while(buffer!="quit" && clientSecureDataSocket.getValidity() == true)
	{
		std::cout << clientSecureDataSocket.getTargetAddrFromSockDesc() << ":" << clientSecureDataSocket.getTargetPortFromSockDesc() << " (Client) >>> " << clientSecureDataSocket.getSourceAddrFromSockDesc() << ":" << clientSecureDataSocket.getSourcePortFromSockDesc() << ": ";
		std::getline(std::cin, buffer); //This form accepts whitespaces,
		clientSecureDataSocket.setBuffer(encrypt(buffer, string_to_int(clientSecureDataSocket.getKeyContainer().getSharedSecret())));
		clientSecureDataSocket.writeSecureSocket();
		clientSecureDataSocket.setBuffer("");
		clientSecureDataSocket.readSecureSocket();
		std::cout << clientSecureDataSocket.getTargetAddrFromSockDesc() << ":" << clientSecureDataSocket.getTargetPortFromSockDesc() << " (Client) <<< " << clientSecureDataSocket.getSourceAddrFromSockDesc() << ":" << clientSecureDataSocket.getSourcePortFromSockDesc() << ": " << decrypt(clientSecureDataSocket.getBuffer(), string_to_int(clientSecureDataSocket.getKeyContainer().getSharedSecret())) << std::endl;
	}
	clientSecureDataSocket.destroySecureSocket();
	std::cout << "Client program ending." << std::endl;
	return 0;
}
