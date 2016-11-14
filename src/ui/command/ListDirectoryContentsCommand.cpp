//
// Created by reubenjohn on 13/11/16.
//

#include "ui/command/ListDirectoryContentsCommand.hpp"

ListDirectoryContentsCommand::ListDirectoryContentsCommand(std::string &commandInput, string &pwd) : Command(
		commandInput) {
	if (commandInput.find("://") != string::npos) {
		serverExecutionPending = true;
	} else {
		serverExecutionPending = false;
		parts.push_back(
				CommandPathUtil::convertToAbsolutePath(CommandPathUtil::getPathSpecified(Command::getRawCommand())[0],
													   pwd));
	}
}

ListDirectoryContentsCommand::ListDirectoryContentsCommand(std::string &commandInput) : Command(commandInput) {
	string absPath = commandInput.substr(3, commandInput.size() - 3);
	parts.push_back(absPath);
}

void ListDirectoryContentsCommand::executeListDirectoryContentsCommandUtil(std::string pathToBeListed) {
	DIR *dir;
	struct dirent *ent;
	vector<string> lsOutput;
	std::string localCommandOutput;
	if ((dir = opendir(pathToBeListed.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			lsOutput.push_back(ent->d_name);
		}
		closedir(dir);
	} else {
		/* could not open directory */
		localCommandOutput = "Cannot open directory";
		return;
	}
	sort(lsOutput.begin(), lsOutput.end());
	lsOutput.erase(lsOutput.begin());
	lsOutput.erase(lsOutput.begin());
	for (int i = 0; i < lsOutput.size(); i++) {
		localCommandOutput = localCommandOutput + lsOutput[i] + string("\n");
	}
	output = localCommandOutput;
}

void ListDirectoryContentsCommand::execute() {
	if (!serverExecutionPending) {
		//>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>;
		if (CommandPathUtil::specifiedPathExists(getPathSpecified()) &&
			CommandPathUtil::specifiedPathIsDirectory(getPathSpecified())) {
			//if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
			executeListDirectoryContentsCommandUtil(getPathSpecified());
			//>>>>>>>>>>>executionComplete();  //Call function to indicate command completed execution <reuben>
			//}
			//else {
			//  setCommandOutput(string("Error: Access Denied"));
			//>>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error:access denied <reuben>
			//  }
		} else {
			output = "Error: Invalid path (Path does not exist, or leads to a file, not directory)";
			//>>>>>>>>>executionIncomplete();  //Call function to indicate command completed execution with error: invalid path <reuben>
		}
	}
}

std::string ListDirectoryContentsCommand::getPathSpecified() {
	return parts[0];
}

int ListDirectoryContentsCommand::getType() {
	return TYPE;
}

bool ListDirectoryContentsCommand::isMatched(string command) {
	return command.substr(0, 2) == "ls";
}
