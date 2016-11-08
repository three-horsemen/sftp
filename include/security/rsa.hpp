#include "security/cryptmath.hpp"

struct Extended_Euclidean_Algorithm_container {
	long var1;
	long var2;
};

Extended_Euclidean_Algorithm_container eea(long a, long b);

long find_inverse(long x, long y);

class RSA_key_container {
private:
	bool valid;
	long private_key;
	long public_key;
	long prime_p;
	long prime_q;
	long modulus;
public:
	RSA_key_container();

	RSA_key_container(long p, long q);

	bool get_validity();

	void set_validity(bool validity);

	long get_private_key();

	void set_private_key(long new_private_key);

	long get_public_key();

	void set_public_key(long new_public_key);

	long get_modulus();

	void set_modulus(long new_modulus);

	long encrypt_RSA(long plaintext);

	long decrypt_RSA(long ciphertext);
};
