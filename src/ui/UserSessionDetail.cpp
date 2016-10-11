#include "ui/UserSessionDetail"
#include "ui/CommandExecutor"
#include <iostream>
#include <string>

UserSessionDetail::UserSessionDetail(std::string uName, std::string password){
  username = uName;
  //Call function to check if credentials are valid.
  presentWorkingDirectory = CommandExecutor.executeCommand(string("pwd").c_str());
  setLoginTimestamp();
  logoutTime = "Not yet logged out.";
}

void UserSessionDetail::setLoginTimestamp() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    loginTimestamp = string(buf);
}

std::string UserSessionDetail::getLoginTimestamp(){
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

void UserSessionDetail::setPresentWorkingDirectory(std::string newWorkingDirectory) {
  presentWorkingDirectory = newWorkingDirectory;
}

std::string UserSessionDetail::getPresentWorkingDirectory() {
  return presentWorkingDirectory;
}

std::string getUsername() {
  return username;
}
