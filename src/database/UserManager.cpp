/*
 * Db.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/UserManager.hpp>

namespace sftp {

	namespace db {

		constexpr const char UserManager::USERNAME[];
		constexpr const char UserManager::PASSWORD[];
		constexpr const char UserManager::CREDENTIALS_VALID[];
		constexpr const char UserManager::CREDENTIALS_INVALID[];
		constexpr const char UserManager::LOGOUT[];

		UserManager::UserManager(DbHandler &dbHandler) :
				dbHandler(dbHandler) {
		}

		UserManager::~UserManager() {
		}

		bool UserManager::registerUser(string username, string password) {

			bool success = false;

			//TODO Prevent SQL injection
			string sql = "INSERT INTO User(username,password) VALUES ('" + username
						 + "', '" + password + "');";

			try {
				int count = dbHandler.executeInsert(sql);
				if (count == 1)
					success = true;
			} catch (SQLiteException &e) {
				LOG_ERROR << e.what();
				return false;
			}
			LOG_INFO << "Operation success: " << success;
			return success;
		}

		bool UserManager::isAuthenticationValid(string username, string password) {

			//TODO Prevent SQL injection
			string sql = "SELECT count(*) from User where username='" + username
						 + "' and password='" + password + "'";

			int rowCount = dbHandler.getRowCount(sql);
			return rowCount == 1;
		}

		bool UserManager::isLogoutCommand(string request) {
			return boost::equals(request, UserManager::LOGOUT);
		}

	}
/* namespace db */

} /* namespace manas_nav_common */
