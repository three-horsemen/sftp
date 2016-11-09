#include "security/encrypt.hpp"
#include <iostream>

using namespace std;
std::string encrypt(std::string message, char key) {
	cout << "Encrypting " << message << " using key: " << (int) key << endl;
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ key;
	return message;
}

std::string decrypt(std::string message, char key) {
	cout << "Decrypting " << message << "using key: " << (int) key << endl;
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ key;
	return message;
}

std::string encrypt_WELL1024(std::string message, WELL1024_PRNG &generator) {
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ (char) generator.generateRandomNumber();
	return message;
}

std::string decrypt_WELL1024(std::string message, WELL1024_PRNG &generator) {
	for (int i = 0; i < message.length(); i++)
		message[i] = message[i] ^ (char) generator.generateRandomNumber();
	return message;
}