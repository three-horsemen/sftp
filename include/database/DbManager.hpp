/*
 * DbHandler.hpp
 *
 *  Created on: 17-Oct-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_DBHANDLER_HPP_
#define SRC_DATABASE_DBHANDLER_HPP_

#include <stdlib.h>

#include <database/UserManager.hpp>
#include <database/DbHandler.hpp>
#include <database/UserManager.hpp>
#include <database/PermissionManager.hpp>
#include <database/TimelineManager.hpp>

namespace sftp {

namespace db {

class DbManager {
private:
	static DbManager* dbManager;
	DbHandler dbHandler;
	UserManager* userManager;
	TimelineManager* timelineManager;
	PermissionManager* permissionManager;
public:
	DbManager(DbHandler&);
	virtual ~DbManager();
	UserManager& getUserManager();
	PermissionManager& getPermissionManager();
	TimelineManager& getTimelineManager();
	static DbManager* getDb();
	static void initializeStaticDbManager(std::string);
};

}

} /* namespace manas_nav_common */

#endif /* SRC_DATABASE_DBHANDLER_HPP_ */
