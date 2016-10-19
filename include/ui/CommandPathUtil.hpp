#include <string>
#include <stdio.h>
#include <vector>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

class CommandPathUtil {
public:
  static std::string getPathSpecified(std::string rawCommand);
  static std::string getPathSpecified(std::string rawCommand, int fromThisPosition);
  static bool specifiedPathExists(std::string pathSpecified);
  static std::string convertToAbsolutePath(std::string pathSpecified, std::string presentWorkingDirectory);
  static bool specifiedPathIsDirectory(std::string pathSpecified);
  static std::string getCurrentWorkingDirectory();
};
