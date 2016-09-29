#include "security/rsa.hpp"
Extended_Euclidean_Algorithm_container eea(int a, int b)
{
    Extended_Euclidean_Algorithm_container eea_container;
    if (b == 0)
    {
        eea_container.var1 = 1;
        eea_container.var2 = 0;
        return eea_container;
    }
    Extended_Euclidean_Algorithm_container alpha, beta;
    alpha.var1 = a/b;
    alpha.var2 = a%b;
    beta = eea(b, alpha.var2);

    eea_container.var1 = beta.var2;
    eea_container.var2 = beta.var1-(alpha.var1*beta.var2);
    return eea_container;
}

int find_inverse(int x, int y)
{
    int inv = eea(x, y).var1;
    if(inv < 1)
        inv += y;
    return inv;
}

RSA_key_container::RSA_key_container()
{
    valid = false;
}
RSA_key_container::RSA_key_container(int p, int q)
{
    int E = rand_prime((p-1)*(q-1) - 1);
    //cout << "The generated value of E is : " << E << endl;
    valid = true;
    prime_p = p;
    prime_q = q;
    modulus = p*q;
    int T = (prime_p - 1) * (prime_q - 1);
    if(!is_prime(prime_p) || !is_prime(prime_q))
    {
        //cout << "Something wrong with the primality!" << endl;
        valid = false;
    }
    else if ((E < 1) || (E > T))
    {
        //cout << "Something wrong with the RSA conditions!" << endl;
        valid = false;
    }
    else if ((T%E == 0))
    {
        //cout << "Something wrong with the other RSA conditions!" << endl;
        valid = false;
    }
    else
    {
        public_key = E;
        private_key = find_inverse(E, T);
    }
}
bool RSA_key_container::get_validity()
{
    return valid;
}
void RSA_key_container::set_validity(bool validity)
{
    valid = validity;
}
int RSA_key_container::get_private_key()
{
    return private_key;
}
void RSA_key_container::set_private_key(int new_private_key)
{
    private_key = new_private_key;
}
int RSA_key_container::get_public_key()
{
    return public_key;
}
void RSA_key_container::set_public_key(int new_public_key)
{
    public_key = new_public_key;
}
int RSA_key_container::get_modulus()
{
    return modulus;
}
void RSA_key_container::set_modulus(int new_modulus)
{
    modulus = new_modulus;
}

int RSA_key_container::encrypt_RSA(int plaintext)
{
    return mpmod(plaintext, get_public_key(), get_modulus());
}
int RSA_key_container::decrypt_RSA(int ciphertext)
{
    return mpmod(ciphertext, get_private_key(), get_modulus());
}
