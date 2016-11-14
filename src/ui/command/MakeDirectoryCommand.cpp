//
// Created by reubenjohn on 13/11/16.
//

#include "ui/command/MakeDirectoryCommand.hpp"

MakeDirectoryCommand::MakeDirectoryCommand(std::string &commandInput, std::string &pwd) : Command(commandInput) {
	if (commandInput.find("://") != string::npos) {
		serverExecutionPending = true;
	} else {
		serverExecutionPending = false;
		parts.push_back(CommandPathUtil::convertToAbsolutePath(CommandPathUtil::getPathSpecified(rawCommand)[0], pwd));
	}
}

void MakeDirectoryCommand::execute() {
	if (!serverExecutionPending) {
		//>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
		std::string pathToParentDirectoryOfNewDirectory = CommandPathUtil::findParentToGivenPath(getPathSpecified());
		if (CommandPathUtil::specifiedPathExists(pathToParentDirectoryOfNewDirectory) &&
			CommandPathUtil::specifiedPathIsDirectory(pathToParentDirectoryOfNewDirectory)) {
			//if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
			executeMakeDirectoryCommandUtil(getPathSpecified());
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

int MakeDirectoryCommand::getType() {
	return 3;
}


void MakeDirectoryCommand::executeMakeDirectoryCommandUtil(std::string pathToNewDirectory) {
	boost::filesystem::path dir(pathToNewDirectory.c_str());
	if (boost::filesystem::create_directory(dir)) {
		output = string("Directory created: ") + pathToNewDirectory;
	} else {
		output = string("Internal error occured while creating directory.");
	}
}

std::string MakeDirectoryCommand::getPathSpecified() {
	return parts[0];
}

bool MakeDirectoryCommand::isMatched(string command) {
	return command.substr(0, 5) == "mkdir";
}