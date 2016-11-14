//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_LISTDIRECTORYCONTENTSCOMMAND_HPP
#define SFTP_LISTDIRECTORYCONTENTSCOMMAND_HPP


#include <ui/UserSessionDetail.hpp>
#include <ui/command/Command.hpp>
#include <ui/CommandInterpreter.hpp>

class ListDirectoryContentsCommand : public Command {
private:
public:
	static const int TYPE = 1;

	ListDirectoryContentsCommand(std::string &, std::string &);

	ListDirectoryContentsCommand(std::string &);

	void execute();

	int getType();

	void executeListDirectoryContentsCommandUtil(std::string pathToBeListed);

	void setPathSpecified();

	static bool isMatched(string command);

	std::string getPathSpecified();
};


#endif //SFTP_LISTDIRECTORYCONTENTSCOMMAND_HPP
