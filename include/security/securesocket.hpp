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

class DHKeyContainer
{
private:
    static const int goodPrimePThreshold;
    static const int goodPrimeQThreshold;
    static const std::string goodLocalPrivateThreshold;
    static const std::string goodLocalPublicThreshold;
    static const std::string goodRemotePublicThreshold;
    static const std::string goodSharedSecretThreshold;

    bool valid;
    int primeP;
    int primeQ;
    std::string localPrivate;
    std::string localPublic;
    std::string remotePublic;
    std::string sharedSecret;
public:
    DHKeyContainer();
    bool isGoodPrimeP();
    bool isGoodPrimeQ();
    bool isGoodLocalPrivate();
    bool isGoodLocalPublic();
    bool isGoodRemotePublic();
    bool isGoodSharedSecret();
    void setValidity(bool newValidity);
    bool getValidity();
    int getPrimeP();
    void setPrimeP(int p);
    int getPrimeQ();
    void setPrimeQ(int q);
    std::string getLocalPrivate();
    void setLocalPrivate(std::string newLocalPrivate);
    std::string getLocalPublic();
    void setLocalPublic(std::string newLocalPublic);
    std::string getRemotePublic();
    void setRemotePublic(std::string newRemotePublic);
    std::string getSharedSecret();
    void setSharedSecret(std::string newSharedSecret);
};

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
    SecureSocket();
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
private:
    DHKeyContainer keyContainer;
public:
    DHKeyContainer getKeyContainer();
    int connectSecureSocket();
    int readSecureSocket();
    int writeSecureSocket();

    int performDHExchange_asClient();
    int performDHExchange_asServer();
};

class SecureListenSocket : public SecureSocket
{
private:
    static const int queueSize;
public:
    int bindSecureSocket();
    int listenSecureSocket();
    SecureDataSocket acceptSecureSocket();
};
