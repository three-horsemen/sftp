#include <ui/ServerUtil.hpp>
#include <iostream>
#include <fstream>

/*

Send and recv commands are basically user input.
So when user says send, client has to send and server receives
and when client says receive, server has to send and client receives.

*/

void ServerUtil::sendToClient(std::string recvCommand, std::string pathToJail) {
  /*when "recv <path>" then called*/

  std::string pathOfFileToBeSent = getAbsoluteServerPath(recvCommand, pathToJail);
  std::cout<<"\nCalculated path: "<<pathOfFileToBeSent;
  std::ifstream infile (pathOfFileToBeSent.c_str(), std::ifstream::in);
  std::string outputText;
  infile >> outputText;
  std::cout<<"\nRead from file: "<<outputText;
  infile.close();
  /*send this outputText*/
}

void ServerUtil::receiveFromClient(std::string sendCommand, std::string pathToJail) {
  /*when "send <path>" then called*/

  std::string pathToStoreIncomingFile = getAbsoluteServerPath(sendCommand, pathToJail);
  std::cout<<"\nCalculated path: "<<pathToStoreIncomingFile;
  std::ofstream outfile (pathToStoreIncomingFile.c_str(), std::ofstream::out);
  std::string receivedFromClient = "Dummy nonsense";
  std::cout<<"\nWrote to file: "<<receivedFromClient;
  outfile << receivedFromClient;
  outfile.close();
}

std::string ServerUtil::convertToAbsoluteServerPath(std::string rawCommand, std::string pathToJail) {
  int startPositionOfUsefulPath = rawCommand.find(std::string("://")) + 3;
  if(startPositionOfUsefulPath == std::string::npos) return rawCommand;
  std::string absolutePath = pathToJail + rawCommand.substr(startPositionOfUsefulPath, rawCommand.size());
  int commandLastPosition = rawCommand.find(std::string(" "));
  return (rawCommand.substr(0, commandLastPosition) + std::string(" ")+ absolutePath);
}

std::string ServerUtil::getAbsoluteServerPath(std::string rawCommand, std::string pathToJail) {
  int startPositionOfUsefulPath = rawCommand.find(std::string("://")) + 3;
  if(startPositionOfUsefulPath == std::string::npos) return rawCommand;
  std::string absolutePath = pathToJail + extractUsername(rawCommand)+ std::string("/") + rawCommand.substr(startPositionOfUsefulPath, rawCommand.size());
  return absolutePath;
}

std::string ServerUtil::extractUsername(std::string receivedCommand) {
  int lastPosition = receivedCommand.find(std::string("://"));
  int firstPosition = receivedCommand.find(std::string(" "));
  return receivedCommand.substr(firstPosition+1, lastPosition-firstPosition-1);
}
