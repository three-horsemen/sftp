/*
 * DbHandler.cpp
 *
 *  Created on: 17-Oct-2016
 *      Author: reubenjohn
 */

#include <database/DbManager.hpp>

namespace sftp {

	namespace db {

		DbManager *DbManager::dbManager = NULL;

		DbManager::DbManager(DbHandler &dbHandler) :
				dbHandler(dbHandler) {
			userManager = NULL;
			permissionManager = NULL;
			timelineManager = NULL;

			try {
				LOG_DEBUG << "Creating tables (if not exists)";
				dbHandler.executeRaw(
						"CREATE TABLE IF NOT EXISTS User (_id INTEGER PRIMARY KEY AUTOINCREMENT, username text not null unique, password text not null, sessionId text);");
				dbHandler.executeRaw(
						"CREATE TABLE IF NOT EXISTS `ResourcePermission` (_id INTEGER PRIMARY KEY AUTOINCREMENT, `resource` text not null, `owner` text not null, FOREIGN KEY(`owner`) REFERENCES `User`(`username`));");
				dbHandler.executeRaw(
						"CREATE TABLE IF NOT EXISTS `Notification`(`_id` INTEGER PRIMARY KEY AUTOINCREMENT, `recipient` INTEGER NOT NULL, `message` TEXT NOT NULL, sentAt INTEGER NOT NULL, deliveredAt INTEGER DEFAULT 0 CONSTRAINT future_delivery_time CHECK (deliveredAt >= strftime('%s', 'now') OR deliveredAt = 0), FOREIGN KEY (`recipient`) REFERENCES `User`(`_id`));");
				LOG_DEBUG << "Tables ready";
			} catch (SQLiteException &e) {
				throw SQLiteException(e.getErrorCode(),
									  string(
											  "Failed to create database: Failed to create tables: ")
									  + string(e.what()));
			}
		}

		DbManager::~DbManager() {
			// TODO Auto-generated destructor stub
		}

		DbManager *DbManager::getDb() {
			if (DbManager::dbManager) {
				return DbManager::dbManager;
			} else {
				throw std::logic_error(
						"getDb manager called before initialization of Db manager");
			}
		}

		UserManager &DbManager::getUserManager() {
			if (userManager) {
				return *userManager;
			} else {
				userManager = new UserManager(dbManager->dbHandler);
				return *userManager;
			}
		}

		PermissionManager &DbManager::getPermissionManager() {
			if (permissionManager) {
				return *permissionManager;
			} else {
				permissionManager = new PermissionManager(dbManager->dbHandler);
				return *permissionManager;
			}
		}

		TimelineManager &DbManager::getTimelineManager() {
			if (timelineManager) {
				return *timelineManager;
			} else {
				timelineManager = new TimelineManager(dbManager->dbHandler);
				return *timelineManager;
			}
		}

		void DbManager::initializeStaticDbManager(std::string dbPath) {
			if (!DbManager::dbManager) {
				DbManager::dbManager = new DbManager(*(new DbHandler(dbPath, true)));
			}
		}

	}

} /* namespace manas_nav_common */
