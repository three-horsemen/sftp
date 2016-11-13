/*
 * Db.h
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_USER_MANAGER_HPP_
#define SRC_DATABASE_USER_MANAGER_HPP_

#include <sqlite3.h>
#include <string.h>

#include <boost/algorithm/string.hpp>

#include <shared/logger.hpp>
#include <database/DbHandler.hpp>
#include <database/SQLiteException.hpp>

namespace sftp {

	namespace db {

		using namespace std;

		class UserManager {
		private:
			DbHandler &dbHandler;
		public:
			static constexpr const char USERNAME[] = "USERNAME";
			static constexpr const char PASSWORD[] = "PASSWORD";
			static constexpr const char CREDENTIALS_VALID[] = "VALID";
			static constexpr const char CREDENTIALS_INVALID[] = "INVALID";
			static constexpr const char EXIT[] = "exit";

			UserManager(DbHandler &);

			virtual ~UserManager();

			bool registerUser(string, string);

			bool isAuthenticationValid(string, string);

			long getUserId(string);

			static int getUserIdCallback(void *, int, char **, char **);

			static bool isExitCommand(string);
		};

	} /* namespace db */

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_DB_HPP_ */
