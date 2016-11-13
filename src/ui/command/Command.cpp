//
// Created by reubenjohn on 13/11/16.
//

#include "ui/command/Command.hpp"

Command::Command() {
	rawCommand = string("");
}

Command::Command(std::string commandInput) {
	rawCommand = commandInput;
	//getInterpretedCommand(rawCommand);
}

std::string Command::getRawCommand() {
	return rawCommand;
}

vector<std::string> Command::getParts() {
	return parts;
}

std::string Command::getOutput() {
	return output;
}