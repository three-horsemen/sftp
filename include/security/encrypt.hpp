#include <iostream>
#include <bitset>
using namespace std;

class EncryptModule
{
public:
	string encrypt(string message, char key)
	{
		//cout << endl << "Beginning encryption." << endl;
		for(int i = 0; i < message.length(); i++)
		{
			//cout << bitset<8>(message[i]) << " ^ " << bitset<8>(key) << " = ";
			message[i] = message[i] ^ key;
			//cout << bitset<8>(message[i]) << endl;
		}
		//cout << endl;
		return message;
	}
};
