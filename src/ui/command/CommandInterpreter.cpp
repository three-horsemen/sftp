//
// Created by reubenjohn on 13/11/16.
//

#include "ui/CommandInterpreter.hpp"

bool CommandInterpreter::interpretIfOnServerExecution(std::string rawCommand) {
	vector<std::string> tokenizedSourcePath;
	boost::split(tokenizedSourcePath, rawCommand, boost::is_any_of(" "), boost::token_compress_on);
	if (tokenizedSourcePath.size() > 1) {
		std::size_t found = tokenizedSourcePath[1].find(string("://"));
		return found != std::string::npos;
	} else return false;
}

Command *CommandInterpreter::getInterpretedCommand(std::string rawCommand, std::string pwd) {
	boost::trim_all(rawCommand);
	if ((rawCommand[rawCommand.size() - 1] == '/') || (rawCommand[rawCommand.size() - 1] == '\\')) {
		rawCommand = rawCommand.substr(0, rawCommand.size() - 1);
	}
	if (rawCommand.compare(0, 2, "ls") == 0) {
		return new ListDirectoryContentsCommand(rawCommand, pwd);
	} else if (rawCommand.compare(0, 2, "cd") == 0) {
		return new ChangeDirectoryCommand(rawCommand, pwd);
	} else if (rawCommand.compare(0, 5, "mkdir") == 0) {
		return new MakeDirectoryCommand(rawCommand, pwd);
	} else if (rawCommand.compare(0, 2, "rm") == 0) {
		return new RemoveCommand(rawCommand, pwd);
	}
/*  else if(rawCommand.compare(0,2,"cp")){
    return CopyFilesAndDirectoriesCommand(rawCommand, newUser);
  }
  else if(rawCommand.compare(0,5,"chown")){
    return ChangeFileOwnerAndGroupCommand(rawCommand, newUser);
  }*/
	else {
		throw UIException(INVALID_COMMAND, string("Invalid command: ") + rawCommand);
	}
}