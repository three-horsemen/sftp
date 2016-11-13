#include<string>
/* Function names as per client perspective */
/*  Send means send to client.
    Receive means get from server. */

class ServerUtil{
public:
  static void sendToClient(std::string, std::string);
  static void receiveFromClient(std::string, std::string);
  static std::string extractUsername(std::string);
  static std::string convertToAbsoluteServerPath(std::string rawCommand, std::string pathToJail);
  static std::string getAbsoluteServerPath(std::string rawCommand, std::string pathToJail);
};
