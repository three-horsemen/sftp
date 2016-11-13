//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"

#include <boost/thread.hpp>

#include <database/DbManager.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define retryLimit 10

namespace sftp {

	using namespace std;
	using namespace db;

	const boost::thread::attributes timelineServerThread(SecureDataSocket &socket) {
		LOG_INFO << "Negotiating with new client " << socket.getSocketDescriptor();
		try {
			if (!socket.getValidity()) {
				throw runtime_error("Socket is invalid");
			}

			string username, password;
			try {
				LOG_DEBUG << socket.getSocketDescriptor() << ": Prompting username";
				socket.encryptAndSend(UserManager::USERNAME);
				username = socket.receiveAndDecrypt();
			} catch (SecureSocketException &e) {
				throw SecureSocketException(e.errorCode, string("Could not receive username(") + e.what() + ")");
			}
			try {
				LOG_DEBUG << socket.getSocketDescriptor() << ": Prompting password";
				socket.encryptAndSend(UserManager::PASSWORD);
				password = socket.receiveAndDecrypt();
			} catch (SecureSocketException &e) {
				throw SecureSocketException(e.errorCode, string("Could not receive password(") + e.what() + ")");
			}

			UserManager userManager = DbManager::getDb()->getUserManager();
			bool isAuthentic = userManager.isAuthenticationValid(username, password);
			if (isAuthentic) {
				socket.encryptAndSend(UserManager::CREDENTIALS_VALID);
				LOG_INFO << socket.getSocketDescriptor() << ": Login sucess";
			} else {
				socket.encryptAndSend(UserManager::CREDENTIALS_INVALID);
				LOG_WARNING << socket.getSocketDescriptor() << ": Invalid credentials";
			}

			long uid = userManager.getUserId(username);
			TimelineManager timelineManager = DbManager::getDb()->getTimelineManager();
			do {
				try {
					unsigned retryCount;
					for (retryCount = 0; retryCount < retryLimit; retryCount++) {
						vector<Notification> notifications = timelineManager.getPendingNotifications(uid);
						if (notifications.size()) {
							for (unsigned int i = 0; i < notifications.size();) {
								//string notification =	Utils::getFormattedEpochTime(notifications[i].getSentAt())
								// + ": " + notifications[i].getMessage();

								string encodedNotification = TimelineManager::getEncodedNotification(notifications[i]);
								socket.encryptAndSend(encodedNotification);

								string echo = socket.receiveAndDecrypt();
								if (encodedNotification == echo) {
									struct timeval tp;
									gettimeofday(&tp, NULL);
									long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
									timelineManager.markAsNotified(notifications[i].getId(), ms);
									i++;
								} else {
									LOG_WARNING << "Received mismatching echo";
								}
							}
							break;
						} else {
							boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
							continue;
						}
					}
					/*TODO Enable this section once encryptAndSend is capable of throwing exception
					 * as opposed to crashing the process when the client is down
					 */
					if (false && retryCount >= retryLimit) {
						//TODO Have a more robust check for whether the connection is alive
						try {
							socket.encryptAndSend(TimelineManager::IS_ALIVE_PROBE);
							string echo = socket.receiveAndDecrypt();
							if (string(TimelineManager::IS_ALIVE_PROBE) != echo) {
								LOG_WARNING << "Closing connection to client: Received mismatching probe echo";
								socket.destroySecureSocket();
							}
						} catch (SecureSocketException &e) {
							LOG_ERROR << "Closing connection to client: " << e.what();
							if (e.errorCode == DATA_SOCK_WRITE_EMPTY_EXC) {
								socket.destroySecureSocket();
							} else {
								throw e;
							}
						}
						continue;
					}
				} catch (SecureSocketException &e) {
					LOG_ERROR << "Could not received next command: " << e.what();
				}
			} while (socket.getValidity());
		} catch (SQLiteException &e) {
			LOG_ERROR << e.what();
			socket.encryptAndSend(TimelineManager::SERVER_ERROR);
		} catch (SecureSocketException &e) {
			LOG_ERROR << e.what();
		} catch (exception &e) {
			LOG_ERROR << e.what();
		}
		try {
			socket.destroySecureSocket();
		} catch (SecureSocketException &e) {
			LOG_ERROR << "Failed to close socket: " << e.what();
		}
	}

}

int main() {
	sftp::DbManager::initializeStaticDbManager("sftp.db");
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "8081");
	if (!serverSecureListenSocket.getValidity()) {
		LOG_ERROR << "Something went wrong!" << endl;
		return -1;
	}
	boost::thread_group threads;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	while (true) {
		LOG_DEBUG << "Waiting to accept a connection...\n";
		// boost::thread t {sftp::timelineServerThread,
		// 	serverSecureListenSocket.acceptSecureSocket()};
#pragma clang diagnostic push
#pragma ide diagnostic ignored "IncompatibleTypes"
		threads.add_thread(new boost::thread{
				sftp::timelineServerThread,
				serverSecureListenSocket.acceptSecureSocket()});
#pragma clang diagnostic pop
	}
#pragma clang diagnostic pop
	/*
	serverSecureListenSocket.destroySecureSocket();
	LOG_DEBUG<<"Not accepting any more connections.";
	LOG_INFO<<"Waiting for all threads to join.";
	threads.join_all();
	LOG_DEBUG<<"Timeline server shutting down.";
	return 0;
	 */
}
