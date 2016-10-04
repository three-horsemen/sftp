#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <exception>

#include <boost/thread.hpp>

#include <sqlite3.h>

#include <shared/SignalHandler.hpp>
#include <shared/logger.hpp>
#include <security/securesocket.hpp>

namespace sftp {

namespace sync {

using namespace std;

void customthread(SecureDataSocket acceptedSecureDataSocket) {
	//acceptedSecureDataSocket.performDHExchange_asServer();
	if (acceptedSecureDataSocket.getValidity() == true) {
		cout << "Diffie-Hellman key exchange with client "
				<< acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
				<< acceptedSecureDataSocket.getTargetPortFromSockDesc()
				<< " successful!" << endl;
		do {
			acceptedSecureDataSocket.readSecureSocket();
			if (acceptedSecureDataSocket.getValidity() == false)
				break;
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
					<< acceptedSecureDataSocket.getTargetPortFromSockDesc()
					<< " <--$ " << acceptedSecureDataSocket.getBuffer() << endl;
			acceptedSecureDataSocket.writeSecureSocket();
			if (acceptedSecureDataSocket.getValidity() == false)
				break;
			cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
					<< acceptedSecureDataSocket.getTargetPortFromSockDesc()
					<< " -->$ " << acceptedSecureDataSocket.getBuffer() << endl;
		} while (acceptedSecureDataSocket.getBuffer() != "quit"
				&& acceptedSecureDataSocket.getValidity() == true);
	}
	cout << "Closing the connection from "
			<< acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
			<< acceptedSecureDataSocket.getTargetPortFromSockDesc() << endl;
	acceptedSecureDataSocket.destroySecureSocket();
}

class TimelineServer {
private:
	SecureListenSocket serverSecureListenSocket;
	SignalHandler sh;
public:
	TimelineServer(int portNo) :
			sh() {
		//sh.setupSignalHandlers();
		serverSecureListenSocket.initSecureSocket();
		serverSecureListenSocket.setSourceIPAddress("127.0.0.1");
		serverSecureListenSocket.setSourcePortNumber(int_to_string(portNo));
		serverSecureListenSocket.bindSecureSocket();
		serverSecureListenSocket.listenSecureSocket();
	}

	void acceptNewConnections() {
		SecureDataSocket serverSecureDataSocket;
		if (serverSecureListenSocket.getValidity() == false) {
			cout << "Something went wrong!" << endl;
			return; // TODO Throw Exception
		} else {
			cout << "Server is ready to accept connections from clients."
					<< endl;
		}
		while (!sh.gotExitSignal()) {
			cout << "Waiting to accept a connection..." << endl;
			serverSecureDataSocket =
					serverSecureListenSocket.acceptSecureSocket();
			boost::thread t { customthread, serverSecureDataSocket };
			//t.join();
		}
		cout << "Server program ending." << endl;
	}

	virtual ~TimelineServer() {
		cout <<"Closing secure listen socket";
		serverSecureListenSocket.destroySecureSocket();
	}
};

}
;
/* sync namespace */

}
;

using namespace sftp::sync;

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Arguments: portNumber\n");
		exit(1);
	}
	int portNo = atoi(argv[1]);
	TimelineServer ts(portNo);
	ts.acceptNewConnections();
	return 0;
}
