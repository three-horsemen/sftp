/*
 * TimelineManager.hpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#ifndef SRC_SYNC_TIMELINEMANAGER_HPP_
#define SRC_SYNC_TIMELINEMANAGER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

#include <shared/Utils.hpp>

#include <database/DbHandler.hpp>
#include <database/Notification.hpp>

#include <boost/any.hpp>

namespace sftp {

	namespace db {

		using namespace std;
		using namespace db;

		class TimelineManager {
		private:
			DbHandler &dbHandler;

			static int pendingUsersCallback(void *, int, char **, char **);

		public:
			static constexpr const char *SERVER_ERROR = "SERVER_ERROR";
			static constexpr const char *NOTIFICATION_PREFIX = "NOTIFICATION";
			static constexpr const char *IS_ALIVE_PROBE = "IS_ALIVE";

			TimelineManager(DbHandler &);

			virtual ~TimelineManager();

			static int ownerIdCallback(void *, int, char **, char **);

			vector<long> getOwnerIds(string);

			void notifyUser(long, string);

			void notifyOwners(string, string);

			vector<Notification> getPendingNotifications(long);

			void markAsNotified(long _id, long);

			static string getEncodedNotification(Notification &);

			static Notification getDecodedNotification(string &);
		};

	} /* namespace db */

} /* namespace sftp */

#endif /* SRC_SYNC_TIMELINEMANAGER_HPP_ */
