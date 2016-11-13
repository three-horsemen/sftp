//
// Created by reubenjohn on 13/11/16.
//
#include "ui/UserSessionDetail.hpp"

UserSessionDetail::UserSessionDetail() {
	username = string("");
	presentWorkingDirectory = string("");
	loginTimestamp = string("");
	logoutTimestamp = string("");
}

UserSessionDetail::UserSessionDetail(std::string uName) {
	username = uName;
	//Call function to check if credentials are valid.
	presentWorkingDirectory = CommandPathUtil::getCurrentWorkingDirectory();
	setLoginTimestamp();
	logoutTimestamp = "Not yet logged out.";
}

void UserSessionDetail::setLoginTimestamp() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	loginTimestamp = string(buf);
}

std::string UserSessionDetail::getLoginTimestamp() {
	return loginTimestamp;
}

void UserSessionDetail::setLogoutTimestamp() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	logoutTimestamp = string(buf);
}

std::string UserSessionDetail::getLogoutTimestamp() {
	return logoutTimestamp;
}

void UserSessionDetail::setPresentWorkingDirectory(std::string &newWorkingDirectory) {
	presentWorkingDirectory = newWorkingDirectory;
}

std::string UserSessionDetail::getPresentWorkingDirectory() {
	return presentWorkingDirectory;
}

void UserSessionDetail::setUsername(std::string uName) {
	username = uName;
}

std::string UserSessionDetail::getUsername() {
	return username;
}

void UserSessionDetail::display() {
	cout << "\nUsername: " << username;
	cout << "\nLogin time: " << loginTimestamp;
	cout << "\nPresent working directory: " << presentWorkingDirectory;
	cout << "\nLogout time: " << logoutTimestamp;
}
