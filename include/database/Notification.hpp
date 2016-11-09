/*
 * Notification.hpp
 *
 *  Created on: 06-Nov-2016
 *      Author: reubenjohn
 */

#ifndef INCLUDE_DATABASE_NOTIFICATION_HPP_
#define INCLUDE_DATABASE_NOTIFICATION_HPP_

#include <string>

namespace sftp {

namespace db {

using namespace std;

class Notification {
	string message;
	long _id, sentAt;
public:
	Notification(long, string, long);
	virtual ~Notification();

	long getId();
	string getMessage();
	long getSentAt();
};

} /* namespace db */

} /* namespace sftp */

#endif /* INCLUDE_DATABASE_NOTIFICATION_HPP_ */
