#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include "shared/logger.hpp"
#include "ui/UIExceptions.hpp"
#include "database/DbManager.hpp"
#include "ui/UserSessionDetail.hpp"
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS                                    /***used for  MakeDirectoryCommand***/
#include <boost/algorithm/string/trim_all.hpp>

class Command {
protected:
  std::string rawCommand;
  UserSessionDetail userSessionDetail;
  std::string commandOutput;
public:
  Command();
  Command(std::string commandInput, UserSessionDetail& newUser);
  std::string getRawCommand();
  std::string getCommandOutput();
  void setCommandOutput(std::string commandResult);
  UserSessionDetail getUserSessionDetail();
};

class ChangeDirectoryCommand : public Command {
private:
  std::string pathSpecified;
public:
  ChangeDirectoryCommand(std::string commandInput, UserSessionDetail& newUser);
  UserSessionDetail executeChangeDirectoryCommand();
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
};

class RemoveCommand : public Command {
private:
  std::string pathSpecified;
public:
  RemoveCommand(std::string commandInput, UserSessionDetail newUser);
  void executeRemoveCommand();
  void executeRemoveCommandUtil(std::string pathSpecified);
  void setPathSpecified();
  std::string getPathSpecified();
};
/*
class CopyCommand : public Command {
private:
  std::string pathSpecified;
public:
  RemoveCommand(std::string commandInput, UserSessionDetail newUser);
  void executeRemoveCommand();
  void executeRemoveCommandUtil(std::string pathSpecified);
  void setPathSpecified();
  std::string getPathSpecified();
};
*/
