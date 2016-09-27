#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "security/cryptmath.hpp"
#include "security/cryptstr.hpp"
#include "security/encrypt.hpp"

class SecureSocket
{
private:
    bool valid;
    int socketDescriptor;
    string targetIPAddress;
    string targetPortNumber;

    string buffer;
public:
    bool getValidity();
    void setValidity(bool newValidity);
    int getSocketDescriptor();
    void setSocketDescriptor(int newSocketDescriptor);
    string getTargetIPAddress();
    void setTargetIPAddress(string newTargetIPAddress);
    string getTargetPortNumber();
    void setTargetPortNumber(string newTargetPortNumber);

    string getBuffer();
    void setBuffer(string newBuffer);

    int initSecureSocket();
    void connectSecureSocket();
    int destroySecureSocket();
    int readSecureSocket();
    int writeSecureSocket();

};
