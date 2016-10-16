#include "ui/ListDirectoryContentsCommand.hpp"
#include "ui/CommandPathUtil"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <vector>

using namespace std;

ListDirectoryContentsCommand::ListDirectoryContentsCommand () {
  setPathSpecified();

}

ListDirectoryContentsCommand::setPathSpecified() {
  pathSpecified = CommandPathUtil.getPathSpecified(rawCommand);
}
