#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "ui/CommandInterpreter.hpp"
#define ON_CLIENT true
#define DATABASE_NAME "SecureFTP"
#define LOGIN_ATTEMPTS 3

void displayInBoldAndRed(std::string message) {
  string displayMessage = string("\033[1;31m") + message+string("\033[0m");
  cout<<displayMessage;
}

void makeJailForUser(UserSessionDetail user) {
  //Make jail for this user at server
  cout<<"\n";
  user.getSecureDataSocket().encryptAndSend(user.getUsername());
}

void displayInBoldAndViolet(std::string message) {
  string displayMessage = string("\033[1;36m") + message+string("\033[0m");
  cout<<displayMessage;
}

std::string getPassword() {
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  displayInBoldAndViolet(string("Password: ")); std::string password; getline(cin, password);
  (void) tcsetattr (STDIN_FILENO, TCSAFLUSH, &oldt);
  return password;
}

int main() {
  int loginAttempts = LOGIN_ATTEMPTS;
  std::string password;
  SecureDataSocket clientSecureDataSocket("127.0.0.1", "6476", HOST_MODE_CLIENT);
  displayInBoldAndRed( string("\n\t\tWelcome to Secure File Transfer Protocol\n") );
  displayInBoldAndViolet(string("Initializing database...\n")); //DEBUG
  sftp::db::DbManager::initializeStaticDbManager(DATABASE_NAME);
  displayInBoldAndViolet( string("\n1. Register\n2. Authenticate\nPress any other key to exit\nChoice: ")); int choice; cin>>choice;
  if(choice!=1 && choice!=2) {
    displayInBoldAndRed(string("\n---Exiting---\n"));
    return 0;
  }
  std::cin.ignore();
  displayInBoldAndViolet(string("Username: ")); std::string userName; getline(cin, userName);
  password = getPassword();
  UserSessionDetail user(userName);
  user.setSecureDataSocket(clientSecureDataSocket);
  if(choice == 1) {
    while(true) {
      if(sftp::db::DbManager::getDb()->getUserManager().registerUser(user.getUsername(),password)) {
        displayInBoldAndViolet(string("\nSuccessfully registered user."));
        makeJailForUser(user);
        break;
      }
      else {
        displayInBoldAndRed(string("\nUnsuccessful in registering user."));
        cout<<"\n0. Exit\n1. Retry\nChoice: "; int retryOrNot; cin>>retryOrNot;
        std::cin.ignore();
        if(!retryOrNot) {
          displayInBoldAndRed(string("\n\t\tExiting"));
          return 0;
        }
        else {
          displayInBoldAndViolet(string("\nUsername: ")); getline(cin, userName);
          user.setUsername(userName);
          password = getPassword();
        }
      }
    }
  }

  else if(choice == 2){
    while(true) {
      if(sftp::db::DbManager::getDb()->getUserManager().isAuthenticationValid(user.getUsername(),password)) {
        displayInBoldAndViolet(string("\nLogin successful.\n"));
        break;
      } else {
        displayInBoldAndRed(string("\nLogin unsuccessful."));
        loginAttempts--;
        if(loginAttempts>0) {
          cout<<"\n0. Exit\n1. Retry";
          displayInBoldAndRed(string("(attempts left:")+std::to_string(loginAttempts)+string(")"));
          cout<<"\nChoice: "; int retryOrNot; cin>>retryOrNot;
          std::cin.ignore();
          if(!retryOrNot) {
            displayInBoldAndRed(string("\n\t\tExiting"));
            return 0;
          }
          else {
            displayInBoldAndViolet(string("\nUsername: ")); getline(cin, userName);
            user.setUsername(userName);
            password = getPassword();
          }
        }
      }
    }
  }
  bool running = true;
  Command command(string("ls"),user);
  /* Sending username to server */
  user.getSecureDataSocket().encryptAndSend(user.getUsername());
  while(running) {
    displayInBoldAndViolet(string("\n") + user.getUsername()); displayInBoldAndRed(string("@client-sftp"));
    cout << command.getUserSessionDetail().getPresentWorkingDirectory() << "$ " ;
    std::string rawCommand; getline(cin, rawCommand);
    if(rawCommand.compare("quit")==0) {
      running = false;
      continue;
    }
    try{
      Command tempCommand = CommandInterpreter::interpretCommandType(rawCommand, user, ON_CLIENT); //true for client, false for server
      command = tempCommand;
    } catch(UIException &exception) {
      LOG_ERROR << exception.what();
      continue;
    }
    user = command.getUserSessionDetail();
    cout << command.getCommandOutput();
  }
}
