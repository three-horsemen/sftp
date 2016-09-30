#include "security/securesocket.hpp"
#include "shared/logger.hpp"
#include <iostream>
using namespace std;


bool SecureSocket::getValidity()
{
    return valid;
}
void SecureSocket::setValidity(bool newValidity)
{
    valid = newValidity;
}
int SecureSocket::getSocketDescriptor()
{
    return socketDescriptor;
}
void SecureSocket::setSocketDescriptor(int newSocketDescriptor)
{
    socketDescriptor = newSocketDescriptor;
}
string SecureSocket::getTargetIPAddress()
{
    return targetIPAddress;
}
void SecureSocket::setTargetIPAddress(string newTargetIPAddress)
{
    targetIPAddress = newTargetIPAddress;
}
string SecureSocket::getTargetPortNumber()
{
    return targetPortNumber;
}
void SecureSocket::setTargetPortNumber(string newTargetPortNumber)
{
    targetPortNumber = newTargetPortNumber;
}
string SecureSocket::getSourceIPAddress()
{
    return sourceIPAddress;
}
void SecureSocket::setSourceIPAddress(string newSourceIPAddress)
{
    sourceIPAddress = newSourceIPAddress;
}
string SecureSocket::getSourcePortNumber()
{
    return sourcePortNumber;
}
void SecureSocket::setSourcePortNumber(string newSourcePortNumber)
{
    sourcePortNumber = newSourcePortNumber;
}
string SecureSocket::getBuffer()
{
    return buffer;
}
void SecureSocket::setBuffer(string newBuffer)
{
    buffer = newBuffer;
}
int SecureSocket::initSecureSocket()
{
    setSocketDescriptor(socket(PF_INET,SOCK_STREAM,0));
    if(getSocketDescriptor() < 0)
    {
        cout << "The socket failed to create." << endl;
        setValidity(false);
    }
    else
    {
        cout << "The socket was successfully created." << endl;
        setValidity(true);
    }
    int force_reuse_socket_port__yes = 1;
    if (setsockopt(getSocketDescriptor(), SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes, sizeof(force_reuse_socket_port__yes)) == -1)
    {
        cout << "The socket couldn't be reused." << endl;
        setValidity(false);
    }
    else
    {
        cout << "The socket is being used successfully." << endl;
        setValidity(true);
    }

    cout << "initSecureSocket(), getSourceAddrFromSockDesc(): " << getSourceAddrFromSockDesc() << endl;
    cout << "initSecureSocket(), getSourcePortFromSockDesc(): " << getSourcePortFromSockDesc() << endl;

    //setSourceIPAddress(getSourceAddrFromSockDesc());
    //setSourcePortNumber(getSourcePortFromSockDesc());

    return getSocketDescriptor();
}

int SecureDataSocket::connectSecureSocket()
{
    int result = -2;
    if(getValidity() == true)
    {
        cout << "The socket descriptor for the client is: " << getSocketDescriptor() << endl;
        cout << "The target IP address for the client is: " << getTargetIPAddress() << endl;
        cout << "The target port number for the client is: " << getTargetPortNumber() << endl;
        struct sockaddr_in server_address;
        memset(&server_address,0,sizeof(server_address));
    	server_address.sin_family = AF_INET;
        char* targetPortNumber_charArray = string_to_charArray(getTargetPortNumber());
    	server_address.sin_port = htons(atoi(targetPortNumber_charArray));
        //free(targetPortNumber_charArray);
        char* targetIPAddress_charArray = string_to_charArray(getTargetIPAddress());
        printf("Printing the targetIPAddress_charArray: <%s>\n", targetIPAddress_charArray);
        server_address.sin_addr.s_addr = inet_addr(targetIPAddress_charArray);
        //free(targetIPAddress_charArray);

cout << endl << endl;

        cout << "Before the connect:" << endl;
        cout << "connectSecureSocket: The source IP address is " << getSourceAddrFromSockDesc() << endl;
        cout << "connectSecureSocket: The source port number is " << getSourcePortFromSockDesc() << endl;
        cout << "connectSecureSocket: The destination IP address is " << getTargetAddrFromSockDesc() << endl;
        cout << "connectSecureSocket: The destination port number is " << getTargetPortFromSockDesc() << endl;

cout << endl;

        result = connect(getSocketDescriptor(),(struct sockaddr*)&server_address,sizeof(server_address));
        if(result < 0)
        {
            setValidity(false);
            //cout << "Something went wrong with connect(), returning: " << result << endl;
            perror("Something went wrong with connect(): ");
        }
        else
        {
            cout << "Connect was successful!" << endl;
            setValidity(true);
        }

        cout << "After the connect:" << endl;
        cout << "connectSecureSocket: The source IP address is " << getSourceAddrFromSockDesc() << endl;
        cout << "connectSecureSocket: The source port number is " << getSourcePortFromSockDesc() << endl;
        cout << "connectSecureSocket: The destination IP address is " << getTargetAddrFromSockDesc() << endl;
        cout << "connectSecureSocket: The destination port number is " << getTargetPortFromSockDesc() << endl;

    }
    return result;
}

