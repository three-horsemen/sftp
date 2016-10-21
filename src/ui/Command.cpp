#include "ui/Command.hpp"

Command::Command() {
  rawCommand = string("");
}

Command::Command(std::string commandInput, UserSessionDetail newUser) {
  boost::trim(commandInput);
  userSessionDetail = newUser;
  rawCommand = commandInput;
  //interpretCommandType(rawCommand);
}

/* shifted code to command interpreter
void Command::interpretCommandType(std::string rawCommand) {
  if(rawCommand.compare(0,2,"cd")==0) {
    ChangeDirectoryCommand newChild();
  }
  else if(rawCommand.compare(0,2,"ls")==0) {
    ListDirectoryContentsCommand newChild();
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
  }
  else {
    std::cout<<"\nError: Invalid command. Please enter one of 'cd', 'ls', 'mkdir', 'cp', 'rm' or 'chown'.";
  }
}
*/

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

ChangeDirectoryCommand::ChangeDirectoryCommand(std::string commandInput, UserSessionDetail newUser) : Command(commandInput, newUser) {
  this->setPathSpecified();
  this->executeChangeDirectoryCommand();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil::getPathSpecified(Command::getRawCommand());
}

void ChangeDirectoryCommand::executeChangeDirectoryCommand() {
  //>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
  std::string newWorkingDirectory = CommandPathUtil::convertToAbsolutePath(getPathSpecified(), getUserSessionDetail().getPresentWorkingDirectory());
  if(CommandPathUtil::specifiedPathExists(newWorkingDirectory) && CommandPathUtil::specifiedPathIsDirectory(newWorkingDirectory)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      getUserSessionDetail().setPresentWorkingDirectory(newWorkingDirectory);
      setCommandOutput(string("Working directory successfully changed to: ") + newWorkingDirectory);
      //>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
    //}

    //else {
    //  setCommandOutput(string("Error: Access Denied"));
      //>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
    //}
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
  //cout<<localCommandOutput;
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
  pathSpecified = CommandPathUtil::getPathSpecified (Command::getRawCommand());
}
