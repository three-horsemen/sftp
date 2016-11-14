//
// Created by Soorya Annadurai on 14/11/16.
//

#ifndef SFTP_SECUREFILETRANSFER_HPP
#define SFTP_SECUREFILETRANSFER_HPP

#include "security/securesocket.hpp"
#include <iostream>

int sendFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string sourceFilePath);

int
sendEncryptedFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string sourceFilePath, int symmetricKey);

int receiveFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string targetFilePath);

int receiveDecryptedFileOverSecureDataSocket(SecureDataSocket &secureDataSocket, std::string targetFilePath,
											 int symmetricKey);

#endif //SFTP_SECUREFILETRANSFER_HPP
