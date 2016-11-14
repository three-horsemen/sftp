/*
 * TimelineManager.cpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#include <iomanip>
#include "database/TimelineManager.hpp"

#define timestampSize 11
namespace sftp {

	namespace db {

		TimelineManager::TimelineManager(DbHandler &dbHandler) :
				dbHandler(dbHandler) {
		}

		TimelineManager::~TimelineManager() {
			// TODO Auto-generated destructor stub
		}

		void TimelineManager::notifyUser(long userId, string message) {
			//TODO Allow for notification of a specific user
			string sql =
					string("INSERT INTO Notification (recipient,message,sentAt) VALUES (") + to_string(userId) +
					", '" + message + "',1478441444);";
			std::map<string, boost::any> map;
			map["recipient"] = userId;
			map["message"] = message;
			map["sentAt"] = Utils::getCurrentTimeMillis();
			dbHandler.executeInsert(sql);
		}

		vector<long> TimelineManager::getOwnerIds(string resource) {
			//TODO Handle SQL injection
			string sql =
					"select _id from User where username in (select owner from ResourcePermission where resource = '" +
					resource + "');";
			vector<long> ids;
			dbHandler.query(sql, ownerIdCallback, (void *) &ids);
			return ids;
		}

		int TimelineManager::ownerIdCallback(void *data, int argc, char **argv,
											 char **colNames) {
			if (argc != 1) return 1;
			if (strcmp("_id", colNames[0])) return 2;

			vector<long> *ids = (vector<long> *) data;
			ids->push_back(atol(argv[0]));

			return 0;
		}

		void TimelineManager::notifyOwners(string resource, string message) {
			long currentTime = Utils::getCurrentTimeMillis();
			vector<long> userIds = getOwnerIds(resource);
			if (userIds.size() <= 0)
				throw invalid_argument("The specified resource has no owners");
			string sql =
					string("INSERT INTO Notification (recipient,message,sentAt) VALUES ");
			for (int i = 0; i < userIds.size(); i++) {
				sql += "(" + to_string(userIds[i]) + ",'" + message + "'," + to_string(currentTime) + "),";
			}
			sql = sql.substr(0, sql.size() - 1);
			sql += ";";
			dbHandler.executeInsert(sql);
		}

		int TimelineManager::pendingUsersCallback(void *data, int argc, char **argv,
												  char **azColName) {
			if (argc != 3)
				return 1;
			if (strcmp(azColName[0], "_id"), strcmp(azColName[1], "message")
											 || strcmp(azColName[2], "sentAt"))
				return 2;

			vector<Notification> *notifications = (vector<Notification> *) data;
			Notification notification(atoi(argv[0]), (long) atoi(argv[2]), string(argv[1]));
			notifications->push_back(notification);

			return 0;
		}

		vector<Notification> TimelineManager::getPendingNotifications(long uid) {
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

		string TimelineManager::getEncodedNotification(Notification &notification) {
			std::ostringstream sentTimeStringStream;
			sentTimeStringStream << std::setw(11) << std::setfill('0') << notification.getSentAt();
			return NOTIFICATION_PREFIX + sentTimeStringStream.str() + notification.getMessage();
		}

		Notification TimelineManager::getDecodedNotification(string &encodedNotification) {
			unsigned long sentTimeIndex = strlen(NOTIFICATION_PREFIX);
			unsigned long messageIndex = sentTimeIndex + timestampSize;
			if (encodedNotification.size() < sentTimeIndex
				|| encodedNotification.substr(0, sentTimeIndex) != NOTIFICATION_PREFIX)
				throw invalid_argument("Invalid notification prefix");
			if (encodedNotification.size() < messageIndex)
				throw invalid_argument("Invalid sent time prefix");

			long sentAt = string_to_long(encodedNotification.substr(sentTimeIndex, timestampSize));
			string message = encodedNotification.substr(messageIndex, encodedNotification.size());
			Notification notification(
					-1l,
					sentAt,
					message);
			return notification;
		}
	} /* namespace db */

} /* namespace sftp */
