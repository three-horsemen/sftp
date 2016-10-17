#include "ui/ChangeDirectoryCommand"
#include "ui/CommandPathUtil"
#include <iostream>
#include <unistd.h>
using namespace std;

ChangeDirectoryCommand::ChangeDirectoryCommand() {
  setPathSpecified();
  executeChangeDirectoryCommand();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil.getPathSpecified(rawCommand);
}

void ChangeDirectoryCommand::executeChangeDirectoryCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string newWorkingDirectory = CommandPathUtil.convertToAbsolutePath(getPathSpecified(), userSessionDetail.getPresentWorkingDirectory());
  if(CommandPathUtil.specifiedPathExists(newWorkingDirectory) && CommandPathUtil.specifiedPathIsDirectory()) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      userSessionDetail.setPresentWorkingDirectory(newWorkingDirectory);
      setCommandOutput(string("Working directory successfully changed to: ") + newWorkingDirectory);
      //>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
    //}
    else {
      setCommandOutput(string("Error: Access Denied"));
      //>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
    }
  }
  else {
    setCommandOutput(string("Error: Invalid path (Path does not exist, or leads to a file, not directory)"));
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
