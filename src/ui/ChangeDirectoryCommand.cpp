#include "ui/ChangeDirectoryCommand"
#include <iostream>
#include <unistd.h>
using namespace std;

int ChangeDirectoryCommand::ChangeDirectoryCommand() {
  std::string rawCommand = getRawCommand();
  setPathSpecified();
}

void ChangeDirectoryCommand::setPathSpecified() {
  pathSpecified = CommandPathFinder.getPathSpecified(rawCommand);
}

void executeChangeDirectoryCommand() {
  //Call function to indicate executing command
  
  //Call function to indicate command completed execution
}

void ChangeDirectoryCommand::setPathSpecified() {

}

/*
//Possibly useless
std::string ChangeDirectoryCommand::getCommandAndAttributesSpecified() {
  return commandAndAttributesSpecified;
}
*/
std::string ChangeDirectoryCommand::getPathSpecified() {
  return pathSpecified;
}

std::string ChangeDirectoryCommand::getRawCommand() {
  return Command::getRawCommand();
}
