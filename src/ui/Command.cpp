  #include "ui/Command.hpp"

Command::Command() {
  rawCommand = string("");
}

Command::Command(std::string commandInput, UserSessionDetail& newUser) {
  userSessionDetail = newUser;
  rawCommand = commandInput;
  //interpretCommandType(rawCommand);
}

std::string Command::getRawCommand () {
  return rawCommand;
}

void Command::setCommandOutput(std::string commandResult) {
  commandOutput = commandResult;
}

std::string Command::getCommandOutput () {
  return commandOutput;
}

UserSessionDetail Command::getUserSessionDetail() {
  return userSessionDetail;
}

/***** Change directory command *****/

ChangeDirectoryCommand::ChangeDirectoryCommand(std::string commandInput, UserSessionDetail& newUser) : Command(commandInput, newUser) {
  setPathSpecified();
  userSessionDetail = executeChangeDirectoryCommand();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil::getPathSpecified(Command::getRawCommand())[0];
}

UserSessionDetail ChangeDirectoryCommand::executeChangeDirectoryCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string newWorkingDirectory = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  if(CommandPathUtil::specifiedPathExists(newWorkingDirectory)) {
    if(CommandPathUtil::specifiedPathIsDirectory(newWorkingDirectory)) {
      //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
        userSessionDetail.setPresentWorkingDirectory(newWorkingDirectory);
        //getUserSessionDetail().setPresentWorkingDirectory(newWorkingDirectory);

        setCommandOutput(string("Working directory successfully changed to: ") + getUserSessionDetail().getPresentWorkingDirectory());
        return getUserSessionDetail();
        //>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
      //}

      //else {
      //  setCommandOutput(string("Error: Access Denied"));
        //>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
      //}
    }
    else {
      throw UIException(NOT_A_DIRECTORY);
      //>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error: not a directory <reuben>
    }
  }
  else {
    throw UIException(PATH_DOES_NOT_EXIST);
    //>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error: invalid path <reuben>
  }
}

std::string ChangeDirectoryCommand::getPathSpecified() {
  return pathSpecified;
}



/*****List directory command*****/

ListDirectoryContentsCommand::ListDirectoryContentsCommand (std::string commandInput, UserSessionDetail newUser) : Command(commandInput, newUser) {
  setPathSpecified ();
  executeListDirectoryContentsCommand ();
}

void ListDirectoryContentsCommand::executeListDirectoryContentsCommandUtil(std::string pathToBeListed) {
  DIR *dir;
	struct dirent *ent;
	vector<string> lsOutput;
  std::string localCommandOutput;
	if ((dir = opendir (pathToBeListed.c_str())) != NULL) {
  	/* print all the files and directories within directory */
  	while ((ent = readdir (dir)) != NULL) {
			lsOutput.push_back(ent->d_name);
  	}
  	closedir (dir);
	} else {
  	/* could not open directory */
  	localCommandOutput = "Cannot open directory";
  	return;
	}
	sort(lsOutput.begin(),lsOutput.end());
	lsOutput.erase(lsOutput.begin());
	lsOutput.erase(lsOutput.begin());
	for(int i=0;i<lsOutput.size();i++) {
		localCommandOutput = localCommandOutput + lsOutput[i] + string("\n");
	}
  setCommandOutput(localCommandOutput);
}

void ListDirectoryContentsCommand::executeListDirectoryContentsCommand () {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string pathToBeListed = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  if(CommandPathUtil::specifiedPathExists(pathToBeListed) && CommandPathUtil::specifiedPathIsDirectory(pathToBeListed)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      executeListDirectoryContentsCommandUtil(pathToBeListed);
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

std::string ListDirectoryContentsCommand::getPathSpecified () {
  return pathSpecified;
}

void ListDirectoryContentsCommand::setPathSpecified () {
  pathSpecified = CommandPathUtil::getPathSpecified (Command::getRawCommand())[0];
}




/*****Make directory command*****/

MakeDirectoryCommand::MakeDirectoryCommand( std::string commandInput, UserSessionDetail newUser) : Command(commandInput, newUser){
  setPathSpecified();
  executeMakeDirectoryCommand();
}

void MakeDirectoryCommand::executeMakeDirectoryCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string pathToNewDirectory = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  std::string pathToParentDirectoryOfNewDirectory = CommandPathUtil::findParentToGivenPath(pathToNewDirectory);
  if(CommandPathUtil::specifiedPathExists(pathToParentDirectoryOfNewDirectory) && CommandPathUtil::specifiedPathIsDirectory(pathToParentDirectoryOfNewDirectory)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      executeMakeDirectoryCommandUtil(pathToNewDirectory);
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


void MakeDirectoryCommand::executeMakeDirectoryCommandUtil(std::string pathToNewDirectory) {
  boost::filesystem::path dir(pathToNewDirectory.c_str());
  if(boost::filesystem::create_directory(dir)) {
    setCommandOutput(string("Directory created: ")+pathToNewDirectory);
  }
  else {
    setCommandOutput(string("Internal error occured while creating directory."));
  }
}

void MakeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil::getPathSpecified(Command::getRawCommand())[0];
}

std::string MakeDirectoryCommand::getPathSpecified() {
  return pathSpecified;
}

/*****Remove directory command*****/

RemoveCommand::RemoveCommand(std::string commandInput, UserSessionDetail newUser) : Command(commandInput, newUser) {
  setPathSpecified();
  executeRemoveCommand();
}

void RemoveCommand::executeRemoveCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string pathForRemoval = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  if(CommandPathUtil::specifiedPathExists(pathForRemoval)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      executeRemoveCommandUtil(pathForRemoval);
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

void RemoveCommand::executeRemoveCommandUtil(std::string pathSpecified) {
  boost::filesystem::path p = pathSpecified.c_str();
  boost::filesystem::remove_all(p);
  setCommandOutput(string("Successfully removed: ")+pathSpecified);
}

void RemoveCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil::getPathSpecified(Command::getRawCommand())[0];
}

std::string RemoveCommand::getPathSpecified() {
  return pathSpecified;
}



/*****Remove directory command*****/
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
