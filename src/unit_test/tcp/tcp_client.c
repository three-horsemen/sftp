#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int s, servPort, len;
    struct sockaddr_in serverAddr;

    char buf[256];
    if (argc != 4) {
       fprintf(stderr,"Usage: %s <Server IP Address> <Server Port Number> <String>\n", argv[0]);
       exit(0);
    }
    char* servName = argv[1];
    servPort = atoi(argv[2]);
    char* a = argv[3];

printf("Port number: %d\n", servPort);
printf("Server IP address: %s\n", argv[1]);
	memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(servPort);
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    s=socket(PF_INET,SOCK_STREAM,0);
    if(s<0) {
        printf("Error: Socket failed!\n");
        return 1;
    }else{
        printf("Successfully created socket: %d\n",s);
    }
    if(connect(s,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
        perror("Error: Connection failed!");
        return 1;
    }else{
        printf("Successfully connected to socket: %d\n",s);
    }
    printf("-> %s\n",a);
    len = write(s,a,strlen(a));
    printf("Sent %d bytes\n",len);

    len = read(s,buf,255);
    if(len<0){
        printf("Error: Received: %d bytes!\n",len);
        return 1;
    }else{
	    printf("Received %d bytes\n",len);
	    buf[len] = '\0';
	    printf("<- ");
	    fputs(buf,stdout);
	}
    printf("\n");

    close(s);

    return 0;
}
