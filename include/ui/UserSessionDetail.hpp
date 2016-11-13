#include <iostream>
#include <stdlib.h>
#include "ui/CommandPathUtil.hpp"
#include "security/securesocket.hpp"

class UserSessionDetail {
private:
  std::string username;
  std::string presentWorkingDirectory;
  std::string loginTimestamp;
  std::string logoutTimestamp;
  SecureDataSocket secureDataSocket;
public:
  UserSessionDetail();
  UserSessionDetail(std::string uName);
  void setLoginTimestamp();
  std::string getLoginTimestamp();
  void setLogoutTimestamp();
  std::string getLogoutTimestamp();
  void setPresentWorkingDirectory(std::string newWorkingDirectory);
  std::string getPresentWorkingDirectory();
  void setUsername();
  SecureDataSocket getSecureDataSocket();
  void setSecureDataSocket(SecureDataSocket secureDataSocket);
  std::string getUsername();
  void display();
};
