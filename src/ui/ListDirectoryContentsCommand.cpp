#include "ui/ListDirectoryContentsCommand.hpp"
#include "ui/CommandPathUtil"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>

using namespace std;

ListDirectoryContentsCommand::ListDirectoryContentsCommand () {
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
  	return -1;
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
  std::string pathToBeListed = CommandPathUtil.convertToAbsolutePath(getPathSpecified(), userSessionDetail.getPresentWorkingDirectory());
  if(CommandPathUtil.specifiedPathExists(pathToBeListed) && CommandPathUtil.specifiedPathIsDirectory(pathToBeListed)) {
    //if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
      executeListDirectoryContentsCommandUtil();
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

std::string ListDirectoryContentsCommand::getPathSpecified () {
  return pathSpecified;
}

void ListDirectoryContentsCommand::setPathSpecified () {
  pathSpecified = CommandPathUtil.getPathSpecified (rawCommand);
}
