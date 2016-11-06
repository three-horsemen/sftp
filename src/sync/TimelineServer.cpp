//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"

#include <boost/thread.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>

#include <iostream>

#include <shared/logger.hpp>

#include <database/DbManager.hpp>
#include <database/UserManager.hpp>
#include <database/TimelineManager.hpp>

namespace sftp {

using namespace std;
using namespace db;

void timelineServerThread(SecureDataSocket socket) {
	LOG_INFO<<"Negotiating with new client "<<socket.getSocketDescriptor();
	try {
		if (!socket.getValidity()) {
			throw runtime_error("Socket is invalid");
		}

		string username,password;
		try {
			LOG_DEBUG<< socket.getSocketDescriptor()<<": Prompting username";
			socket.encryptAndSend(UserManager::USERNAME);
			username = socket.receiveAndDecrypt();
		} catch(SecureSocketException &e) {
			throw SecureSocketException(e.errorCode,string("Could not receive username(")+e.what()+")");
		}
		try {
			LOG_DEBUG<< socket.getSocketDescriptor()<<": Prompting password";
			socket.encryptAndSend("PASSWORD");
			password = socket.receiveAndDecrypt();
		} catch(SecureSocketException &e) {
			throw SecureSocketException(e.errorCode,string("Could not receive password(")+e.what()+")");
		}

		bool isAuthentic =
		DbManager::getDb()->getUserManager().isAuthenticationValid(
				username, password);
		if (isAuthentic) {
			socket.encryptAndSend("VALID");
			LOG_INFO<< socket.getSocketDescriptor()<<": Login sucess";
		} else {
			socket.encryptAndSend("INVALID");
			LOG_WARNING<< socket.getSocketDescriptor()<<": Invalid credentials";
		}

		do {
			try {
				vector<Notification> notifications = DbManager::getDb()->getTimelineManager().getPendingNotifications(1);

				for(unsigned int i=0;i<notifications.size();) {
					std::time_t tt = static_cast<time_t>(notifications[i].getSentAt()/1000);
					boost::posix_time::ptime sentAt = boost::posix_time::from_time_t(tt);
					string notification = boost::posix_time::to_iso_string(sentAt) + ": "+notifications[i].getMessage();
					socket.encryptAndSend(notification);

					string echo = socket.receiveAndDecrypt();
					if(notification == echo) {
						struct timeval tp;
						gettimeofday(&tp, NULL);
						long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
						DbManager::getDb()->getTimelineManager().markAsNotified(notifications[i].getId(),ms);
						i++;
					}
				}
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			} catch(SecureSocketException &e) {
				LOG_ERROR<<"Could not received next command: "<<e.what();
			}
		}while (socket.getValidity() == true);

		//TODO Handle reception of commands once secure socket timeouts are implemented:
		do {
			try {
				string command = socket.receiveAndDecrypt();
				LOG_DEBUG<<"Received command: "<<command;
				if (UserManager::isLogoutCommand(command)) {
					LOG_INFO<< socket.getSocketDescriptor()<<": Client logged out";
					break;
				}
			} catch(SecureSocketException &e) {
				LOG_ERROR<<"Could not received next command: "<<e.what();
			}
		}while (socket.getValidity() == true);
	} catch (SQLiteException &e) {
		LOG_ERROR<<e.what();
		socket.encryptAndSend(TimelineManager::SERVER_ERROR);
	} catch(SecureSocketException &e) {
		LOG_ERROR<<e.what();
	} catch(exception &e) {
		LOG_ERROR<<e.what();
	}
	try {
		socket.destroySecureSocket();
	} catch(SecureSocketException &e) {
		LOG_ERROR<<"Failed to close socket: "<<e.what();
	}
}

}

int main() {
	sftp::DbManager::initializeStaticDbManager("sftp.db");
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "8081");
	if (serverSecureListenSocket.getValidity() == false) {
		LOG_ERROR<< "Something went wrong!" << endl;
		return -1;
	}
	while (true) {
		LOG_DEBUG<< "Waiting to accept a connection..." << endl;
		boost::thread t {sftp::timelineServerThread,
			serverSecureListenSocket.acceptSecureSocket()};
	}
	LOG_DEBUG<<"Timeline server shutting down";
	return 0;
}
