#include <iostream>
#include <stdlib>

using namespace std;

class UserSessionDetail {
private:
  std::string username;
  std::string presentWorkingDirectory;
  std::string loginTimestamp;
  std::string logoutTimestamp;
public:
  UserSessionDetail(std::string uName, std::string password);
  void setLoginTimestamp();
  std::string getLoginTimestamp();
  void setLogoutTimestamp();
  std::string getLogoutTimestamp();
  void setPresentWorkingDirectory(std::string newWorkingDirectory);
  std::string getPresentWorkingDirectory();
  std::string getUsername();
}
