/*
 * Db.h
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_PERMISSION_MANAGER_HPP_
#define SRC_DATABASE_PERMISSION_MANAGER_HPP_

#include <sqlite3.h>
#include <string>
#include <string.h>

#include <shared/logger.hpp>
#include <database/DbHandler.hpp>

namespace sftp {

namespace db {

using namespace std;

class PermissionManager {
private:
	DbHandler &dbHandler;
public:
	PermissionManager(DbHandler&);
	virtual ~PermissionManager();

	bool setOwner(string, string);
	bool setOwners(string, string[], unsigned int);
	bool isResourceAccessible(string, string);
	int moveResource(string, string);

};

} /* namespace db */

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_PERMISSION_MANAGER_HPP_ */
