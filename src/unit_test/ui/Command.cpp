#include "ui/CommandInterpreter.hpp"

int main() {
  cout<<"\nEnter username: ";
  std::string username; cin>>username;
  cout<<"\nEnter password: ";
  std::string password; cin>>password;

  UserSessionDetail newUser(username, password);
  cin.ignore();
  cout<<"\nEnter a command (ls only currently): ";
  std::string rawCommand; getline(cin, rawCommand);
  Command newCommand = CommandInterpreter::interpretCommandType(rawCommand, newUser);
  //cout<<"\nCommand input is:"<<newCommand.getRawCommand();
  cout<<"\nOutput is:"<<newCommand.getCommandOutput();
  return 0;
}
