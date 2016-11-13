//
// Created by Soorya Annadurai on 9/11/16.
//
#include "security/WELL1024a.hpp"

void WELL1024_PRNG::InitWELLRNG1024a(unsigned long newSeedValue) {
	seedValue = newSeedValue;
	init[0] = seedValue % 256;
	for (long i = 1; i < R; i++)
		init[i] = (init[i - 1] * init[i - 1] * init[i - 1] * seedValue) % 256;
	state_i = 0;
	for (long j = 0; j < R; j++)
		STATE[j] = init[j];
}

double WELL1024_PRNG::generateRandomNumber() {
	z0 = VRm1;
	z1 = Identity(V0) ^ MAT0POS (8, VM1);
	z2 = MAT0NEG (-19, VM2) ^ MAT0NEG(-14, VM3);
	newV1 = z1 ^ z2;
	newV0 = MAT0NEG (-11, z0) ^ MAT0NEG(-7, z1) ^ MAT0NEG(-13, z2);
	state_i = (state_i + 31) & 0x0000001fU;
	long randomNumber = ((long) ((double) STATE[state_i] * FACT * 1024)) % 256;
	return randomNumber;
}