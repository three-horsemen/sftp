#include <stdlib>
#include <iostream>
#include <stdio.h>
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
};

class ChangeDirectoryCommand : public Command {
private:
  //std::string commandAndAttributesSpecified; //possibly useless
  std::string pathSpecified;
public:
  ChangeDirectoryCommand();
  void executeChangeDirectoryCommand();
  //std::string getCommandAndAttributesSpecified(); //possibly useless
  std::string getPathSpecified();
};

class ListDirectoryContentsCommand : public Command {
private:
  std::string pathSpecified;
  std::string attributesSpecified;
public:
  ListDirectoryContentsCommand();
  void executeListDirectoryContentsCommand();
  void executeListDirectoryContentsCommandUtil();
  void setPathSpecified();
  std::string getPathSpecified();
};
