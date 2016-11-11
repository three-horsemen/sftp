#include "ui/UIExceptions.hpp"

UIException::UIException(int newErrorCode) :
		errorCode(newErrorCode) {
	message = "UI Exception";
}

UIException::UIException(int newErrorCode,
											 std::string newMessage) :
		errorCode(newErrorCode) {
	message = newMessage;
}
