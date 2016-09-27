#include "security/securesocket.hpp"

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

void SecureSocket::setBuffer(string newBuffer)
{
    buffer = newBuffer;
}

string SecureSocket::getBuffer()
{
    return buffer;
}

int SecureSocket::initSecureSocket()
{
    setSocketDescriptor(socket(PF_INET,SOCK_STREAM,0));
    if(getSocketDescriptor() < 0)
    {
        setValidity(false);
    }
    else
    {
        setValidity(true);
    }
    int force_reuse_socket_port__yes = 1;
    if (setsockopt(getSocketDescriptor(), SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes, sizeof(force_reuse_socket_port__yes)) == -1)
    {
        setValidity(false);
    }
    else
    {
        setValidity(true);
    }
    return getSocketDescriptor();
}

void SecureSocket::connectSecureSocket()
{
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
        if(connect(getSocketDescriptor(),(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
        {
            setValidity(false);
        }
        else
        {
            setValidity(true);
        }
    }
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
