//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_REMOVECOMMAND_HPP
#define SFTP_REMOVECOMMAND_HPP

#include <boost/filesystem.hpp>
#include <ui/command/Command.hpp>

class RemoveCommand : public Command {
private:
public:
	RemoveCommand(std::string &, string &);

	void execute();

	int getType();

	void executeRemoveCommandUtil(std::string pathSpecified);

	void setPathSpecified();

	std::string getPathSpecified();
};


#endif //SFTP_REMOVECOMMAND_HPP
