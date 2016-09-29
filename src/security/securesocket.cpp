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


    return getSocketDescriptor();
}

int SecureSocket::connectSecureSocket()
{
    int result = -2;
    if(getValidity() == true)
    {
        struct sockaddr_in server_address;
        memset(&server_address,0,sizeof(server_address));
    	server_address.sin_family = AF_INET;
        char* targetPortNumber_charArray = string_to_charArray(getTargetPortNumber());
    	server_address.sin_port = htons(atoi(targetPortNumber_charArray));
        free(targetPortNumber_charArray);
        char* targetIPAddress_charArray = string_to_charArray(getTargetIPAddress());
        server_address.sin_addr.s_addr = inet_addr(targetIPAddress_charArray);
        free(targetIPAddress_charArray);
        //server_address.sin_addr.s_addr = inet_addr(server_ip_address);
        char* s = inet_ntoa(((struct sockaddr_in*)&server_address)->sin_addr);
        cout << "Before the connect:" << endl;
        cout << "connectSecureSocket: The IP address is " << charArray_to_string(s, strlen(s)) << endl;
        cout << "connectSecureSocket: The port number is " << ntohs(((struct sockaddr_in*)&server_address)->sin_port) << endl;
        result = connect(getSocketDescriptor(),(struct sockaddr*)&server_address,sizeof(server_address));
        if(result < 0)
        {
            setValidity(false);
            cout << "Something went wrong with connect()." << endl;
        }
        else
        {
            cout << "Connect was successful!" << endl;
            setValidity(true);
        }

        struct sockaddr tempSockAddr;
        socklen_t tempLen = sizeof(tempSockAddr);
        getsockname(getSocketDescriptor(), &tempSockAddr, &tempLen);
        //getpeername(getSocketDescriptor(), &tempSockAddr, &tempLen);
        s = inet_ntoa(((struct sockaddr_in*)&tempSockAddr)->sin_addr);
        cout << "connectSecureSocket: The getsockname IP address is " << charArray_to_string(s, strlen(s)) << endl;
        cout << "connectSecureSocket: The getsockname port number is " << ntohs(((struct sockaddr_in*)&tempSockAddr)->sin_port) << endl;
        getpeername(getSocketDescriptor(), &tempSockAddr, &tempLen);
        s = inet_ntoa(((struct sockaddr_in*)&tempSockAddr)->sin_addr);
        cout << "connectSecureSocket: The getpeername IP address is " << charArray_to_string(s, strlen(s)) << endl;
        cout << "connectSecureSocket: The getpeername port number is " << ntohs(((struct sockaddr_in*)&tempSockAddr)->sin_port) << endl;

    }
    return result;
}

int SecureSocket::readSecureSocket()
{
    int len = -2;
    if(getValidity() == true)
    {
        char buffer_char[256];
        len = read(getSocketDescriptor(), buffer_char, sizeof(buffer_char));
        setBuffer(charArray_to_string(buffer_char, strlen(buffer_char)));
    }
    return len;
}

int SecureSocket::writeSecureSocket()
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
