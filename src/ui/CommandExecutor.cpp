#include <stdio.h>
#include <string>
#include <iostream>
#include "ui/CommandExecutor"

static std::string CommandExecutor::executeCommand() {
  char buffer[1024];
  string commandOutput = "";
  string commandInput;
  cout<<"\nEnter the command string: "; getline(cin, commandInput);
  std::tr1::shared_ptr<FILE> pipe(popen(commandInput.c_str(), "r"), pclose);
  if (!pipe) throw std::runtime_error("Internal error: popen() failed!");
  while (!feof(pipe.get())) {
      if (fgets(buffer, 1024, pipe.get()) != NULL)
         commandOutput+=buffer;
  }
  return commandOutput;
}

static std::string CommandExecutor::executeCommand(std::string commandInput) {
  char buffer[1024];
  string commandOutput = "";
  std::tr1::shared_ptr<FILE> pipe(popen(commandInput.c_str(), "r"), pclose);
  if (!pipe) throw std::runtime_error("Internal error: popen() failed!");
  while (!feof(pipe.get())) {
      if (fgets(buffer, 1024, pipe.get()) != NULL)
        commandOutput+=buffer;
  }
  return commandOutput;
}
