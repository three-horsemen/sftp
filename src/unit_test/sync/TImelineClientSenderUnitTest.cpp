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
			 << "1. Notify User\n"
			 << "2. Notify Owners\n";

		cin >> ch;
		if (ch == 0) {
			cout << "Exiting...\n";
		} else if (ch == 1) {
			cout << "Username or user ID: ";
			string user;
			cin >> user;
			long uid;
			if (Utils::isNumber(user)) {
				uid = stoi(user);
			} else {
				try {
					UserManager &userManager = DbManager::getDb()->getUserManager();
					uid = userManager.getUserId(user);
					if (uid == -1)
						throw invalid_argument("Invalid username. Aborting operation.");
				} catch (SQLiteException &e) {
					LOG_ERROR << e.what();
					cout << "Failed to determine user: " << e.what() << endl;
					continue;
				} catch (invalid_argument &e) {
					LOG_ERROR << e.what();
					cout << e.what();
					continue;
				}
			}
			cout << "Message: ";
			string message;
			cin >> message;
			DbManager::getDb()->getTimelineManager().notifyUser(uid, message);
		} else if (ch == 2) {
			cout << "Resource: ";
			string resource;
			cin >> resource;
			cout << "Enter the message: ";
			string message;
			cin >> message;
			try {
				DbManager::getDb()->getTimelineManager().notifyOwners(resource, message);
			} catch (invalid_argument &e) {
				LOG_ERROR << e.what();
			}
		} else {
			cout << "Unknown choice\n";
		}
	} while (ch);
	return 0;
}
