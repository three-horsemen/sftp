#include "security/securesocket.hpp"

int SecureSocket::getValidity()
{
    return valid;
}

void SecureSocket::setValidity(int newValidity)
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
    socketDescriptor = socket(PF_INET,SOCK_STREAM,0);
    if(socketDescriptor < 0)
    {
        valid = false;
    }
    else
    {
        valid = true;
    }
    int force_reuse_socket_port__yes = 1;
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes, sizeof(force_reuse_socket_port__yes)) == -1)
    {
        valid = false;
    }
    else
    {
        valid = true;
    }
}

int SecureSocket::connectSecureSocket()
{
    if(valid == true)
    {
        if(connect(socket_descriptor,(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
        {
            valid = false;
        }
        else
        {
            valid = true;
        }
    }
}

int SecureSocket::readSecureSocket()
{
    if(valid == true)
    {
        char buffer_char[256];
        len = read(socket_descriptor, buffer_char, sizeof(buffer_char));
    }
}
