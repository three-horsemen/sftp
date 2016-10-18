/*
 * Db.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/DbHandler.hpp>

namespace sftp {

namespace db {

DbHandler::DbHandler(std::string dbPath) {
	int rc;
	rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		throw new std::invalid_argument(dbPath);
	}
	LOG_DEBUG<< "Successfully opened database: "<<dbPath;
}

DbHandler::~DbHandler() {
	sqlite3_close(db);
}

int DbHandler::executeSQL(std::string sql,
		int (*callback)(void*, int, char**, char**), bool &success,
		char* &errorMessage) {
	LOG_DEBUG<<"Executing SQL: "+sql;
	int rc = sqlite3_exec(db, sql.c_str(), callback,
			(void*) &success, &errorMessage);
	return rc;
}

}
/* namespace db */

} /* namespace manas_nav_common */
