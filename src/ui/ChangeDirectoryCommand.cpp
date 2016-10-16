#include "ui/ChangeDirectoryCommand"
#include "ui/CommandPathUtil"
#include <iostream>
#include <unistd.h>
using namespace std;

ChangeDirectoryCommand::ChangeDirectoryCommand() {
  std::string rawCommand = getRawCommand();
  setPathSpecified();
  executeChangeDirectoryCommand();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathFinder.getPathSpecified(rawCommand);
}

void ChangeDirectoryCommand::executeChangeDirectoryCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string newWorkingDirectory = CommandPathUtil.convertToAbsolutePath(getPathSpecified(), userSessionDetail.getPresentWorkingDirectory());
  if(CommandPathUtil.specifiedPathExists(newWorkingDirectory) && CommandPathUtil.specifiedPathIsDirectory()) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      userSessionDetail.setPresentWorkingDirectory(newWorkingDirectory);
      commandOutput = "Working directory successfully changed to: " + newWorkingDirectory;
      //>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
    //}
    else {
      commandOutput = "Error: Access Denied";
      //>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
    }
  }
  else {
    commandOutput = "Error: Invalid path (Path does not exist, or leads to a file, not directory)";
    //>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error: invalid path <reuben>
  }
}

/*
//Possibly useless
std::string ChangeDirectoryCommand::getCommandAndAttributesSpecified() {
  return commandAndAttributesSpecified;
}
*/
std::string ChangeDirectoryCommand::getPathSpecified() {
  return pathSpecified;
}

std::string ChangeDirectoryCommand::getRawCommand() {
  return Command::getRawCommand();
}
