/*
 * Notification.cpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#include <database/Notification.hpp>

namespace sftp {

namespace db {

Notification::Notification(long _id, string message, long sentAt) :
		_id(_id), message(message), sentAt(sentAt) {
}

Notification::~Notification() {
	// TODO Auto-generated destructor stub
}

long Notification::getId() {
	return _id;
}

string Notification::getMessage() {
	return message;
}

long Notification::getSentAt() {
	return sentAt;
}

} /* namespace db */

} /* namespace sftp */
