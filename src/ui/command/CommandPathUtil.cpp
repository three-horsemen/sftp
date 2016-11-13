#include "ui/CommandPathUtil.hpp"

std::vector<std::string> CommandPathUtil::getPathSpecified(std::string rawCommand) {
	//Finds pathSpecified
	int pathStartPosition, pathEndPosition;
	for (int i = 0; i < rawCommand.size(); i++) {
		if (rawCommand[i] == ' ' && rawCommand[i + 1] != '-' && rawCommand[i + 1] != ' ') {
			pathStartPosition = i + 1;
			break;
		} else if (i == rawCommand.size() - 1) {
			std::vector<std::string> emptyStringVector;
			emptyStringVector.push_back(string(" "));
			return emptyStringVector;
		}
	}
	for (pathEndPosition = pathStartPosition;
		 pathEndPosition < rawCommand.size() && rawCommand[pathEndPosition] != ' '; pathEndPosition++);
	pathEndPosition -= 3;
	std::vector<std::string> paths;
	paths.push_back(rawCommand.substr(pathStartPosition, pathEndPosition));
	if ((rawCommand.size() - (pathEndPosition + 2)) > 3)
		paths.push_back(rawCommand.substr(pathEndPosition + 2, rawCommand.size()));
	return paths;
}

bool CommandPathUtil::specifiedPathExists(std::string pathSpecified) {
	struct stat st;
	if (stat(pathSpecified.c_str(), &st) == 0)
		return true;
		//cout<<"PATH IS VALID.";
	else
		return false;
	//cout<<"INVALID PATH.";
}

void CommandPathUtil::reduceToCanonicalForm(vector<std::string> &tokenizedPresentWorkingDirectory) {
	for (int i = 1; i < tokenizedPresentWorkingDirectory.size(); i++) {
		boost::trim(tokenizedPresentWorkingDirectory[i]);
		if (tokenizedPresentWorkingDirectory[i].compare(string("..")) == 0) {
			while (i > 0 && tokenizedPresentWorkingDirectory[i].compare(string("..")) == 0) {
				tokenizedPresentWorkingDirectory.erase(tokenizedPresentWorkingDirectory.begin() + i);
				tokenizedPresentWorkingDirectory.erase(tokenizedPresentWorkingDirectory.begin() + i - 1);
				i--;
			}
		}
	}
	if (tokenizedPresentWorkingDirectory.size() == 1 &&
		tokenizedPresentWorkingDirectory[0].compare(string("..")) == 0) {
		tokenizedPresentWorkingDirectory[0] = string("");
	}
}

std::string CommandPathUtil::convertToAbsolutePath(std::string pathSpecified, std::string presentWorkingDirectory) {
	if (pathSpecified.size() != 0 && pathSpecified[0] == '/') {
		return pathSpecified;
	} else if (pathSpecified.size() == 0) {
		return presentWorkingDirectory;
	} else {
		std::vector<std::string> tokenizedPresentWorkingDirectory;
		std::string newWorkingDirectory;
		presentWorkingDirectory = presentWorkingDirectory + string("/") + pathSpecified;
		boost::split(tokenizedPresentWorkingDirectory, presentWorkingDirectory, boost::is_any_of("/"),
					 boost::token_compress_on);
		tokenizedPresentWorkingDirectory.erase(
				std::remove_if(
						tokenizedPresentWorkingDirectory.begin(),
						tokenizedPresentWorkingDirectory.end(),
						[](std::string const &tempString) { return tempString.size() == 0; }),
				tokenizedPresentWorkingDirectory.end());
		reduceToCanonicalForm(tokenizedPresentWorkingDirectory);
		int size = tokenizedPresentWorkingDirectory.size();
		if (tokenizedPresentWorkingDirectory.size() == 0) {
			return string("/");
		}
		for (int i = 0; i < size; i++) {
			newWorkingDirectory = newWorkingDirectory + string("/") + tokenizedPresentWorkingDirectory[i];
		}
		return newWorkingDirectory;
	}
}

std::string CommandPathUtil::findParentToGivenPath(std::string pathToNewDirectory) {
	std::size_t parentPathEndPosition = pathToNewDirectory.find_last_of("/\\");
	if (parentPathEndPosition != std::string::npos) {
		return pathToNewDirectory.substr(0, parentPathEndPosition);
	}
	return pathToNewDirectory;
}

bool CommandPathUtil::specifiedPathIsDirectory(std::string pathSpecified) {
	struct stat st;
	if (stat(pathSpecified.c_str(), &st) == 0) {
		if (st.st_mode & S_IFDIR) return true;
		else return false;
	} else
		return false;
}

std::string CommandPathUtil::getCurrentWorkingDirectory() {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return string(cwd);
	else
		perror("Couldn't get the present working directory. <getcwd() error>");
	return string("NULL");
}
