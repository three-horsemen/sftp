//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"
#include "security/securefiletransfer.hpp"
#include <boost/thread.hpp>

#include <database/DbManager.hpp>
#include <ui/command/ListDirectoryContentsCommand.hpp>

#define retryLimit 10
#define JAILS "/home/reubenjohn/workspace/c_cpp/sftp/build/Debug/jails/"

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
					//TODO Add logic to respond to commands here
					std::string receivedTask = socket.receiveAndDecrypt();
					socket.encryptAndSend(receivedTask);
					cout << "Task received." << endl;
					if (receivedTask == "MODE_SENDTOSERVER") {
						cout << "Entered send mode." << endl;
						std::string targetDirectory = socket.receiveAndDecrypt();
						socket.encryptAndSend(targetDirectory);
						cout << "About to receive the file." << endl;
						receiveFileOverSecureDataSocket(socket, targetDirectory);
					} else if (ListDirectoryContentsCommand::isMatched(receivedTask)) {
						receivedTask = socket.receiveAndDecrypt();
						int startPositionOfUsefulPath = receivedTask.find("://");
						int startPositionOfUsername = receivedTask.find(" ");
						string jail = string(JAILS);
						std::string calculatedPath = string("ls ") + receivedTask.substr(startPositionOfUsername + 1,
																						 startPositionOfUsefulPath -
																						 (startPositionOfUsername +
																						  1)) + string("/") +
													 receivedTask.substr(startPositionOfUsefulPath + 3);
						ListDirectoryContentsCommand command(calculatedPath, jail);
						command.execute();
						socket.encryptAndSend(command.getOutput());
					} else if (MakeDirectoryCommand::isMatched(receivedTask)) {
						receivedTask = socket.receiveAndDecrypt();
						int startPositionOfUsefulPath = receivedTask.find("://");
						int startPositionOfUsername = receivedTask.find(" ");
						string jail = string(JAILS);
						std::string calculatedPath = string("mkdir ") + receivedTask.substr(startPositionOfUsername + 1,
																							startPositionOfUsefulPath -
																							(startPositionOfUsername +
																							 1)) + string("/") +
													 receivedTask.substr(startPositionOfUsefulPath + 3);
						MakeDirectoryCommand command(calculatedPath, jail);
						command.execute();
						socket.encryptAndSend(command.getOutput());
					} else if (RemoveCommand::isMatched(receivedTask)) {
						receivedTask = socket.receiveAndDecrypt();
						int startPositionOfUsefulPath = receivedTask.find("://");
						int startPositionOfUsername = receivedTask.find(" ");
						string jail = string(JAILS);
						std::string calculatedPath = string("rm ") + receivedTask.substr(startPositionOfUsername + 1,
																						 startPositionOfUsefulPath -
																						 (startPositionOfUsername +
																						  1)) + string("/") +
													 receivedTask.substr(startPositionOfUsefulPath + 3);
						RemoveCommand command(calculatedPath, jail);
						command.execute();
						socket.encryptAndSend(command.getOutput());
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
	sftp::DbManager::initializeStaticDbManager("SecureFTP.db");
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

/*
#include "security/securesocket.hpp"
#include "ui/CommandInterpreter.hpp"
#include <boost/thread.hpp>

#define ON_SERVER true
using namespace std;

#define JAIL_PATH "./jails/"

void createJailIfDoesNotExist(std::string path) {
	if (CommandPathUtil::specifiedPathExists(CommandPathUtil::findParentToGivenPath(path)) &&
		CommandPathUtil::specifiedPathIsDirectory(CommandPathUtil::findParentToGivenPath(path))) {
		boost::filesystem::path dir(path.c_str());
		boost::filesystem::create_directory(dir);
		//boost::filesystem::permissions(path, boost::filesystem::others_read | boost::filesystem::owner_read);
	}
}

void serverThread(SecureDataSocket &acceptedSecureDataSocket) {
	try {
		LOG_INFO << "Negotiating with new client.";
		if (acceptedSecureDataSocket.getValidity()) {
			LOG_INFO << "Diffie-Hellman key exchange with client "
					 << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
					 << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " successful!";

			UserSessionDetail user;

			std::string rawCommand;
			std::string username = acceptedSecureDataSocket.receiveAndDecrypt();
			LOG_INFO << "\nRECEIVED USERNAME: " << username;
			user.setUsername(username);
			user.setPresentWorkingDirectory(JAIL_PATH + username);

			createJailIfDoesNotExist(user.getPresentWorkingDirectory());

			do {

				//cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " <--$ ";
				//cout << message << endl;
				//cout << " $$$Mesg length: " << message.length() << " &&&Mesg size: " << message.size() << endl;

				rawCommand = acceptedSecureDataSocket.receiveAndDecrypt();
				Command command = CommandInterpreter::getInterpretedCommand(rawCommand, user, ON_SERVER);
				acceptedSecureDataSocket.encryptAndSend(command.getParts());

				//cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " -->$ ";
				//cout << acceptedSecureDataSocket.getBuffer() << endl;

			} while (rawCommand != "quit" &&
					 acceptedSecureDataSocket.getValidity());
		}
	}
	catch (SecureSocketException &e) {
		cout << e.what() << endl;
	}
	cout << "Closing the connection from " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":"
		 << acceptedSecureDataSocket.getTargetPortFromSockDesc() << endl;
	acceptedSecureDataSocket.destroySecureSocket();
}

int main() {
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "5576");
	if (!serverSecureListenSocket.getValidity()) {
		cout << "Something went wrong!" << endl;
		return -1;
	}
	boost::thread_group threads;
	do {
		if (threads.size() >= 2)
			break;
		cout << "Waiting to accept a connection..." << endl;
		threads.add_thread(new boost::thread{serverThread, serverSecureListenSocket.acceptSecureSocket()});
	} while (true);
	serverSecureListenSocket.destroySecureSocket();
	cout << "Not accepting any more connections." << endl;
	LOG_INFO << "Waiting for all threads to join.";
	threads.join_all();
	cout << "Server program ending." << endl;
	return 0;
}
*/