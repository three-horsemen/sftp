//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"
#include <boost/thread.hpp>
#include <iostream>
using namespace std;

void customthread(SecureDataSocket acceptedSecureDataSocket)
{
	acceptedSecureDataSocket.performDHExchange_asServer();
	if(acceptedSecureDataSocket.getValidity() == true)
	{
		cout << "Diffie-Hellman key exchange with client " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " successful!" << endl;
		do
		{
			acceptedSecureDataSocket.readSecureSocket();
			if(acceptedSecureDataSocket.getValidity() == false) break;
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " <--$ " << acceptedSecureDataSocket.getBuffer() << endl;
			acceptedSecureDataSocket.writeSecureSocket();
			if(acceptedSecureDataSocket.getValidity() == false) break;
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " -->$ " << acceptedSecureDataSocket.getBuffer() << endl;
		} while(acceptedSecureDataSocket.getBuffer() != "quit" && acceptedSecureDataSocket.getValidity() == true);
	}
	cout << "Closing the connection from " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << endl;
	acceptedSecureDataSocket.destroySecureSocket();
}

int main()
{
	SecureListenSocket serverSecureListenSocket;
	serverSecureListenSocket.initSecureSocket();
	serverSecureListenSocket.setSourceIPAddress("127.0.0.1");
	serverSecureListenSocket.setSourcePortNumber("8889");
	serverSecureListenSocket.bindSecureSocket();
	serverSecureListenSocket.listenSecureSocket();
	SecureDataSocket serverSecureDataSocket;
	if(serverSecureListenSocket.getValidity() == false)
	{
		cout << "Something went wrong!" << endl;
		return -1;
	}
	else
	{
		cout << "Server is ready to accept connections from clients." << endl;
	}
	while(true)
	{
		cout << "Waiting to accept a connection..." << endl;
		serverSecureDataSocket = serverSecureListenSocket.acceptSecureSocket();
		boost::thread t{customthread, serverSecureDataSocket};
	    //t.join();
	}
	cout << "Server program ending." << endl;
	return 0;
}
