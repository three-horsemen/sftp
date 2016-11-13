#include "ui/UserSessionDetail.hpp"

int main() {
  std::string username;
  std::string password;

  cout<<"\nEnter username: "; cin>>username;
  cout<<"Enter password: "; cin>>password;

  UserSessionDetail newUser(username, password);

  std::cout<<"User session details before logout:";
  newUser.display();

  std::cout<<"Sleeping for 2 seconds... and logging out for debugging purposes.\n";
  sleep(2);
  newUser.setLogoutTimestamp();

  std::cout<<"User session details after logout:\n";
  newUser.display();

  return 0;
}
