/*
 * Db.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/PermissionManager.hpp>

namespace sftp {

namespace db {

PermissionManager::PermissionManager(DbHandler &dbHandler) :
		dbHandler(dbHandler) {
	int x = test;
}

PermissionManager::~PermissionManager() {
}

bool PermissionManager::isResourceAccessible(string absolutePath,
		string username) {
	char* errorMessage;
	string sql = "select count(*) from ResourcePermission where resource='"
			+ absolutePath + "' and owner='" + username + "';";
	return dbHandler.getRowCount(sql) == 1;
}

bool PermissionManager::setOwner(string absolutePath, string newOwner) {
	char* errorMessage;
	bool failure = false;

	//TODO Prevent SQL injection
	//TODO Check if the username exists
	bool isAlreadyOwner = isResourceAccessible(absolutePath, newOwner);
	if (isAlreadyOwner) {
		LOG_WARNING<<"User was already an owner when attempting to set the owner";
		return true;
	} else {
		string insertSql =
		"INSERT INTO ResourcePermission (resource,owner) VALUES('"+absolutePath+"', '"+newOwner+"');";
		int count = dbHandler.executeInsert(insertSql);
		return count==1;
	}
	return false;
}

bool PermissionManager::setOwners(string absolutePath, string newOwners[],
		unsigned ownerCount) {
	char* errorMessage;
	bool success = false;

	//TODO Prevent SQL injection
	for (unsigned int i = 0; i < ownerCount; i++) {
		bool success = setOwner(absolutePath, newOwners[i]);
		return success;
	}
	return false;
}

bool PermissionManager::moveResource(string sourceAbsolutePath,
		string destinationAbsolutePath) {
	return false;
}

}
/* namespace db */

} /* namespace manas_nav_common */
