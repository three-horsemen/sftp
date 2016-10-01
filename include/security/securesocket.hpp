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
    std::string targetIPAddress;
    std::string targetPortNumber;

    std::string sourceIPAddress;
    std::string sourcePortNumber;

    std::string buffer;
public:
    void setValidity(bool newValidity);
    bool getValidity();
    int getSocketDescriptor();
    void setSocketDescriptor(int newSocketDescriptor);
    std::string getTargetIPAddress();
    void setTargetIPAddress(std::string newTargetIPAddress);
    std::string getTargetPortNumber();
    void setTargetPortNumber(std::string newTargetPortNumber);

    std::string getSourceIPAddress();
    void setSourceIPAddress(std::string newSourceIPAddress);
    std::string getSourcePortNumber();
    void setSourcePortNumber(std::string newSourcePortNumber);

    std::string getBuffer();
    void setBuffer(std::string newBuffer);

    int initSecureSocket();
    int destroySecureSocket();

    std::string getTargetAddrFromSockDesc();
    std::string getTargetPortFromSockDesc();
    std::string getSourceAddrFromSockDesc();
    std::string getSourcePortFromSockDesc();
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
