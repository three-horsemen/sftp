//Client program to keep talking to a server until a "quit" message is sent.
#include "security/securesocket.hpp"
#include <iostream>

int main()
{
	try
	{
		SecureDataSocket clientSecureDataSocket("127.0.0.1", "8081", HOST_MODE_CLIENT);
		std::string buffer;
		while(buffer!="quit" && clientSecureDataSocket.getValidity() == true)
		{
			std::cout << clientSecureDataSocket.getSourceAddrFromSockDesc() << ":" << clientSecureDataSocket.getSourcePortFromSockDesc() << " (Client) >>> " << clientSecureDataSocket.getTargetAddrFromSockDesc() << ":" << clientSecureDataSocket.getTargetPortFromSockDesc() << ": ";
			std::getline(std::cin, buffer); //This form accepts whitespaces,
			clientSecureDataSocket.encryptAndSend(buffer);
			buffer = clientSecureDataSocket.receiveAndDecrypt();
			std::cout << clientSecureDataSocket.getSourceAddrFromSockDesc() << ":" << clientSecureDataSocket.getSourcePortFromSockDesc() << " (Client) <<< " << clientSecureDataSocket.getTargetAddrFromSockDesc() << ":" << clientSecureDataSocket.getTargetPortFromSockDesc() << ": ";
			std::cout << clientSecureDataSocket.getAndDecryptBuffer() << std::endl; //The buffer is still in an encrypted state.
		}
		clientSecureDataSocket.destroySecureSocket();
	}
	catch(SecureSocketException &e)
	{
		cout << e.what();
	}
	std::cout << "Client program ending." << std::endl;
	return 0;
}
