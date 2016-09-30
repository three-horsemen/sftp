/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8889 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

	int len = 0;

    //keep communicating with server
    while(1)
    {
		bzero(message, 1000);
        printf("Enter message : ");
        scanf("%s" , message);

        //Send some data
        if(len = send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
		bzero(server_reply, 2000);
        if(len = recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
		//server_reply[len] = '\0';
        puts("Server reply :");
        puts(server_reply);
		//printf("%s\n", server_reply);
    }

    close(sock);
    return 0;
}



/*
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <netinet/in.h>

char* getSourceAddrfromSockDesc(int sock)
{
	struct sockaddr clientAddr;
	socklen_t clilen = sizeof(clientAddr);
	getsockname(sock,&clientAddr,&clilen);
	return inet_ntoa(((struct sockaddr_in*)&clientAddr)->sin_addr);
}
char* getDestAddrfromSockDesc(int sock)
{
	struct sockaddr clientAddr;
	socklen_t clilen = sizeof(clientAddr);
	getpeername(sock,&clientAddr,&clilen);
	return inet_ntoa(((struct sockaddr_in*)&clientAddr)->sin_addr);
}


void main()
{
	int sfd,i = 0;
	struct sockaddr_in saddr;
	char buffer[1024];
	sfd = socket(AF_INET,SOCK_STREAM,0);
	// printf("getSourceAddrfromSockDesc :: %s\n",getSourceAddrfromSockDesc(sfd));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(12344);
	connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
	while(buffer!="quit")
	{
		// connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
		// printf("getSourceAddrfromSockDesc :: %s\n",getSourceAddrfromSockDesc(sfd));
		// printf("getDestAddrfromSockDesc :: %s\n",getDestAddrfromSockDesc(sfd));
		printf("Enter message:: ");
		scanf("%s",buffer);
		printf("Writing\n");
		// send(sfd,buffer,strlen(buffer),0);
		write(sfd,buffer,strlen(buffer));
		printf("Reading\n");
		// recv(sfd,buffer,1024,0);
		read(sfd,buffer,1024);
		printf("Received :: %s\n",buffer);
		bzero(buffer, 1024);
	}
	close(sfd);
}
*/
