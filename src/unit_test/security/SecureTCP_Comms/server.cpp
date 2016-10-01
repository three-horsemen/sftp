//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
#include "security/securesocket.hpp"
#include <boost/thread.hpp>
#include <iostream>
using namespace std;

void customthread(SecureDataSocket acceptedSecureDataSocket)
{
	do
	{
		acceptedSecureDataSocket.readSecureSocket();
		cout << "Received: " << acceptedSecureDataSocket.getBuffer() << endl;
		acceptedSecureDataSocket.writeSecureSocket();
		cout << "Finished write attempt." << endl;
	} while(acceptedSecureDataSocket.getBuffer() != "quit" && acceptedSecureDataSocket.getValidity() == true);
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
