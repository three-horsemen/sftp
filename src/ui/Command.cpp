#include "ui/Command.hpp"

Command::Command(std::string commandInput, UserSessionDetail newUser){
  boost::trim(commandInput);
  userSessionDetail = newUser;
  rawCommand = commandInput;
  interpretCommandType(rawCommand);
}

void Command::interpretCommandType(std::string rawCommand) {
  if(rawCommand.compare(0,2,"cd")){
    ChangeDirectoryCommand newChild(rawCommand);
  }
  else if(rawCommand.compare(0,2,"ls")){
    ListDirectoryContentsCommand newChild(rawCommand);
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
  else{
    std::cout<<"\nError: Invalid command. Please enter one of 'cd', 'ls', 'mkdir', 'cp', 'rm' or 'chown'.";
  }
}

std::string Command::getRawCommand(){
  return rawCommand;
}
