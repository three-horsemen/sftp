#include "ui/CommandInterpreter.hpp"

Command CommandInterpreter::interpretCommandType(std::string rawCommand, UserSessionDetail newUser) {
  boost::trim_all(rawCommand);
  if(rawCommand.compare(0,2,"cd")==0) {
    // return new ChangeDirectoryCommand(rawCommand, newUser);
    return ChangeDirectoryCommand(rawCommand, newUser);
  }
  else if(rawCommand.compare(0,2,"ls")==0) {
    // return new ListDirectoryContentsCommand(rawCommand, newUser);
    return ListDirectoryContentsCommand(rawCommand, newUser);
  }
/*  else if(rawCommand.compare(0,5,"mkdir")){
    MakeDirectoryCommand newChild(rawCommand);
  }
  else if(rawCommand.compare(0,2,"cp")){
    CopyFilesAndDirectoriesCommand newChild(rawCommand);
  }
  else if(rawCommand.compare(0,2,"rm")){
    RemoveFilesAndDirectoriesCommand newChild(rawCommand);
  }
  else if(rawCommand.compare(0,5,"chown")){
    ChangeFileOwnerAndGroupCommand newChild(rawCommand);
  }*/
  else {
    std::cout<<"\nError: Invalid command. Please enter one of 'cd', 'ls', 'mkdir', 'cp', 'rm' or 'chown'.";
  }
}
