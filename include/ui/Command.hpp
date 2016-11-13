#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include "shared/logger.hpp"
#include "ui/UIException.hpp"
#include "database/DbManager.hpp"

#include <ui/command/Command.hpp>
#include <ui/command/ChangeDirectoryCommand.hpp>

#define BOOST_NO_CXX11_SCOPED_ENUMS


#undef BOOST_NO_CXX11_SCOPED_ENUMS                                    /***used for  MakeDirectoryCommand***/

#include <boost/algorithm/string/trim_all.hpp>

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
