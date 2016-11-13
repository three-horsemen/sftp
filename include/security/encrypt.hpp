#include <bitset>
#include "security/WELL1024a.hpp"

std::string encrypt(std::string message, char key);

std::string decrypt(std::string message, char key);

std::string encrypt_WELL1024(std::string message, WELL1024_PRNG &generator);

std::string decrypt_WELL1024(std::string message, WELL1024_PRNG &generator);