//
// Created by Reuben John on 9/11/16.
//

#include <database/DbManager.hpp>

using namespace sftp::db;
using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
		LOG_ERROR << "Must specify database name as argument";
		exit(1);
	}
	DbManager::initializeStaticDbManager(argv[1]);
	int ch = 0;
	do {
		cout << "Options:\n"
			 << "0. Exit\n"
			 << "1. Register\n"
			 << "2. Authenticate\n";

		cin >> ch;
		if (ch == 0) {

			cout << "Exiting...\n";
		} else if (ch == 1) {
			cout << "username: ";
			string username;
			cin >> username;
			cout << "password: ";
			string password;
			cin >> password;
			DbManager::getDb()->getUserManager().registerUser(username, password);
		} else if (ch == 2) {
			cout << "username: ";
			string username;
			cin >> username;
			cout << "password: ";
			string password;
			cin >> password;
			bool isAuthentic = DbManager::getDb()->getUserManager().isAuthenticationValid(username, password);
			if (isAuthentic) {
				cout << "Login was a success\n";
			} else {
				cout << "Authentication credentials invalid\n";
			}
		} else {
			cout << "Unknown choice\n";
		}
	} while (ch);
	return 0;
}
