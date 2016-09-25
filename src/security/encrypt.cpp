#include <bitset>
#include "security/encrypt.hpp"
std::string EncryptModule::encrypt(std::string message, char key)
{
	for(int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ key;
	return message;
}
