#include <sys/stat.h>
#include "ui/CommandPathUtil.hpp"
using namespace std;

static std::string CommandPathUtil::getPathSpecified(std::string rawCommand) {
  //Finds pathSpecified
  int pathStartPosition, pathEndPosition;
  for(int i=0;i<rawCommand.size();i++) {
    if(rawCommand[i] == ' ' && rawCommand[i+1] != '-' && rawCommand[i+1] != ' ') {
      pathStartPosition = i+1;
      break;
    }
    else if(i==rawCommand.size()-1) {
      return string("");
    }
  }
  for(pathEndPosition = pathStartPosition ; pathEndPosition<rawCommand.size() && rawCommand[pathEndPosition] != ' ' ; pathEndPosition++);
  pathEndPosition--;
  return rawCommand.substr(pathStartPosition,pathEndPosition);
}

static std::string CommandPathUtil::getPathSpecified(std::string rawCommand, int fromThisPosition) {
  //Finds pathSpecified
  int pathStartPosition, pathEndPosition;
  for(int i=fromThisPosition;i<rawCommand.size();i++) {
    if(rawCommand[i]==' '&&rawCommand[i+1]!='-'&&rawCommand[i+1]!=' ') {
      pathStartPosition = i+1;
      break;
    }
    else if(i==rawCommand.size()-1) {
      return string("");
    }
  }
  for(pathEndPosition=pathStartPosition;pathEndPosition<rawCommand.size()&&rawCommand[pathEndPosition]!=' ';pathEndPosition++);
  pathEndPosition--;
  return rawCommand.substr(pathStartPosition,pathEndPosition);
}

static bool CommandPathUtil::specifiedPathExists(std::string pathSpecified) {
  struct stat st;
  if (stat(pathSpecified.c_str(),&st)==0)
    return true;
      //cout<<"PATH IS VALID.";
  else
    return false;
      //cout<<"INVALID PATH.";
}

static std::string CommandPathUtil::convertToAbsolutePath(std::string pathSpecified, std::string presentWorkingDirectory) {
  if(pathSpecified.size()!=0 && pathSpecified[0]=='/') return pathSpecified;
  std::vector<std::string> tokenizedPresentWorkingDirectory;
	std::string newWorkingDirectory;
	presentWorkingDirectory = presentWorkingDirectory + string("/") + pathSpecified;
	boost::split(tokenizedPresentWorkingDirectory, presentWorkingDirectory, boost::is_any_of("/"), boost::token_compress_on);
	tokenizedPresentWorkingDirectory.erase(
    std::remove_if(
        tokenizedPresentWorkingDirectory.begin(),
        tokenizedPresentWorkingDirectory.end(),
        [](std::string const& tempString) { return tempString.size()==0; }),
    tokenizedPresentWorkingDirectory.end());
	/*cout<<"\nTokenized presentWorkingDirectory:\n";
	for(int i=0;i<tokenizedPresentWorkingDirectory.size();i++){
		cout<<tokenizedPresentWorkingDirectory[i]<<endl;
	}
  */
	for(int i=0; i<tokenizedPresentWorkingDirectory.size();i++) {
		newWorkingDirectory =newWorkingDirectory + string("/")+ tokenizedPresentWorkingDirectory[i];
	}
	return newWorkingDirectory;
}

static bool CommandPathUtil::specifiedPathIsDirectory(std::string pathSpecified) {
  struct stat st;
  if (stat(pathSpecified.c_str(),&st)==0) {
    if ( st.st_mode & S_IFDIR ) return true;
    else return false;
  }
  else
    return false;
}
