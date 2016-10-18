/*
 * Db.h
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_DB_HPP_
#define SRC_DATABASE_DB_HPP_

#include <string>
#include <stdexcept>

#include <sqlite3.h>

#include <shared/logger.hpp>

#define test 2

namespace sftp {

namespace db {

class DbHandler {
	sqlite3 *db;
public:
	DbHandler(std::string);
	virtual ~DbHandler();

	int executeSQL(std::string sql, int (*callback)(void*, int, char**, char**),
			bool &success, char* &errorMessage);
};

} /* namespace db */

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_DB_HPP_ */
