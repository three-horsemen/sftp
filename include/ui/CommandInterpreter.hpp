//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_COMMANDINTERPRETER2_HPP
#define SFTP_COMMANDINTERPRETER2_HPP

#include <boost/algorithm/string/trim_all.hpp>

#include <ui/command/Command.hpp>
#include <ui/command/ChangeDirectoryCommand.hpp>
#include <ui/command/MakeDirectoryCommand.hpp>
#include <ui/command/RemoveCommand.hpp>
#include <ui/command/ListDirectoryContentsCommand.hpp>

class CommandInterpreter {
public:
	CommandInterpreter();

	bool isOfType(std::string, std::string);

	static bool interpretIfOnServerExecution(std::string);

	static Command* getInterpretedCommand(std::string, std::string);
};


#endif //SFTP_COMMANDINTERPRETER2_HPP
