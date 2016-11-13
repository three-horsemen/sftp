//Client program to keep talking to a server until a "quit" message is sent.
#include "security/securesocket.hpp"

#include <database/UserManager.hpp>
#include <database/TimelineManager.hpp>

using namespace std;
using namespace sftp::db;

int main() {
	SecureDataSocket clientSocket("127.0.0.1", "8081",
								  HOST_MODE_CLIENT);

	string buffer;
	try {

		buffer = clientSocket.receiveAndDecrypt();
		if (buffer != UserManager::USERNAME)
			throw invalid_argument(
					string("Unknown server response: ") + buffer);
		string username = "";
		cout << "Username: ";
		getline(cin, username);
		clientSocket.encryptAndSend(username);

		buffer = clientSocket.receiveAndDecrypt();
		if (buffer != UserManager::PASSWORD)
			throw invalid_argument(string("Unknown server response: ") + buffer);
		string password = "";
		cout << "Password: ";
		getline(cin, password);
		clientSocket.encryptAndSend(password);
		buffer = clientSocket.receiveAndDecrypt();
		if (buffer == UserManager::CREDENTIALS_VALID) {
			cout << "Login success (To logout use the 'logout' command)\n";
		} else {
			throw invalid_argument("Invalid credentials");
		}

		cout << "Notifications:\n---\n";
		try {
			while (clientSocket.getValidity()) {
				string receivedMessage = clientSocket.receiveAndDecrypt();

				if (receivedMessage == TimelineManager::IS_ALIVE_PROBE) {
					clientSocket.encryptAndSend(TimelineManager::IS_ALIVE_PROBE);
					continue;
				}
				try {
					Notification notification = TimelineManager::getDecodedNotification(receivedMessage);
					cout << receivedMessage << endl;
					cout << Utils::getFormattedEpochTime(notification.getSentAt()) + ": " + notification.getMessage()
						 << endl;
					clientSocket.encryptAndSend(TimelineManager::getEncodedNotification(notification));
				} catch (invalid_argument &e) {
					LOG_ERROR << "Discarding corrupted notification: " << e.what();
					clientSocket.encryptAndSend(TimelineManager::IS_ALIVE_PROBE);
				}
			}
		} catch (SecureSocketException &e) {
			throw SecureSocketException(e.errorCode, string("Failed to received notification: ") + e.what());
		}

		//TODO Handle sending of commands once secure socket timeouts are implemented:
		while (clientSocket.getValidity()) {
			cout << "$ ";
			string command;
			getline(cin, command);
			if (UserManager::isLogoutCommand(command)) {
				clientSocket.encryptAndSend(command);
				throw runtime_error("Logging out...");
			} else {
				cout << command << ": Command not found" << endl;
			}
		}
	} catch (exception &e) {
		cout << e.what() << endl;
		clientSocket.destroySecureSocket();
		return 0;
	}
	cout << "The server unexpectedly hung up" << endl;
	return 0;
}
