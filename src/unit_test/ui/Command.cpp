#include "ui/CommandInterpreter.hpp"

int main() {
  cout<<"\nEnter username: ";
  std::string username; cin>>username;
  cout<<"Enter password: ";
  std::string password; cin>>password;
  cin.ignore(); //IMPORTANT
  UserSessionDetail newUser(username, password);
  Command newCommand;
  cout<<"UI SFTP\nTry out the following commands:\n";
  cout<<"1. List directory contents command: ls [path]\n2. Change working directory: cd [path]\n3. Make a new directory: mkdir [path]\n4. Remove directoy: rm [path]";
  while(true) {
  cout<<endl<<newUser.getUsername()<<"@client-sftp:"<<newCommand.getUserSessionDetail().getPresentWorkingDirectory()<<"$ ";
  std::string rawCommand; getline(cin, rawCommand);
  newCommand = CommandInterpreter::interpretCommandType(rawCommand, newUser, false); //true for client, false for server
  newUser = newCommand.getUserSessionDetail();
  cout<<newCommand.getCommandOutput();
}
  return 0;
}
