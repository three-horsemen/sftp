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

    string sourceIPAddress;
    string sourcePortNumber;

    string buffer;
public:
    void setValidity(bool newValidity);
    bool getValidity();
    int getSocketDescriptor();
    void setSocketDescriptor(int newSocketDescriptor);
    string getTargetIPAddress();
    void setTargetIPAddress(string newTargetIPAddress);
    string getTargetPortNumber();
    void setTargetPortNumber(string newTargetPortNumber);

    string getSourceIPAddress();
    void setSourceIPAddress(string newSourceIPAddress);
    string getSourcePortNumber();
    void setSourcePortNumber(string newSourcePortNumber);

    string getBuffer();
    void setBuffer(string newBuffer);

    int initSecureSocket();
    int destroySecureSocket();

    string getTargetAddrFromSockDesc();
    string getTargetPortFromSockDesc();
    string getSourceAddrFromSockDesc();
    string getSourcePortFromSockDesc();
};

class SecureDataSocket : public SecureSocket
{
public:
    int connectSecureSocket();
    int readSecureSocket();
    int writeSecureSocket();
};

class SecureListenSocket : public SecureSocket
{
private:
    static const int queueSize = 16;
public:
    int bindSecureSocket();
    int listenSecureSocket();
    SecureDataSocket acceptSecureSocket();
};
