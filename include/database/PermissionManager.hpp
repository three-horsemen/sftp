/*
 * PermissionManager.hpp
 *
 *  Created on: 04-Oct-2016
 *      Author: reubenjohn
 */

#ifndef INCLUDE_DATABASE_PERMISSIONMANAGER_HPP_
#define INCLUDE_DATABASE_PERMISSIONMANAGER_HPP_

#include <string>

namespace security {

using namespace std;

class PermissionManager {
public:
	PermissionManager(SecureDataSocket dataSocket);
	virtual ~PermissionManager();

	bool setOwners(string absolutePath, string newOwners[]);
	vector<string> getOwners(string absolutePath);
	bool isResourceAccessible(string absolutePath, string username);
	bool moveResource(string sourceAbsolutePath,
			string destinationAbsolutePath);
};

} /* namespace security */

#endif /* INCLUDE_DATABASE_PERMISSIONMANAGER_HPP_ */
