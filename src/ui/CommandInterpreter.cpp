#include "ui/CommandInterpreter.hpp"

bool CommandInterpreter::interpretIfOnServerExecution(std::string rawCommand) {
  vector<std::string> tokenizedSourcePath;
  boost::split(tokenizedSourcePath, rawCommand, boost::is_any_of(" "), boost::token_compress_on);
  if(tokenizedSourcePath.size()>1) {
    std::size_t found = tokenizedSourcePath[1].find(string("://"));
    if(found!=std::string::npos)
    return true;
    else return false;
  }
  else return false;
}

Command CommandInterpreter::interpretCommandType(std::string rawCommand, UserSessionDetail& newUser, bool isCurrentlyOnClientSide) {
  boost::trim_all(rawCommand);
  if((rawCommand[rawCommand.size()-1]=='/') || (rawCommand[rawCommand.size()-1]=='\\')) {
    rawCommand = rawCommand.substr(0, rawCommand.size()-1);
  }
  if(isCurrentlyOnClientSide && interpretIfOnServerExecution(rawCommand)) {
    //Send to server /* SOORYA */
    //receive the output in a string 'outputFromServer' /* SOORYA */
    Command newCommand(rawCommand, newUser);
    //newCommand.setCommandOutput(outputFromServer);
    return newCommand;
  }
  if(rawCommand.compare(0,2,"cd")==0) {
    //return ChangeDirectoryCommand(rawCommand, newUser);
    ChangeDirectoryCommand c_temp = ChangeDirectoryCommand(rawCommand, newUser);
    //cout << endl <<  c_temp.getUserSessionDetail().getPresentWorkingDirectory() << " HAHAHA" << endl;
    return c_temp;
  }
  else if(rawCommand.compare(0,2,"ls")==0) {
    return ListDirectoryContentsCommand(rawCommand, newUser);
  }
  else if(rawCommand.compare(0,5,"mkdir")==0){
    return MakeDirectoryCommand(rawCommand, newUser);
  }
  else if(rawCommand.compare(0,2,"rm")==0){
    return RemoveCommand(rawCommand, newUser);
  }
  else if(rawCommand.compare(0,2,"cp")){
    return CopyFiles(rawCommand, newUser);
  }
  /*
  else if(rawCommand.compare(0,5,"chown")){
    return ChangeFileOwnerAndGroupCommand(rawCommand, newUser);
  }*/
  else {
    throw UIException(INVALID_COMMAND);
  }
}
