  #include "ui/Command.hpp"

/*
CopyCommand::CopyCommand(std::string commandInput, UserSessionDetail newUser) : Command(commandInput, newUser) {
  setPathSpecified();
  executeCopyCommand();
}

void CopyCommand::executeCopyCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string pathForRemoval = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  if(CommandPathUtil::specifiedPathExists(pathForRemoval)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      executeCopyCommandUtil(pathForRemoval);
      //>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
    //}
    //else {
    //  setCommandOutput(string("Error: Access Denied"));
      //>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
  //  }
  }
  else {
    setCommandOutput(string("Error: Invalid path (Path does not exist, or leads to a file, not directory)"));
    //>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error: invalid path <reuben>
  }
}

void CopyCommand::executeCopyCommandUtil(std::string pathSpecified) {

}

void CopyCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil::getPathSpecified(Command::getRawCommand())[0];
}

std::string CopyCommand::getPathSpecified() {
  return pathSpecified;
}
*/
