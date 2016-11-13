//
// Created by reubenjohn on 13/11/16.
//

#include "ui/command/ChangeDirectoryCommand.hpp"

ChangeDirectoryCommand::ChangeDirectoryCommand(std::string commandInput, std::string pwd) : Command(commandInput) {
	parts.push_back(
			CommandPathUtil::convertToAbsolutePath(CommandPathUtil::getPathSpecified(Command::getRawCommand())[0],
												   pwd));
}

std::string ChangeDirectoryCommand::getPathSpecified() {
	return parts[0];
}

void ChangeDirectoryCommand::execute() {
	if (CommandPathUtil::specifiedPathExists(getPathSpecified())) {
		if (CommandPathUtil::specifiedPathIsDirectory(getPathSpecified())) {
			output = "Successfully changed directory to " + getPathSpecified();
		} else {
			throw UIException(NOT_A_DIRECTORY);
		}
	} else {
		throw UIException(PATH_DOES_NOT_EXIST);
	}
}

std::string ChangeDirectoryCommand::getPathSpecified(Command &command) {
	command.getParts()[0];
}

int ChangeDirectoryCommand::getType() {
	return TYPE;
}
