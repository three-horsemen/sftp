#include<string>
#include<stdio.h>
using namespace std;

class CommandPathUtil {
public:
  static size_t getPathSpecified(std::string rawCommand);
  static size_t getPathSpecified(std::string rawCommand, int fromThisPosition);
  static bool specifiedPathExists(std::string pathSpecified);
}
