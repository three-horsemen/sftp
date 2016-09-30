#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

void main()
{
	int s,len,sd,maxlen = 5256,clen=0;
	char buffer[5256];
	char* ptr = buffer;
	len = 0;
	int n = 0;
	//ls = socket(AF_INET,SOCK_STREAM,0);
	//int wait_size = 16; //Size of waiting clients
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(12345);
	//bind(ls,(struct sockaddr*)&saddr,sizeof(saddr));
	if((sd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("ERROR IN LISTEN SOCKET\n");
		return;
	}
	if((bind(sd,((struct sockaddr*)&saddr),sizeof(saddr)))<0)
	{
		printf("ERROR IN BINDING\n");
		return;
	}
	if(listen(sd,5)<0)
	{
		printf("ERROR LISTENING \n");
		return;
	}
	clen = sizeof(caddr);
	while(1)
	{
		printf("Hello World\n");
		s = accept(sd,(struct sockaddr*)&caddr,&clen);
		if(s<0)
		{
			printf("ERROR ACCEPTING CONNECTION \n");
			return;
		}
		n = recv(s,ptr,maxlen,0);
		printf("%s\n",ptr);
		/*while((n = recv(s,ptr,maxlen,0))>0)
		{
			printf("%s",ptr);
			ptr+=n;
			maxlen-=n;
			len+=n;
		}*/
		send(s,ptr,len,0);
		close(s);
	}
}
