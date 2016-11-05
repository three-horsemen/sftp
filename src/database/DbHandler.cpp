/*
 * Db.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/DbHandler.hpp>

namespace sftp {

namespace db {

char* DbHandler::generateSQLiteError(string errorMessageStr) {
	char* errorMessage = (char*) sqlite3_malloc(errorMessageStr.size());
	strcpy(errorMessage, errorMessageStr.c_str());
	return errorMessage;

}

void DbHandler::throwExceptionIfNeeded(int rc, const char* errorMessage) {
	if (rc != SQLITE_OK && rc != SQLITE_DONE) {
		if (errorMessage != NULL) {
			SQLiteException e(rc, errorMessage);
			throw e;
		} else {
			SQLiteException e(rc, "Unspecified error occured");
			throw e;
		}
	}
}

void DbHandler::throwExceptionIfNeeded(int rc, string errorMessage) {
	if (rc != SQLITE_OK && rc != SQLITE_DONE) {
		SQLiteException e(rc, errorMessage);
		throw e;
	}
}

int DbHandler::pragmaCallback(void* data, int argc, char** argv,
		char** azColName) {
	LOG_DEBUG<<"PRAGMA callback";
	bool &success = *((bool*)data);
	success = true;
	return 0;
}

DbHandler::DbHandler(std::string dbPath) {
	int rc;
	rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc != SQLITE_OK) {
		string errorMessage = "Failed to open database: "
				+ string(sqlite3_errmsg(db));
		throw invalid_argument(errorMessage);
	}
	LOG_DEBUG<< "Successfully opened database: "<<dbPath;

	LOG_DEBUG<< "Enabling foreign_keys";
	sqlite3_stmt * stmt;
	sqlite3_prepare(db, "PRAGMA foreign_keys = ON;", -1, &stmt, NULL);
	int rc2 = sqlite3_step(stmt);
	const char* errorMessage = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc2,
			string("Failed to create database: Enable foreign_keys failed: ")
					+ string(errorMessage));
	LOG_DEBUG<< "Enabled foreign_keys";

}

DbHandler::~DbHandler() {
	sqlite3_close(db);
}

void DbHandler::executeQuery(std::string sql,
		int (*callback)(void*, int, char**, char**), bool &success) {
	char* errorMessage = NULL;
	LOG_DEBUG<<"Executing SQL: "+sql;
	int rc = sqlite3_exec(db, sql.c_str(), callback, (void*) &success,
			&errorMessage);
	throwExceptionIfNeeded(rc, errorMessage);
	if (errorMessage == NULL)
		sqlite3_free((void*) errorMessage);
}

int DbHandler::rowCountCallback(void* data, int argc, char** argv,
		char** azColName) {
	LOG_DEBUG<< "Fetched "<<argc<<" rows";
	int &rowCount = *((int*)data);
	rowCount = -1;
	if(argc==1) {
		LOG_DEBUG<<"Row count valid";
		if(strcmp("count(*)",azColName[0])==0) {
			LOG_DEBUG<<"Column name valid";
			if(argv[0]) {
				rowCount = atoi(argv[0]);
				LOG_DEBUG<<"Returning rowCount = "<<rowCount;
				return 0;
			}
		}
	}
	return -1;
}

int DbHandler::getRowCount(std::string sql) {
	char* errorMessage = NULL;
	LOG_DEBUG<<"Executing SQL: "+sql;
	int count = -1;
	int rc = sqlite3_exec(db, sql.c_str(), rowCountCallback, (void*) &count,
			&errorMessage);
	throwExceptionIfNeeded(rc, errorMessage);
	if (errorMessage != NULL)
		sqlite3_free((void*) errorMessage);
	LOG_DEBUG<< "Row count: "<<count;
	return count;
}

int DbHandler::executeUpdate(std::string sql) {
	LOG_DEBUG<<"Executing SQL: "+sql;
	int count = -1;
	sqlite3_stmt * stmt;
	int rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
	const char* errorMessage = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, errorMessage);

	rc = sqlite3_step(stmt);
	const char* errorMessage2 = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, errorMessage2);
	count = sqlite3_changes(db);
	LOG_DEBUG<< "Affected "<<count<<" rows";
	return count;
}

int DbHandler::executeInsert(std::string sql) {
	LOG_DEBUG<<"Preparing statement: "+sql;
	int count = -1;

	sqlite3_stmt * stmt;
	int rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
	const char* errorMessage = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, errorMessage);

	LOG_DEBUG<<"Executing prepared statement";
	rc = sqlite3_step(stmt);
	int errorCode = sqlite3_errcode(db);
	const char* errorMessage2 = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, errorMessage2);
	count = sqlite3_changes(db);
	LOG_DEBUG<< "Affected "<<count<<" rows";
	return count;
}

}
/* namespace db */

} /* namespace manas_nav_common */
