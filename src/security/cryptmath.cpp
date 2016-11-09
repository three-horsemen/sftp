#include "security/cryptmath.hpp"

long custom_rand(long lim = 100) {
	clock_t t = clock();
	static long a = 1; // could be made the seed value
	a = (a * t * 32719 + 3) % 32749;
	return ((a % lim) + 1);
}

long crtModulus(long base, long exponent, long modulus) {
	if ((base < 1) || (exponent < 0) || (modulus < 1)) {
		return (-1);
	}
	long result = 1;
	while (exponent > 0) {
		if ((exponent % 2) == 1) {
			result = (result * base) % modulus;
		}
		base = (base * base) % modulus;
		exponent = exponent / 2;
	}
	return (result);
}

int isPrime(long num) {
	if ((num & 1) == 0)
		return num == 2;
	else {
		long i;
		long limit = num / 2 + 1;
		for (i = 3; i <= limit; i += 2) {
			if (num % i == 0)
				return 0;
		}
	}
	return 1;
}

long nextPrime(long num) {
	long c;
	if (num < 2)
		c = 2;
	else if (num == 2)
		c = 3;
	else if (num & 1) {
		num += 2;
		c = isPrime(num) ? num : nextPrime(num);
	} else
		c = nextPrime(num - 1);
	return c;
}

long randomPrime(long upper_limit) {
	if (upper_limit <= 2)
		return 2;
	long temp = custom_rand(upper_limit);
	do {
		if (isPrime(temp))
			break;
		temp--;
	} while (temp > 2);
	return temp;
}
