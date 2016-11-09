#include "security/encrypt.hpp"

std::string encrypt(std::string message, char key) {
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ key;
	return message;
}

std::string decrypt(std::string message, char key) {
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ key;
	return message;
}
