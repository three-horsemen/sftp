#include <string>
#include <stdio.h>
#include <vector>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

class CommandPathUtil {
public:
  static std::string getCurrentWorkingDirectory();
  static bool specifiedPathExists(std::string pathSpecified);
  static std::string getPathSpecified(std::string rawCommand);
  static bool specifiedPathIsDirectory(std::string pathSpecified);
  static std::string findParentToGivenPath(std::string pathToNewDirectory);
  static void reduceToCanonicalForm(vector<std::string>& tokenizedPresentWorkingDirectory);
  //static bool prisonerIsLeavingJail(std::string rawCommand, PATH_TO_JAIL); //server side usage only
  static std::string convertToAbsolutePath(std::string pathSpecified, std::string presentWorkingDirectory);
};
