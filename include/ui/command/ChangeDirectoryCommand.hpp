//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_CHANGEDIRECTORYCOMMAND_HPP
#define SFTP_CHANGEDIRECTORYCOMMAND_HPP

#include <ui/command/Command.hpp>
#include <ui/UIException.hpp>

class ChangeDirectoryCommand : public Command {
public:
	static const int TYPE = 2;

	ChangeDirectoryCommand(std::string &, std::string &);

	void execute();

	int getType();

	std::string getPathSpecified();

	static std::string getPathSpecified(Command &command);
};


#endif //SFTP_CHANGEDIRECTORYCOMMAND_HPP
