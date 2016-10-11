//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"
#include <boost/thread.hpp>
#include <iostream>
using namespace std;

void customthread(SecureDataSocket acceptedSecureDataSocket)
{
	cout << "Negotiating with new client." << endl;
	//acceptedSecureDataSocket.performDHExchange_asServer();
	if(acceptedSecureDataSocket.getValidity() == true)
	{
		cout << "Diffie-Hellman key exchange with client " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " successful!" << endl;
		do
		{
			std::string message = acceptedSecureDataSocket.decryptAndReceiveSecureSocket();
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " <--$ ";
			cout << message << " $$$Mesg length: " << message.length() << " &&&Mesg size: " << message.size() << endl;
			acceptedSecureDataSocket.encryptAndSendSecureSocket(message);
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " -->$ ";
			cout << acceptedSecureDataSocket.getBuffer() << endl;
		} while(acceptedSecureDataSocket.getAndDecryptBuffer() != "quit" && acceptedSecureDataSocket.getValidity() == true);
	}
	cout << "Closing the connection from " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << endl;
	acceptedSecureDataSocket.destroySecureSocket();
}

int main()
{
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "8081");
	if(serverSecureListenSocket.getValidity() == false)
	{
		cout << "Something went wrong!" << endl;
		return -1;
	}
	while(true)
	{
		cout << "Waiting to accept a connection..." << endl;
		boost::thread t{customthread, serverSecureListenSocket.acceptSecureSocket()};
	    //t.join();
	}
	cout << "Server program ending." << endl;
	return 0;
}
