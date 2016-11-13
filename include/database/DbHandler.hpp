/*
 * Db.h
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_DB_HPP_
#define SRC_DATABASE_DB_HPP_

#include <string.h>
#include <string>
#include <exception>
#include <stdexcept>

#include <sqlite3.h>

#include <shared/logger.hpp>
#include <security/cryptstr.hpp>

#include <database/SQLiteException.hpp>

// #define test 2
const int test = 2;

namespace sftp {

namespace db {

class DbHandler {
	sqlite3 *db;
	void throwExceptionIfNeeded(int rc, const char* errorMessage);
	void throwExceptionIfNeeded(int rc, string errorMessage);
	static int pragmaCallback(void*, int, char**, char**);
	char* generateSQLiteError(string);
	string convertAndFreeIfNeeded(char*);
public:
	DbHandler(std::string, bool);
	virtual ~DbHandler();

	void executeRaw(std::string sql);
	void query(std::string sql, int (*callback)(void*, int, char**, char**),
			void* data);
	template<class T> void query(std::string sql,
			int (*callback)(void*, int, char**, char**), vector<T> &data);
	int getRowCount(std::string sql);
	int executeUpdate(std::string sql);
	int executeInsert(std::string sql);
	static int rowCountCallback(void*, int, char**, char**);
};

} /* namespace db */

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_DB_HPP_ */
