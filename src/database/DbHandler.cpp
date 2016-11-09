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

string DbHandler::convertAndFreeIfNeeded(char* buffer) {
	if (buffer != NULL) {
		string s(buffer);
		sqlite3_free((void*) buffer);
		return s;
	} else {
		return string("");
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

DbHandler::DbHandler(std::string dbPath, bool foreignKeysEnabled = true) {
	int rc;
	rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc != SQLITE_OK) {
		string errorMessage = "Failed to open database: "
				+ string(sqlite3_errmsg(db));
		throw invalid_argument(errorMessage);
	}
	LOG_DEBUG<< "Successfully opened database: "<<dbPath;

	if (foreignKeysEnabled) {
		try {
			LOG_DEBUG<< "Enabling foreign_keys";
			executeRaw("PRAGMA foreign_keys = ON;");
			LOG_DEBUG<< "Enabled foreign_keys";
		} catch (SQLiteException &e) {
			throwExceptionIfNeeded(e.getErrorCode(),
					string(
							"Failed to create database: Enable foreign_keys failed: ")
					+ string(e.what()));
		}
	}
}

DbHandler::~DbHandler() {
	sqlite3_close(db);
}

void DbHandler::executeRaw(std::string sql) {
	LOG_DEBUG<< "Executing raw statement: "<<sql;
	sqlite3_stmt * stmt;
	sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	const char* errorMessage = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, string(errorMessage));
	LOG_DEBUG<< "Raw statement execution success";
}

void DbHandler::query(std::string sql,
		int (*callback)(void*, int, char**, char**), void* data) {
	char* errorMessage = NULL;
	LOG_DEBUG<<"Executing SQL: "+sql;
	int rc = sqlite3_exec(db, sql.c_str(), callback, data, &errorMessage);
	throwExceptionIfNeeded(rc, convertAndFreeIfNeeded(errorMessage));
}

template<class T> void DbHandler::query(std::string sql,
		int (*callback)(void*, int, char**, char**), vector<T> &data) {
	char* errorMessage = NULL;
	LOG_DEBUG<<"Executing SQL: "+sql;
	int rc = sqlite3_exec(db, sql.c_str(), callback, (void*) data,
			&errorMessage);
	throwExceptionIfNeeded(rc, convertAndFreeIfNeeded(errorMessage));
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
	throwExceptionIfNeeded(rc, convertAndFreeIfNeeded(errorMessage));
	LOG_DEBUG<< "Row count: "<<count;
	return count;
}

int DbHandler::executeUpdate(std::string sql) {
	LOG_DEBUG<<"Executing SQL: "+sql;
	int count = -1;
	sqlite3_stmt * stmt;
	int rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
	throwExceptionIfNeeded(rc, charArray_to_string(sqlite3_errmsg(db)));

	rc = sqlite3_step(stmt);
	throwExceptionIfNeeded(rc, charArray_to_string(sqlite3_errmsg(db)));
	count = sqlite3_changes(db);
	LOG_DEBUG<< "Affected "<<count<<" rows";
	return count;
}

int DbHandler::executeInsert(std::string sql) {
	LOG_DEBUG<<"Preparing statement: "+sql;
	int count = -1;

	sqlite3_stmt * stmt;
	int rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
	throwExceptionIfNeeded(rc, charArray_to_string(sqlite3_errmsg(db)));

	LOG_DEBUG<<"Executing prepared statement";
	rc = sqlite3_step(stmt);
	int errorCode = sqlite3_errcode(db);
	const char* errorMessage2 = sqlite3_errmsg(db);
	throwExceptionIfNeeded(rc, charArray_to_string(sqlite3_errmsg(db)));
	count = sqlite3_changes(db);
	LOG_DEBUG<< "Affected "<<count<<" rows";
	return count;
}

}
/* namespace db */

} /* namespace manas_nav_common */
