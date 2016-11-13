//
// Created by reubenjohn on 13/11/16.
//

#include "ui/UIException.hpp"

UIException::UIException(int newErrorCode) :
		errorCode(newErrorCode) {
	message = "UI Exception";
}

UIException::UIException(int newErrorCode,
						 std::string newMessage) :
		errorCode(newErrorCode) {
	message = newMessage;
}
