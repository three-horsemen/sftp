//
// Created by Soorya Annadurai on 14/11/16.
//

#ifndef SFTP_SECUREFILETRANSFER_HPP
#define SFTP_SECUREFILETRANSFER_HPP

#include "security/securesocket.hpp"
#include <iostream>

int sendFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string sourceFilePath);

int receiveFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string targetFilePath);


#endif //SFTP_SECUREFILETRANSFER_HPP
