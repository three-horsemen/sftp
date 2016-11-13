//
// Created by reubenjohn on 13/11/16.
//

#include <ui/command/RemoveCommand.hpp>

RemoveCommand::RemoveCommand(std::string commandInput, string pwd) : Command(commandInput) {
	parts.push_back(CommandPathUtil::convertToAbsolutePath(getPathSpecified(), pwd));
}

void RemoveCommand::execute() {
	//>>>>>>>>>>>>>executionCommenced(); //Call function to indicate executing command <<<REUBEN>>>
	if (CommandPathUtil::specifiedPathExists(getPathSpecified())) {
		//if(isPermittedUser()) { //isPermittedUser() is <<<REUBEN's Function>>>
		executeRemoveCommandUtil(getPathSpecified());
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

int RemoveCommand::getType() {
	return 4;
}

void RemoveCommand::executeRemoveCommandUtil(std::string pathSpecified) {
	boost::filesystem::path p = pathSpecified.c_str();
	boost::filesystem::remove_all(p);
	output = "Successfully removed: ";
}

std::string RemoveCommand::getPathSpecified() {
	return pathSpecified;
}