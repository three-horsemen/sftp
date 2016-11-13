//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_UserSessionDetail_HPP
#define SFTP_UserSessionDetail_HPP

#include <string>

#include <ui/CommandPathUtil.hpp>
#include <security/securesocket.hpp>

class UserSessionDetail {
private:
	std::string username;
	std::string presentWorkingDirectory;
	std::string loginTimestamp;
	std::string logoutTimestamp;
public:
	UserSessionDetail();

	UserSessionDetail(std::string uName);

	void setLoginTimestamp();

	std::string getLoginTimestamp();

	void setLogoutTimestamp();

	std::string getLogoutTimestamp();

	void setPresentWorkingDirectory(std::string newWorkingDirectory);

	std::string getPresentWorkingDirectory();

	void setUsername(std::string uName);

	std::string getUsername();

	void display();
};


#endif //SFTP_UserSessionDetail_HPP
