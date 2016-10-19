#include <stdlib.h>
#include "ui/UserSessionDetail.hpp"
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
  Command();
  Command(std::string commandInput, UserSessionDetail newUser);
  void interpretCommandType(std::string rawCommand);
  std::string getRawCommand();
  std::string getCommandOutput();
  void setCommandOutput(std::string commandResult);
  UserSessionDetail getUserSessionDetail();
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
  void setPathSpecified();
};

class ListDirectoryContentsCommand : public Command {
private:
  std::string pathSpecified;
  std::string attributesSpecified;
public:
  ListDirectoryContentsCommand();
  void executeListDirectoryContentsCommand();
  void executeListDirectoryContentsCommandUtil(std::string pathToBeListed);
  void setPathSpecified();
  std::string getPathSpecified();
};