int SecureDataSocket::readSecureSocket()
{
    int len = -2;
    if(getValidity() == true)
    {
        char buffer[256];
        bzero(buffer,256);
        len = read(getSocketDescriptor(), buffer, sizeof(buffer));
        setBuffer(charArray_to_string(buffer, strlen(buffer)));
    }
    return len;
}

int SecureDataSocket::writeSecureSocket()
{
    int len = -2;
    if(getValidity() == true)
    {
        char* buffer_char = string_to_charArray(getBuffer());
        len = write(getSocketDescriptor(), buffer_char, strlen(buffer_char));
        free(buffer_char);
    }
    return len;
}

int SecureSocket::destroySecureSocket()
{
    return close(getSocketDescriptor());
}

string SecureSocket::getSourceAddrFromSockDesc()
{
    struct sockaddr tempSockAddr;
    socklen_t tempLen = sizeof(tempSockAddr);
    getsockname(getSocketDescriptor(), &tempSockAddr, &tempLen);
    return charArray_to_string(inet_ntoa(((struct sockaddr_in*)&tempSockAddr)->sin_addr));
}
string SecureSocket::getSourcePortFromSockDesc()
{
    struct sockaddr tempSockAddr;
    socklen_t tempLen = sizeof(tempSockAddr);
    getsockname(getSocketDescriptor(), &tempSockAddr, &tempLen);
    return int_to_string(ntohs(((struct sockaddr_in*)&tempSockAddr)->sin_port));
}
string SecureSocket::getTargetAddrFromSockDesc()
{
    struct sockaddr tempSockAddr;
    socklen_t tempLen = sizeof(tempSockAddr);
    getpeername(getSocketDescriptor(), &tempSockAddr, &tempLen);
    char *s = inet_ntoa(((struct sockaddr_in*)&tempSockAddr)->sin_addr);
    string result = charArray_to_string(s, strlen(s));
    //free(s);
    return result;
}
string SecureSocket::getTargetPortFromSockDesc()
{
    struct sockaddr tempSockAddr;
    socklen_t tempLen = sizeof(tempSockAddr);
    getpeername(getSocketDescriptor(), &tempSockAddr, &tempLen);
    string result = int_to_string(ntohs(((struct sockaddr_in*)&tempSockAddr)->sin_port));
    return result;
}




int SecureListenSocket::bindSecureSocket()
{
    int result = -2;
    if(getValidity() == true)
    {
        struct sockaddr_in servAddr;
        memset(&servAddr,0,sizeof(servAddr));
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = inet_addr(string_to_charArray(getSourceIPAddress()));
        servAddr.sin_port = htons(atoi(string_to_charArray(getSourcePortNumber())));
        result = bind(getSocketDescriptor(),(struct sockaddr*)&servAddr,sizeof(servAddr));
    }
    return result;
}

int SecureListenSocket::listenSecureSocket()
{
    int result = -2;
    if(getValidity() == true)
    {
        result = listen(getSocketDescriptor(),queueSize);
    }
    return result;
}

SecureDataSocket SecureListenSocket::acceptSecureSocket()
{
    SecureDataSocket newSecureDataSocket;
    newSecureDataSocket.setValidity(false);
    if(getValidity() == true)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int s = accept(getSocketDescriptor(), (struct sockaddr *)&clientAddr, &clientAddrLen);
/*
        newSecureDataSocket.setSocketDescriptor(s);
        newSecureDataSocket.setSourceIPAddress(this->getSourceIPAddress());
        newSecureDataSocket.setSourcePortNumber(this->getSourcePortNumber());
        newSecureDataSocket.setTargetIPAddress(newSecureDataSocket.getTargetAddrFromSockDesc());
        newSecureDataSocket.setTargetPortNumber(newSecureDataSocket.getTargetPortFromSockDesc());
        newSecureDataSocket.setValidity(true);
*/
        newSecureDataSocket.setSocketDescriptor(s);
        newSecureDataSocket.setSourceIPAddress(this->getSourceIPAddress());
        newSecureDataSocket.setSourcePortNumber(this->getSourcePortNumber());
        newSecureDataSocket.setTargetIPAddress(newSecureDataSocket.getTargetAddrFromSockDesc());
        newSecureDataSocket.setTargetPortNumber(newSecureDataSocket.getTargetPortFromSockDesc());
        newSecureDataSocket.setValidity(true);
    }
    return newSecureDataSocket;
}
