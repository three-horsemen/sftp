#include <stdlib>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

class Command {
private:
  std::string rawCommand;
  UserSessionDetail userSessionDetail;
public:
  Command(std::string commandInput, UserSessionDetail newUser);
  void interpretCommandType(std::string rawCommand);
  std::string getRawCommand();
}
