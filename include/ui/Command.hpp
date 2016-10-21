#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include <boost/algorithm/string/trim_all.hpp>
#include "ui/UserSessionDetail.hpp"
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
  ChangeDirectoryCommand(std::string commandInput, UserSessionDetail newUser);
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
  ListDirectoryContentsCommand(std::string commandInput, UserSessionDetail newUser);
  void executeListDirectoryContentsCommand();
  void executeListDirectoryContentsCommandUtil(std::string pathToBeListed);
  void setPathSpecified();
  std::string getPathSpecified();
};

class MakeDirectoryCommand : public Command {
private:
  std::string pathSpecified;
public:
  MakeDirectoryCommand(std::string commandInput, UserSessionDetail newUser);
  void executeMakeDirectoryCommand();
  void executeMakeDirectoryCommandUtil(std::string pathToNewDirectory);
  void setPathSpecified();
  std::string getPathSpecified();
}
