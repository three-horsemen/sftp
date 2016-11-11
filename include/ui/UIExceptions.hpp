#include "security/cryptstr.hpp"

#define INVALID_COMMAND 01
#define PATH_DOES_NOT_EXIST 02
#define ACCESS_DENIED 03
#define NOT_A_DIRECTORY 04

class UIException : public std::exception {
private:
	std::string message;
public:
	const int errorCode;

	UIException(int newErrorCode);

	UIException(int newErrorCode, std::string newMessage);

	virtual const char *what() const throw() {
		return string_to_charArray(
				"UIException. " + message + " || Error code: "
				+ std::to_string(errorCode) + "\n");
	}
};
