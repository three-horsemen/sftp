#include<stdlib.h>
#include "ui/Command.hpp"
using namespace std;

class ChangeDirectoryCommand : public Command {
private:
  //std::string commandAndAttributesSpecified; //possibly useless
  std::string pathSpecified;
public:
  ChangeDirectoryCommand();
  void executeChangeDirectoryCommand();
  //std::string getCommandAndAttributesSpecified(); //possibly useless
  std::string getPathSpecified();
}
