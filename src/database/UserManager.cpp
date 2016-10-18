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
		if(strcmp("cnt",azColName[0])==0) {
			LOG_DEBUG<<"Column name valid";
			if(argv[0] && atoi(argv[0])==1) {
				LOG_DEBUG<<"Count is not null and 1";
				failure = false;
			}
		}
	}
	LOG_DEBUG<<"Returning authentication failure = "<<failure;
	return failure;
}

int UserManager::registerUserCallback(void *data, int argc, char **argv,
		char **azColName) {
	LOG_DEBUG<< "Fetched "<<argc<<" rows";
	int i;
	for (i = 0; i < argc; i++) {
		LOG_INFO<< azColName[i] << " = " << argv[i] ? argv[i] : "NULL";
	}
	LOG_INFO<< endl;

	if (argc == 1) {
		*((bool*)data) = true;
	}
	return 0;
}

bool UserManager::registerUser(string username, string password) {

	char* errorMessage;
	bool success = false;

	//TODO Prevent SQL injection
	string sql = "INSERT INTO User(username,password) VALUES ('" + username
			+ "', '" + password + "');";

	/* Execute SQL statement */
	int rc = dbHandler.executeSQL(sql, registerUserCallback, success,
			errorMessage);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return false;
	} else {
		LOG_INFO<<"Operation success";
		return success;
	}
}

bool UserManager::isAuthenticationValid(string username, string password) {

	char* errorMessage;
	bool success = false;

	//TODO Prevent SQL injection
	string sql = "SELECT count(*) cnt from User where username='" + username
			+ "' and password='" + password + "'";

	/* Execute SQL statement */
	int rc = dbHandler.executeSQL(sql, isAuthenticationValidCallback, success,
			errorMessage);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return false;
	} else {
		LOG_INFO<<"Operation success";
		return !success;
	}
}

}
/* namespace db */

} /* namespace manas_nav_common */
