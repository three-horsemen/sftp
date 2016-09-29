#include "security/cryptmath.hpp"
struct Extended_Euclidean_Algorithm_container
{
    int var1;
    int var2;
};

Extended_Euclidean_Algorithm_container eea(int a, int b);
int find_inverse(int x, int y);

class RSA_key_container
{
private:
    bool valid;
    int private_key;
    int public_key;
    int prime_p;
    int prime_q;
    int modulus;
public:
    RSA_key_container();
    RSA_key_container(int p, int q);
    bool get_validity();
    void set_validity(bool validity);
    int get_private_key();
    void set_private_key(int new_private_key);
    int get_public_key();
    void set_public_key(int new_public_key);
    int get_modulus();
    void set_modulus(int new_modulus);
    int encrypt_RSA(int plaintext);
    int decrypt_RSA(int ciphertext);
};
