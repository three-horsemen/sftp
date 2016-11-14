//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_MAKEDIRECTORYCOMMAND_HPP
#define SFTP_MAKEDIRECTORYCOMMAND_HPP

#include <boost/filesystem.hpp>

#include <ui/command/Command.hpp>

class MakeDirectoryCommand : public Command {
private:
public:
	MakeDirectoryCommand(std::string &, std::string &);

	void execute();

	int getType();

	void executeMakeDirectoryCommandUtil(std::string pathToNewDirectory);

	void setPathSpecified();

	std::string getPathSpecified();

	static bool isMatched(string command);
};


#endif //SFTP_MAKEDIRECTORYCOMMAND_HPP
