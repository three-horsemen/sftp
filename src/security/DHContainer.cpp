//
// Created by Soorya Annadurai on 9/11/16.
//
#include "security/DHContainer.hpp"

const long DHKeyContainer::goodPrimePThreshold = 20;
const long DHKeyContainer::goodPrimeQThreshold = 20;
const std::string DHKeyContainer::goodLocalPrivateThreshold = "10";
const std::string DHKeyContainer::goodLocalPublicThreshold = "10";
const std::string DHKeyContainer::goodRemotePublicThreshold = "10";
const std::string DHKeyContainer::goodSharedSecretThreshold = "10";

DHKeyContainer::DHKeyContainer() {
	setValidity(false);
	sharedSecret = "00000000";
}

void DHKeyContainer::setValidity(bool newValidity) {
	valid = newValidity;
}

bool DHKeyContainer::getValidity() {
	return valid;
}

long DHKeyContainer::getPrimeP() {
	return primeP;
}

void DHKeyContainer::setPrimeP(long p) {
	primeP = p;
}

long DHKeyContainer::getPrimeQ() {
	return primeQ;
}

void DHKeyContainer::setPrimeQ(long q) {
	primeQ = q;
}

std::string DHKeyContainer::getLocalPrivate() {
	return localPrivate;
}

void DHKeyContainer::setLocalPrivate(std::string newLocalPrivate) {
	localPrivate = newLocalPrivate;
}

std::string DHKeyContainer::getLocalPublic() {
	return localPublic;
}

void DHKeyContainer::setLocalPublic(std::string newLocalPublic) {
	localPublic = newLocalPublic;
}

std::string DHKeyContainer::getRemotePublic() {
	return remotePublic;
}

void DHKeyContainer::setRemotePublic(std::string newRemotePublic) {
	remotePublic = newRemotePublic;
}

std::string DHKeyContainer::getSharedSecret() {
	return sharedSecret;
}

void DHKeyContainer::setSharedSecret(std::string newSharedSecret) {
	sharedSecret = newSharedSecret;
}

bool DHKeyContainer::isGoodPrimeP() {
	return getPrimeP() >= goodPrimePThreshold;
}

bool DHKeyContainer::isGoodPrimeQ() {
	return getPrimeQ() >= goodPrimeQThreshold;
}

bool DHKeyContainer::isGoodLocalPrivate() {
	return string_to_long(getLocalPrivate()) >= string_to_long(goodLocalPrivateThreshold);
}

bool DHKeyContainer::isGoodLocalPublic() {
	return string_to_long(getLocalPublic()) >= string_to_long(goodLocalPublicThreshold);
}

bool DHKeyContainer::isGoodRemotePublic() {
	return string_to_long(getRemotePublic()) >= string_to_long(goodRemotePublicThreshold);
}

bool DHKeyContainer::isGoodSharedSecret() {
	return string_to_long(getSharedSecret()) >= string_to_long(goodSharedSecretThreshold);
}
