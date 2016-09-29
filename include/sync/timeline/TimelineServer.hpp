#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define queueSize 16

int main(int argc, char** argv){

     int listenSocketDescriptor, s, portno;
     socklen_t clientAddrLen;
     char buffer[256];

     struct sockaddr_in servAddr, clientAddr;
     int n;
     if (argc < 2) {
         printf("Invalid arguments\n");
         exit(1);
     }

	listenSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	if(listenSocketDescriptor<0) {
		printf("Error: Socket failed!\n");
		return 1;
	}else{
		printf("Successfully created socket: %d\n",listenSocketDescriptor);
	}

	memset(&servAddr,0,sizeof(servAddr));
    portno = atoi(argv[1]);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portno);

	if(bind(listenSocketDescriptor,(struct sockaddr*)&servAddr,sizeof(servAddr))<0){
		printf("Error: Bind failed!\n");
		return 1;
	}else{
		printf("Successfully performed bind on socket\n");
	}

	if(listen(listenSocketDescriptor,queueSize)<0){
		printf("Error: Listen failed!\n");
		return 1;
	}else{
		printf("Successfully listening to socket\n");
	}
     clientAddrLen = sizeof(clientAddr);

	while(1){
		printf("Waiting for connection\n");

		s = accept(listenSocketDescriptor,(struct sockaddr *) &clientAddr,&clientAddrLen);
		if(s<0){
			printf("Error: Connection was not accepted: %d!\n",s);
			return 1;
		}else{
			printf("Successfully accepted socket\n");
		}

		bzero(buffer,256);
		n = read(s,buffer,255);
     	if (n < 0) printf("ERROR reading from socket");

		printf("Read %d bytes: %s\n",n,buffer);
		n = write(s,buffer,n);
		printf("Wrote %d bytes\n",n);
		close(s);
	}

     close(listenSocketDescriptor);
     return 0;
}
