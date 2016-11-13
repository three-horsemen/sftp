
#include <unistd.h>
#include "ui/CommandInterpreter.hpp"

#define ON_CLIENT true
#define DATABASE_NAME "SecureFTP.db"
#define LOGIN_ATTEMPTS 3

#define boldAndRed(str) Utils::displayInBoldAndRed(str)
#define boldAndViolet(str) Utils::boldAndViolet(str)

void makeJailForUser(UserSessionDetail user) {
	//Make jail for this user at server
	cout << "\n";
	user.getSecureDataSocket().encryptAndSend(user.getUsername());
}

int main() {
	int loginAttempts = LOGIN_ATTEMPTS;
	std::string password;
	SecureDataSocket clientSecureDataSocket("127.0.0.1", "5576", HOST_MODE_CLIENT);
	boldAndRed(string("\n\t\tWelcome to Secure File Transfer Protocol\n"));
	sftp::db::DbManager::initializeStaticDbManager(DATABASE_NAME);
	boldAndViolet(string("\n1. New User\n2. Existing User\nPress any other key to exit\nChoice: "));
	int choice;
	cin >> choice;
	if (choice != 1 && choice != 2) {
		boldAndRed(string("\n---Exiting---\n"));
		return 0;
	}
	std::cin.ignore();
	boldAndViolet(string("Username: "));
	std::string userName;
	getline(cin, userName);
	password = getPassword();
	UserSessionDetail user(userName);
	user.setSecureDataSocket(clientSecureDataSocket);
	if (choice == 1) {
		while (true) {
			if (sftp::db::DbManager::getDb()->getUserManager().registerUser(user.getUsername(), password)) {
				boldAndViolet(string("\nSuccessfully registered user."));
				makeJailForUser(user);
				break;
			} else {
				displayInBoldAndRed(string("\nUnsuccessful in registering user."));
				cout << "\n0. Exit\n1. Retry\nChoice: ";
				int retryOrNot;
				cin >> retryOrNot;
				std::cin.ignore();
				if (!retryOrNot) {
					displayInBoldAndRed(string("\n\t\tExiting"));
					return 0;
				} else {
					boldAndViolet(string("\nUsername: "));
					getline(cin, userName);
					user.setUsername(userName);
					password = Utils::getPassword();
				}
			}
		}
	} else if (choice == 2) {
		while (true) {
			if (sftp::db::DbManager::getDb()->getUserManager().isAuthenticationValid(user.getUsername(), password)) {
				boldAndViolet(string("\nLogin successful.\n"));
				break;
			} else {
				displayInBoldAndRed(string("\nLogin unsuccessful."));
				loginAttempts--;
				if (loginAttempts > 0) {
					cout << "\n0. Exit\n1. Retry";
					displayInBoldAndRed(string("(attempts left:") + std::to_string(loginAttempts) + string(")"));
					cout << "\nChoice: ";
					int retryOrNot;
					cin >> retryOrNot;
					std::cin.ignore();
					if (!retryOrNot) {
						displayInBoldAndRed(string("\n\t\tExiting"));
						return 0;
					} else {
						boldAndViolet(string("\nUsername: "));
						getline(cin, userName);
						user.setUsername(userName);
						password = getPassword();
					}
				}
			}
		}
	}
	bool running = true;
	Command command(string("ls"), user);
	/* Sending username to server */
	user.getSecureDataSocket().encryptAndSend(user.getUsername());
	while (running) {
		boldAndViolet(string("\n") + user.getUsername());
		displayInBoldAndRed(string("@client-sftp"));
		cout << command.getUserSessionDetail().getPresentWorkingDirectory() << "$ ";
		std::string rawCommand;
		getline(cin, rawCommand);
		if (rawCommand.compare("quit") == 0) {
			running = false;
			continue;
		}
		try {
			Command tempCommand = CommandInterpreter::interpretCommandType(rawCommand, user,
																		   ON_CLIENT); //true for client, false for server
			command = tempCommand;
		} catch (UIException &exception) {
			LOG_ERROR << exception.what();
			continue;
		}
		user = command.getUserSessionDetail();
		cout << command.getCommandOutput();
	}
}
