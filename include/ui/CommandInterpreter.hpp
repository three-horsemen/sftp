#include "ui/Command.hpp"

class CommandInterpreter {
public:
  CommandInterpreter();
  static Command interpretCommandType(std::string rawCommand, UserSessionDetail newUser);
};
