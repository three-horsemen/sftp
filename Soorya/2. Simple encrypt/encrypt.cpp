#include <iostream>
#include <bitset>

using namespace std;

string encrypt(string message, char key)
{
	cout << endl << "Beginning encryption." << endl;
	for(int i = 0; i < message.length(); i++)
	{
		cout << bitset<8>(message[i]) << " ^ " << bitset<8>(key) << " = ";
		message[i] = message[i] ^ key;
		cout << bitset<8>(message[i]) << endl;
	}
	cout << endl;
	return message;
}

int main()
{
	string message = "Hi there!";
	char key = 'a';
	string encrypted = encrypt(message, key);
	cout << "The encrypted form of \"" << message << "\" with the key as '" << key << "' is:" << endl;
	for(int i = 0; i < encrypted.length(); i++)
	{
		cout << (int)encrypted[i] << " ";
	}

	cout << "The decrypted message is \"" << encrypt(encrypted, key) << "\"" << endl;
	cout << endl;
	return 0;
}
