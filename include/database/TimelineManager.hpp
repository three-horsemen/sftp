/*
 * TimelineManager.hpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#ifndef SRC_SYNC_TIMELINEMANAGER_HPP_
#define SRC_SYNC_TIMELINEMANAGER_HPP_

#include <string>
#include <vector>
#include <string.h>
#include <iostream>

#include <database/DbHandler.hpp>
#include <database/Notification.hpp>

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

			TimelineManager(DbHandler &);

			virtual ~TimelineManager();

			void notifyUser(string, string);

			void notifyOwners(string, string);

			vector<Notification> getPendingNotifications(int);

			void markAsNotified(long _id, long);
		};

	} /* namespace db */

} /* namespace sftp */

#endif /* SRC_SYNC_TIMELINEMANAGER_HPP_ */
