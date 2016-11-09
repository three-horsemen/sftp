//
// Created by Soorya Annadurai on 9/11/16.
//

#ifndef SFTP_DHCONTAINER_HPP
#define SFTP_DHCONTAINER_HPP

#include "security/cryptmath.hpp"
#include "security/cryptstr.hpp"

class DHKeyContainer {
private:
	static const long goodPrimePThreshold;
	static const long goodPrimeQThreshold;
	static const std::string goodLocalPrivateThreshold;
	static const std::string goodLocalPublicThreshold;
	static const std::string goodRemotePublicThreshold;
	static const std::string goodSharedSecretThreshold;

	bool valid;
	long primeP;
	long primeQ;
	std::string localPrivate;
	std::string localPublic;
	std::string remotePublic;
	std::string sharedSecret;
public:
	DHKeyContainer();

	bool isGoodPrimeP();

	bool isGoodPrimeQ();

	bool isGoodLocalPrivate();

	bool isGoodLocalPublic();

	bool isGoodRemotePublic();

	bool isGoodSharedSecret();

	void setValidity(bool newValidity);

	bool getValidity();

	long getPrimeP();

	void setPrimeP(long p);

	long getPrimeQ();

	void setPrimeQ(long q);

	std::string getLocalPrivate();

	void setLocalPrivate(std::string newLocalPrivate);

	std::string getLocalPublic();

	void setLocalPublic(std::string newLocalPublic);

	std::string getRemotePublic();

	void setRemotePublic(std::string newRemotePublic);

	std::string getSharedSecret();

	void setSharedSecret(std::string newSharedSecret);
};

#endif //SFTP_DHCONTAINER_HPP
