#include "ui/Command.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

class ListDirectoryContentsCommand {
private:
  std::string pathSpecified;
  std::string attributesSpecified;
public:
  ListDirectoryContentsCommand();
  void executeListDirectoryContentsCommand();
  void executeListDirectoryContentsCommandUtil();
  void setPathSpecified();
  std::string getPathSpecified();
}
