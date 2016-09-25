#include "security/encrypt.hpp"

int main()
{
	string message = "Hi there!";
	char key = 'a';
	EncryptModule testEncryptModule;
	string encrypted = testEncryptModule.encrypt(message, key);
	cout << "The encrypted form of \"" << message << "\" with the key as '" << key << "' is:" << endl;
	for(int i = 0; i < encrypted.length(); i++)
	{
		cout << (int)encrypted[i] << " ";
	}

	cout << "The decrypted message is \"" << testEncryptModule.encrypt(encrypted, key) << "\"" << endl;
	cout << endl;
	return 0;
}
