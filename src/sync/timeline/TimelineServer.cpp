#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <exception>

#include <shared/SignalHandler.hpp>
#include <security/SecureSocketManager.hpp>

using namespace std;
using namespace security;

/*
 struct MyException: public exception {
 const char * what() const throw () {
 return "C++ Exception";
 }
 };

 int main() {
 try {
 throw MyException();
 } catch (MyException& e) {
 std::cout << "MyException caught" << std::endl;
 std::cout << e.what() << std::endl;
 } catch (std::exception& e) {
 //Other errors
 }
 }
 */

class TimelineServer {
private:
	int listenSocketDescriptor;
	socklen_t clientAddrLen;
	char buffer[256];

	struct sockaddr_in servAddr, clientAddr;
	SignalHandler sh;
public:
	TimelineServer(int portNo) :
			sh() {
		//sh.setupSignalHandlers();

		int portNumber = portNo;
		int n;

		listenSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
		if (listenSocketDescriptor < 0) {
			printf("Error: Socket failed!\n");
			return;
		} else {
			printf("Successfully created socket: %d\n", listenSocketDescriptor);
		}

		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_addr.s_addr = INADDR_ANY;
		servAddr.sin_port = htons(portNumber);

		if (bind(listenSocketDescriptor, (struct sockaddr*) &servAddr,
				sizeof(servAddr)) < 0) {
			printf("Error: Bind failed!\n");
			return;
		} else {
			printf("Successfully performed bind on socket\n");
		}

		if (listen(listenSocketDescriptor, 10) < 0) {
			printf("Error: Listen failed!\n");
			return;
		} else {
			printf("Successfully listening to socket\n");
		}
		clientAddrLen = sizeof(clientAddr);
	}

	void acceptNewConnection() {
		printf("Waiting for connection\n");

		int s = accept(listenSocketDescriptor, (struct sockaddr *) &clientAddr,
				&clientAddrLen);

		try {
			bool bufferEmpty = false;
			SecureSocketManager ssm(s);
			while (!sh.gotExitSignal() && !bufferEmpty) {
				try {
					bzero(buffer, 256);
					int n = ssm.readBuffer(buffer, 255);
					buffer[n] = '\0';
					printf("Read %d bytes: %s\n", n, buffer);
					try {
						ssm.writeBuffer(buffer, n);
						printf("Wrote %d bytes\n", n);
					} catch (SocketIOException e) {
						LOG_ERROR<< "Socket write failed\n";
					}
				} catch (SocketIOException e) {
					LOG_ERROR<< "Socket read failed";
				} catch(SocketBufferEmptyException e) {
					LOG_DEBUG<<"Socket buffer empty";
					bufferEmpty = true;
				}
			}
			LOG_DEBUG<<"Closing data socket: "<<s;
			close(s);
		} catch (shared::InvalidSocketException& e) {
			LOG_ERROR<< e.what() << '\n';
		} catch (std::exception& e) {
			LOG_ERROR<< e.what() << '\n';
		}
	}

	virtual ~TimelineServer() {
		close(listenSocketDescriptor);
	}
};

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Arguments: portNumber\n");
		exit(1);
	}
	int portNo = atoi(argv[1]);
	TimelineServer ts(portNo);
	ts.acceptNewConnection();
	return 0;
}
