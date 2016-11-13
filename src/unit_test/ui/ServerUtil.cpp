#include <ui/ServerUtil.hpp>
#include <stdio.h>
#include <iostream>
#define JAIL_PATH "/home/ayushsoni/Desktop/ayushsoni/"
#define CMD_RECVD1 "send reuben://ayush/soni.txt"
#define CMD_RECVD2 "recv reuben://AyushSoni.txt"

int main() {
  std::cout<<"\nJail Path: "<<JAIL_PATH;
  std::cout<<"\nTesting sendToClient:";
  std::cout<<"\nCommand received by server: "<<CMD_RECVD2;
  std::cout<<"\nOutput: "; ServerUtil::sendToClient(CMD_RECVD2, JAIL_PATH);

  std::cout<<"\nTesting receiveFromClient:";
  std::cout<<"\nCommand received by server: "<<CMD_RECVD1;
  std::cout<<"\nOutput: "; ServerUtil::receiveFromClient(CMD_RECVD1, JAIL_PATH);
}
