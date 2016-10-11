#include "ui/CommandPathFinder.hpp"

static std::string CommandPathFinder::getPathSpecified(std::string rawCommand) {
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
