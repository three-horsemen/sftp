#include <stdlib>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

class Command {
private:
  std::string rawCommand;
  UserSessionDetail userSessionDetail;
  std::string commandOutput;
public:
  Command(std::string commandInput, UserSessionDetail newUser);
  void interpretCommandType(std::string rawCommand);
  std::string getRawCommand();
  std::string getCommandOutput();
  void setCommandOutput(std::string commandResult);
}
