//
// Created by Soorya Annadurai on 9/11/16.
//
#include <security/WELL1024a.hpp>
#include <iostream>

int main() {
	unsigned int seedValue = 42;
	WELL1024_PRNG wellObject;
	wellObject.InitWELLRNG1024a(seedValue);
	for (int i = 0; i < 1; i++)
		std::cout << wellObject.generateRandomNumber() << std::endl;
	return 0;
}