
#include "security/securesocket.hpp"
#include <iostream>
using namespace std;
int main()
{
	SecureListenSocket serverSecureListenSocket;
	serverSecureListenSocket.initSecureSocket();
	string buffer;
	serverSecureListenSocket.setSourceIPAddress("127.0.0.1");
	serverSecureListenSocket.setSourcePortNumber("8088");
	if((serverSecureListenSocket.getValidity()) == false)
	{
		printf("ERROR IN LISTEN SOCKET\n");
		return 0;
	}
	if((serverSecureListenSocket.bindSecureSocket())<0)
	{
		printf("ERROR IN BINDING\n");
		return 0;
	}
	if(serverSecureListenSocket.listenSecureSocket()<0)
	{
		printf("ERROR LISTENING \n");
		return 0;
	}
	SecureDataSocket acceptedClientDataSocket;
	while(fork() != 0)
	{
		printf("Hello World\n");
		acceptedClientDataSocket = serverSecureListenSocket.acceptSecureSocket();
		if(acceptedClientDataSocket.getValidity() == false)
		{
			printf("ERROR ACCEPTING CONNECTION \n");
			return 0;
		}
		acceptedClientDataSocket.readSecureSocket();
		cout << "Server <--: " << acceptedClientDataSocket.getBuffer() << endl;
		acceptedClientDataSocket.writeSecureSocket();
		cout << "Server -->: " << acceptedClientDataSocket.getBuffer() << endl;
		acceptedClientDataSocket.destroySecureSocket();
		exit(0);
	}
	serverSecureListenSocket.destroySecureSocket();
	return 0;
}
