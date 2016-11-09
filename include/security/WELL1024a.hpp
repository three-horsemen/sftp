//
// Created by Soorya Annadurai on 9/11/16.
//

#ifndef SFTP_WELL1024A_HPP
#define SFTP_WELL1024A_HPP

#define MAT0POS(t, v) (v^(v>>t))
#define MAT0NEG(t, v) (v^(v<<(-(t))))
#define Identity(v) (v)

#define V0            STATE[state_i                   ]
#define VM1           STATE[(state_i+M1) & 0x0000001fU]
#define VM2           STATE[(state_i+M2) & 0x0000001fU]
#define VM3           STATE[(state_i+M3) & 0x0000001fU]
#define VRm1          STATE[(state_i+31) & 0x0000001fU]
#define newV0         STATE[(state_i+31) & 0x0000001fU]
#define newV1         STATE[state_i                   ]

#define FACT 2.32830643653869628906e-10

class WELL1024_PRNG {
private:
	static const int W = 32;
	static const int R = 32;
	static const int M1 = 3;
	static const int M2 = 24;
	static const int M3 = 10;
	unsigned long state_i = 0;
	unsigned long init[R];
	unsigned long STATE[R];
	unsigned long z0, z1, z2;
	unsigned long seedValue;
public:
	void InitWELLRNG1024a(unsigned long newSeedValue);

	double generateRandomNumber();
};

#endif //SFTP_WELL1024A_HPP
