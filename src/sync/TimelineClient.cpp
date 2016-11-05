//Client program to keep talking to a server until a "quit" message is sent.
#include "security/securesocket.hpp"

#include <iostream>

#include <database/UserManager.hpp>

using namespace std;
using namespace sftp::db;

int main() {
	{
		SecureDataSocket clientSecureDataSocket("127.0.0.1", "8081",
		HOST_MODE_CLIENT);

		try {
			runtime_error unknownResponseException(
					string("Unknown server response"));

			string buffer;

			buffer = clientSecureDataSocket.receiveAndDecrypt();
			if (buffer != UserManager::USERNAME)
				throw unknownResponseException;
			string username = "";
			cout << "Username: ";
			getline(cin, username);
			clientSecureDataSocket.encryptAndSend(username);

			buffer = clientSecureDataSocket.receiveAndDecrypt();
			if (buffer != UserManager::PASSWORD)
				throw unknownResponseException;
			string password = "";
			cout << "Password: ";
			getline(cin, password);
			clientSecureDataSocket.encryptAndSend(password);
			buffer = clientSecureDataSocket.receiveAndDecrypt();
			if (buffer == UserManager::CREDENTIALS_VALID)
				cout << "Login success\n";
			else
				cout << "Invalid credentials\n";
		} catch (exception &e) {
			cout << e.what() << endl;
		}

		string buffer = "";
		while (buffer != UserManager::LOGOUT
				&& clientSecureDataSocket.getValidity() == true) {

		}
		clientSecureDataSocket.destroySecureSocket();
	}
	cout << "Client program ending." << endl;
	return 0;
}
