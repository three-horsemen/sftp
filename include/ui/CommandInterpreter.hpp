#include "ui/Command.hpp"

class CommandInterpreter {
public:
  CommandInterpreter();
  bool isOfType(std::string rawCommand, std::string type);
  static bool interpretIfOnServerExecution(std::string rawCommand);
  static Command interpretCommandType(std::string rawCommand, UserSessionDetail& newUser, bool isCurrentlyOnClientSide);
};
