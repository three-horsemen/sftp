/*
 * DbHandler.cpp
 *
 *  Created on: 17-Oct-2016
 *      Author: reubenjohn
 */

#include <database/DbManager.hpp>

namespace sftp {

namespace db {

DbManager* DbManager::dbManager = NULL;

DbManager::DbManager(DbHandler &dbHandler) :
		dbHandler(dbHandler) {
	userManager = NULL;
	permissionManager = NULL;

}

DbManager::~DbManager() {
	// TODO Auto-generated destructor stub
}

DbManager* DbManager::getDb() {
	if (DbManager::dbManager) {
		return DbManager::dbManager;
	} else {
		throw std::logic_error(
				"getDb manager called before initialization of Db manager");
	}
}

UserManager& DbManager::getUserManager() {
	if (userManager) {
		return *userManager;
	} else {
		userManager = new UserManager(dbManager->dbHandler);
		return *userManager;
	}
}

PermissionManager& DbManager::getPermissionManager() {
	if (permissionManager) {
		return *permissionManager;
	} else {
		permissionManager = new PermissionManager(dbManager->dbHandler);
		return *permissionManager;
	}
}

void DbManager::initializeStaticDbManager(std::string dbPath) {
	if (!DbManager::dbManager) {
		DbManager::dbManager = new DbManager(*(new DbHandler(dbPath)));
	}
}

}

} /* namespace manas_nav_common */
