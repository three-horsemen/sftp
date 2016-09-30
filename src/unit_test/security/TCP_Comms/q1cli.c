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
	printf("getSourceAddrfromSockDesc :: %s\n",getSourceAddrfromSockDesc(sfd));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(12345);
	while(buffer!="quit")
	{
		connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
		printf("getSourceAddrfromSockDesc :: %s\n",getSourceAddrfromSockDesc(sfd));
		printf("getDestAddrfromSockDesc :: %s\n",getDestAddrfromSockDesc(sfd));
		scanf("%s",buffer);
		write(sfd,buffer,strlen(buffer));
		//printf("Kya ho raha hai????\n");
		recv(sfd,buffer,1024,0);
		//printf("Kya ho raha hai Part 2????\n");
		//read(sfd,str,maxlen,0);
		printf("%s\n",buffer);
	}
	close(sfd);
	//exit(0);
}
