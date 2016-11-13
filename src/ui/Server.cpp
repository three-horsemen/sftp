//Server program to keep talking to clients until a "quit" message is sent.
//Multithreading functionality is enabled, but not limited.
//The communications are secured over a Diffie-Hellman key exchange.
#include "security/securesocket.hpp"
#include "ui/CommandInterpreter.hpp"
#include <boost/thread.hpp>
#define ON_SERVER true
using namespace std;

#define JAIL_PATH "/home/ayushsoni/Desktop/MyJails/"

void createJailIfDoesNotExist(std::string path) {
	if(CommandPathUtil::specifiedPathExists(CommandPathUtil::findParentToGivenPath(path)) && CommandPathUtil::specifiedPathIsDirectory(CommandPathUtil::findParentToGivenPath(path))) {
		boost::filesystem::path dir(path.c_str());
		boost::filesystem::create_directory(dir);
	}
}

void serverThread(SecureDataSocket &acceptedSecureDataSocket)
{
	try
	{
		LOG_INFO << "Negotiating with new client.";
		if (acceptedSecureDataSocket.getValidity())
		{
			LOG_INFO << "Diffie-Hellman key exchange with client " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " successful!";

			UserSessionDetail user;

			std::string rawCommand;
      std::string username = acceptedSecureDataSocket.receiveAndDecrypt();
			LOG_INFO << "\nRECEIVED USERNAME: " << username;
      user.setUsername(username);
      user.setPresentWorkingDirectory(JAIL_PATH + username);

			createJailIfDoesNotExist(user.getPresentWorkingDirectory());

			do
			{

			  //cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " <--$ ";
        //cout << message << endl;
        //cout << " $$$Mesg length: " << message.length() << " &&&Mesg size: " << message.size() << endl;

				rawCommand = acceptedSecureDataSocket.receiveAndDecrypt();
        Command command = CommandInterpreter::interpretCommandType(rawCommand, user, ON_SERVER);
				acceptedSecureDataSocket.encryptAndSend(command.getCommandOutput());

				//cout << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << " -->$ ";
				//cout << acceptedSecureDataSocket.getBuffer() << endl;

			} while (rawCommand != "quit" &&
					 acceptedSecureDataSocket.getValidity());
		}
	}
	catch(SecureSocketException &e)
	{
		cout << e.what() << endl;
	}
	cout << "Closing the connection from " << acceptedSecureDataSocket.getTargetAddrFromSockDesc() << ":" << acceptedSecureDataSocket.getTargetPortFromSockDesc() << endl;
	acceptedSecureDataSocket.destroySecureSocket();
}

int main()
{
	SecureListenSocket serverSecureListenSocket("127.0.0.1", "5576");
	if (!serverSecureListenSocket.getValidity())
	{
		cout << "Something went wrong!" << endl;
		return -1;
	}
	boost::thread_group threads;
	do
	{
		if(threads.size() >= 2)
			break;
		cout << "Waiting to accept a connection..." << endl;
		threads.add_thread(new boost::thread{serverThread, serverSecureListenSocket.acceptSecureSocket()});
	} while(true);
	serverSecureListenSocket.destroySecureSocket();
	cout << "Not accepting any more connections." << endl;
	LOG_INFO << "Waiting for all threads to join.";
	threads.join_all();
	cout << "Server program ending." << endl;
	return 0;
}
