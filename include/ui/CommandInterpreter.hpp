#include "ui/Command.hpp"

class CommandInterpreter {
public:
  CommandInterpreter();
  static bool interpretIfOnServerExecution(std::string rawCommand);
  static Command interpretCommandType(std::string rawCommand, UserSessionDetail& newUser, bool isCurrentlyOnClientSide);
};
