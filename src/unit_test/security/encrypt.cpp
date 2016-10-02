#include <iostream>
#include "security/encrypt.hpp"

using namespace std;
int main()
{
	string message = "Hi there!";
	char key = 'a';
	string encrypted = encrypt(message, (int)key);
	cout << "The encrypted form of \"" << message << "\" with the key as '" << key << "' is:" << endl;
	for(int i = 0; i < encrypted.length(); i++)
		cout << (int)encrypted[i] << " ";
	cout << endl << "The decrypted message is \"" << encrypt(encrypted, (int)key) << "\"" << endl;
	return 0;
}
