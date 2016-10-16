#include "ui/Command.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

class ListDirectoryContentsCommand {
private:
  std::string pathSpecified;
  std::string commandOutput;
public:
  ListDirectoryContentsCommand();
  void executeListDirectoryContentsCommand();
  std::string getPathSpecified();
  std::string getRawCommand();
}
