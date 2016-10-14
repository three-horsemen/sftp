#include <sys/stat.h>
#include "ui/CommandPathUtil.hpp"

static std::string CommandPathUtil::getPathSpecified(std::string rawCommand) {
  //Finds pathSpecified
  int pathStartPosition, pathEndPosition;
  for(int i=0;i<rawCommand.size();i++) {
    if(rawCommand[i]==' '&&rawCommand[i+1]!='-'&&rawCommand[i+1]!=' ') {
      pathStartPosition = i+1;
      break;
    }
    else if(i==rawCommand.size()-1) {
      return NULL;
    }
  }
  for(pathEndPosition=pathStartPosition;pathEndPosition<rawCommand.size()&&rawCommand[pathEndPosition]!=' ';pathEndPosition++);
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
      return NULL;
    }
  }
  for(pathEndPosition=pathStartPosition;pathEndPosition<rawCommand.size()&&rawCommand[pathEndPosition]!=' ';pathEndPosition++);
  pathEndPosition--;
  return rawCommand.substr(pathStartPosition,pathEndPosition);
}

static bool CommandPathUtil::specifiedPathExists(std::string pathSpecified) {
  struct stat st;
  string filePath= "/home/ayushsoni/Desktop/MyStuff";
  if (stat(filePath.c_str(),&st)==0)
    return true;
      //cout<<"PATH IS VALID.";
  else
    return false;
      //cout<<"INVALID PATH.";
}
