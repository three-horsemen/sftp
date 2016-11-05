//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"

#include <boost/thread.hpp>

#include <iostream>

#include <database/DbManager.hpp>
#include <database/UserManager.hpp>

namespace sftp {

using namespace std;
using namespace db;

void timelineServerThread(SecureDataSocket acceptedSecureDataSocket) {
	cout << "Negotiating with new client." << endl;
	//acceptedSecureDataSocket.performDHExchange_asServer();
	if (acceptedSecureDataSocket.getValidity() == true) {
		acceptedSecureDataSocket.encryptAndSend(UserManager::USERNAME);
		string username = acceptedSecureDataSocket.receiveAndDecrypt();
		acceptedSecureDataSocket.encryptAndSend("PASSWORD");
		string password = acceptedSecureDataSocket.receiveAndDecrypt();

		try {
			bool isAuthentic =
					DbManager::getDb()->getUserManager().isAuthenticationValid(
							username, password);
			if (isAuthentic) {
				acceptedSecureDataSocket.encryptAndSend("VALID");
			} else {
				acceptedSecureDataSocket.encryptAndSend("INVALID");
			}
		} catch (SQLiteException &e) {
			acceptedSecureDataSocket.encryptAndSend("INVALID");
		}
		do {
		} while (acceptedSecureDataSocket.getAndDecryptBuffer()
				!= UserManager::LOGOUT
				&& acceptedSecureDataSocket.getValidity() == true);
	}
	acceptedSecureDataSocket.destroySecureSocket();
}

}

int main() {
	sftp::DbManager::initializeStaticDbManager("sftp.db");
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "8081");
	if (serverSecureListenSocket.getValidity() == false) {
		cout << "Something went wrong!" << endl;
		return -1;
	}
	while (true) {
		cout << "Waiting to accept a connection..." << endl;
		boost::thread t { sftp::timelineServerThread,
				serverSecureListenSocket.acceptSecureSocket() };
		//t.join();
	}
	cout << "Server program ending." << endl;
	return 0;
}
