#include "ui/CommandInterpreter.hpp"

int main() {
  cout<<"\nEnter username: ";
  std::string username; cin>>username;
  cout<<"\nEnter password: ";
  std::string password; cin>>password;
  cin.ignore(); //IMPORTANT

  UserSessionDetail newUser(username, password);

  cout<<"\nEnter a command (ls only currently): ";
  std::string rawCommand; getline(cin, rawCommand);
  Command newCommand = CommandInterpreter::interpretCommandType(rawCommand, newUser, false); //true for client, false for server
  //cout<<"\nCommand input is:"<<newCommand.getRawCommand();
  cout<<"\nOutput is:"<<newCommand.getCommandOutput();
  return 0;
}
