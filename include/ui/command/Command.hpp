//
// Created by reubenjohn on 13/11/16.
//

#ifndef SFTP_COMMAND_HPP
#define SFTP_COMMAND_HPP

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include "shared/logger.hpp"
#include "database/DbManager.hpp"
#include "ui/UserSessionDetail.hpp"

class Command {
protected:
	std::string rawCommand, output;
	vector<std::string> parts;
public:
	Command();

	Command(std::string commandInput);

	std::string getRawCommand();

	vector<std::string> getParts();

	std::string getOutput();

	virtual void execute() = 0;

	virtual int getType() = 0;
};


#endif //SFTP_COMMAND_HPP
