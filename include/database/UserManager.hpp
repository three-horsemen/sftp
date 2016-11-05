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

#include <shared/logger.hpp>
#include <database/DbHandler.hpp>
#include <database/SQLiteException.hpp>

namespace sftp {

namespace db {

using namespace std;
class UserManager {
private:
	DbHandler &dbHandler;
	static int registerUserCallback(void *data, int argc, char **argv,
			char **azColName);
	static int isAuthenticationValidCallback(void *data, int argc, char **argv,
			char **azColName);
public:
	UserManager(DbHandler&);
	virtual ~UserManager();

	bool registerUser(string, string);
	bool isAuthenticationValid(string, string);
};

} /* namespace db */

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_DB_HPP_ */
