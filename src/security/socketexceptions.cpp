#include "security/socketexceptions.hpp"

SecureSocketException::SecureSocketException(int newErrorCode) :
		errorCode(newErrorCode) {
	message = "";
}
SecureSocketException::SecureSocketException(int newErrorCode,
		std::string newMessage) :
		errorCode(newErrorCode) {
	message = newMessage;
}
