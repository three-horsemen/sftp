#include "security/securesocket.hpp"
#include <iostream>
using namespace std;

int main()
{
	SecureDataSocket clientSecureDataSocket;
	/*
	clientSecureDataSocket.initSecureSocket();
	clientSecureDataSocket.setTargetIPAddress("127.0.0.1");
	clientSecureDataSocket.setTargetPortNumber("8088");
	*/
	string buffer;
	while(buffer!="quit")
	{

		clientSecureDataSocket.initSecureSocket();
		clientSecureDataSocket.setTargetIPAddress("127.0.0.1");
		clientSecureDataSocket.setTargetPortNumber("8088");

		clientSecureDataSocket.connectSecureSocket();
		cout << "Client -->: ";
		cin >> buffer;
		clientSecureDataSocket.setBuffer(buffer);
		clientSecureDataSocket.writeSecureSocket();
		clientSecureDataSocket.setBuffer("");
		clientSecureDataSocket.readSecureSocket();
		cout << "Client <--: " << clientSecureDataSocket.getBuffer() << endl;

		clientSecureDataSocket.destroySecureSocket();
	}
	//clientSecureDataSocket.destroySecureSocket();
	return 0;
}
