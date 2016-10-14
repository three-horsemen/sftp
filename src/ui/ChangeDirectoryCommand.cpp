#include "ui/ChangeDirectoryCommand"
#include <iostream>
#include <unistd.h>
using namespace std;

ChangeDirectoryCommand::ChangeDirectoryCommand() {
  std::string rawCommand = getRawCommand();
  setPathSpecified();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathFinder.getPathSpecified(rawCommand);
}

void ChangeDirectoryCommand::executeChangeDirectoryCommand() {
  //Call function to indicate executing command <reuben>
  if(CommandPathUtil.specifiedPathExists(getPathSpecified())) {
    if(//call function to check if command permitted to the user <reuben>) {
      userSessionDetail.setPresentWorkingDirectory(getPathSpecified());
      commandOutput = "Working directory successfully changed to: " + getPathSpecified();
    }
    else {
      commandOutput = "Error: Access Denied";
    }
  }
  else {
    commandOutput = "Error: Invalid Path";
  }
  //Call function to indicate command completed execution <reuben>
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
