#include "security/rsa.hpp"
#include <iostream>
using namespace std;

int main()
{
    RSA_key_container rsa_key_container(97, 83);
    if(!rsa_key_container.get_validity())
        cout << "The RSA key container is invalid." << endl;
    else
    {
        cout << "modulus: " << rsa_key_container.get_modulus() << endl;
        cout << "public key: " << rsa_key_container.get_public_key() << endl;
        cout << "private key: " << rsa_key_container.get_private_key() << endl;
        cout << endl;
        int data = 1234;
        cout << "Original: " << data << endl;
        int encrypted_RSA = rsa_key_container.encrypt_RSA(data);
        cout << "Encrypted: " << encrypted_RSA << endl;
        int decrypted_RSA = rsa_key_container.decrypt_RSA(encrypted_RSA);
        cout << "Decrypted: " << decrypted_RSA << endl;
    }
}
