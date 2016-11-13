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
		}

		PermissionManager::~PermissionManager() {
		}

		bool PermissionManager::isResourceAccessible(string absolutePath,
													 string username) {
			string sql = "select count(*) from ResourcePermission where resource='"
						 + absolutePath + "' and owner='" + username + "';";
			return dbHandler.getRowCount(sql) == 1;
		}

		bool PermissionManager::setOwner(string absolutePath, string newOwner) {

			//TODO Prevent SQL injection
			//TODO Check if the username exists
			bool isAlreadyOwner = isResourceAccessible(absolutePath, newOwner);
			if (isAlreadyOwner) {
				LOG_WARNING << "User was already an owner when attempting to set the owner";
				return true;
			} else {
				string insertSql =
						"INSERT INTO ResourcePermission (resource,owner) VALUES('" + absolutePath + "', '" + newOwner +
						"');";
				int count = dbHandler.executeInsert(insertSql);
				return count == 1;
			}
		}

		bool PermissionManager::setOwners(string absolutePath, string newOwners[],
										  unsigned ownerCount) {

			//TODO Prevent SQL injection
			for (unsigned int i = 0; i < ownerCount; i++) {
				bool success = setOwner(absolutePath, newOwners[i]);
				if (!success)
					return false;
			}
			return true;
		}

		int PermissionManager::moveResource(string sourceAbsolutePath,
											string destinationAbsolutePath) {
			string sql = "UPDATE ResourcePermission set resource='"
						 + destinationAbsolutePath + "' where resource='"
						 + sourceAbsolutePath + "'";
			int count = dbHandler.executeUpdate(sql);

			return count;
		}

	}
/* namespace db */

} /* namespace manas_nav_common */
