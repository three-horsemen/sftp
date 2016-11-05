/*
 * Db.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/UserManager.hpp>

namespace sftp {

namespace db {

UserManager::UserManager(DbHandler &dbHandler) :
		dbHandler(dbHandler) {
	int x = test;
}

UserManager::~UserManager() {
}

int UserManager::isAuthenticationValidCallback(void *data, int argc,
		char **argv, char **azColName) {
	LOG_DEBUG<< "Fetched "<<argc<<" rows";
	bool &failure = *((bool*)data);
	failure = true;
	if(argc==1) {
		LOG_DEBUG<<"Row count valid";
		if(strcmp("count(*)",azColName[0])==0) {
			LOG_DEBUG<<"Column name valid";
			if(argv[0] && atoi(argv[0])==1) {
				LOG_DEBUG<<"Count is not null and 1";
				failure = false;
			}
		}
	}
	LOG_DEBUG<<"Returning authentication failure = "<<failure;
	return 0;
}

bool UserManager::registerUser(string username, string password) {

	char* errorMessage;
	bool success = false;

	//TODO Prevent SQL injection
	string sql = "INSERT INTO User(username,password) VALUES ('" + username
			+ "', '" + password + "');";

	try {
		int count = dbHandler.executeInsert(sql);
		if (count == 1)
			success = true;
	} catch (SQLiteException &e) {
		LOG_ERROR<<e.what();
		return false;
	}
	LOG_INFO<<"Operation success: "<<success;
	return success;
}

bool UserManager::isAuthenticationValid(string username, string password) {

	char* errorMessage;
	bool failure = false;

	//TODO Prevent SQL injection
	string sql = "SELECT count(*) from User where username='" + username
			+ "' and password='" + password + "'";

	/* Execute SQL statement */
	dbHandler.query(sql, isAuthenticationValidCallback, failure);
	int rowCount = dbHandler.getRowCount(sql);
	return !failure;
}

}
/* namespace db */

} /* namespace manas_nav_common */
