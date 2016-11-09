/*
 * TimelineManager.cpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#include "database/TimelineManager.hpp"

namespace sftp {

	namespace db {

		TimelineManager::TimelineManager(DbHandler &dbHandler) :
				dbHandler(dbHandler) {
		}

		TimelineManager::~TimelineManager() {
			// TODO Auto-generated destructor stub
		}

		void TimelineManager::notifyUser(string username, string message) {
			//TODO Allow for notification of a specific user
		}

		void TimelineManager::notifyOwners(string, string) {
			//TODO Refer to database for owners and notify them
		}

		int TimelineManager::pendingUsersCallback(void *data, int argc, char **argv,
												  char **azColName) {
			if (argc != 3)
				return 1;
			if (strcmp(azColName[0], "_id"), strcmp(azColName[1], "message")
											 || strcmp(azColName[2], "sentAt"))
				return 2;

			vector<Notification> *notifications = (vector<Notification> *) data;
			Notification notification(atoi(argv[0]), string(argv[1]),
									  (long) atoi(argv[2]));
			notifications->push_back(notification);

			return 0;
		}

		vector<Notification> TimelineManager::getPendingNotifications(int uid) {
			//TODO Handle SQL injection
			string sql =
					"select _id, message, sentAt from Notification where deliveredAt = 0 and recipient = "
					+ to_string(uid) + ";";
			vector<Notification> notifications;
			dbHandler.query(sql, pendingUsersCallback, (void *) &notifications);
			return notifications;
		}

		void TimelineManager::markAsNotified(long _id, long deliveredAt) {
			//TODO Handle SQL injection
			string sql = "update Notification set deliveredAt = "
						 + to_string(deliveredAt) + " where _id = " + to_string(_id) + ";";
			int count = dbHandler.executeUpdate(sql);
			if (count != 1) {
				throw runtime_error(
						string("Notification affected: ") + to_string(count) + " rows");
			}
		}

	} /* namespace db */

} /* namespace sftp */
