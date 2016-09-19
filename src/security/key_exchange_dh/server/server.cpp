#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>
#define queueSize 16


int mpmod(int base, int exponent, int modulus) {
  if ((base < 1) || (exponent < 0) || (modulus < 1)) {
    return(-1);
  }
  long result = 1;
  while (exponent > 0) {
    if ((exponent % 2) == 1) {
      result = (result * base) % modulus;
    }
    base = (base * base) % modulus;
    exponent = (int)(exponent / 2);
  }
return (result);
}

int is_prime(int num){
    if((num & 1)==0)
        return num == 2;
    else {
        int i, limit = num/2 + 1;
        for (i = 3; i <= limit; i+=2){
            if (num % i == 0)
                return 0;
        }
    }
    return 1;
}
int next_pr(int num){
    int c;
    if(num < 2)
        c = 2;
    else if (num == 2)
        c = 3;
    else if(num & 1){
        num += 2;
        c = is_prime(num) ? num : next_pr(num);
    } else
        c = next_pr(num-1);

    return c;
}

int custom_rand()
{
	return ((((time(NULL)%9)*(time(NULL)%99))%99)+1);
}

int main(int argc, char** argv)
{
	int server_private_int;
	char server_private[256];
	char server_public[256];
	char client_public[256];
	char dh_p[256];
	char dh_q[256];
	char dh_secret[256];

	//int server_private;
	int listenSocketDescriptor, s, portno;
	socklen_t clientAddrLen;
	char buffer[256];

	struct sockaddr_in servAddr, clientAddr;
	int n;
	if (argc < 2)
	{
		printf("Invalid arguments\n");
		exit(1);
	}

	listenSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	if(listenSocketDescriptor<0)
	{
		printf("Error: Socket failed!\n");
		return 1;
	}
	else
	{
		printf("Successfully created socket: %d\n",listenSocketDescriptor);
	}

	memset(&servAddr,0,sizeof(servAddr));
    portno = atoi(argv[2]);
printf("Port number: %d\n", portno);
printf("Server IP address: %s\n", argv[1]);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(portno);

	if(bind(listenSocketDescriptor,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
	{
		printf("Error: Bind failed!\n");
		return 1;
	}
	else
	{
		printf("Successfully performed bind on socket\n");
	}

	if(listen(listenSocketDescriptor,queueSize)<0){
		printf("Error: Listen failed!\n");
		return 1;
	}
	else
	{
		printf("Successfully listening to socket\n");
	}
	clientAddrLen = sizeof(clientAddr);

	while(1)
	{
		printf("Waiting for connection\n");

		s = accept(listenSocketDescriptor,(struct sockaddr *) &clientAddr,&clientAddrLen);
		if(s<0)
		{
			printf("Error: Connection was not accepted: %d!\n",s);
			return 1;
		}
		else
		{
			printf("Successfully accepted socket\n");
		}

//Try to read a HELLO request from a client.
		bzero(buffer,256);
		n = read(s,buffer,255);
		if(n>=0)
			buffer[n] = '\0';
		if(strcmp(buffer, "hello_exchangeDH") != 0)
		{
			printf("Invalid HELLO request from client.\n");
			close(s);
			continue;
		}
		printf("HELLO request from client recognized.\n");
		printf("Read %d bytes: %s\n",n,buffer);
	begin:
//Try to send p.
		sprintf(dh_p, "%d", next_pr(custom_rand()));
		//server_private = custom_rand();
		//printf("Generated random number p: %d\n", server_private);
		printf("Generated random number p: %s\n", dh_p);
        sprintf(buffer,"%s",dh_p);
        printf("-> %s\n",buffer);
		n = write(s,buffer,strlen(buffer));
		printf("Wrote %d bytes\n",n);

sleep(1);

//Try to send q.
		sprintf(dh_q, "%d", (custom_rand()%atoi(dh_p))+1);
		//sprintf(dh_q, "%d", (custom_rand()%atoi("10"))+1);
		//server_private = custom_rand();
		printf("Generated random number q: %s\n", dh_q);
		//printf("Generated random number q: %d\n", server_private);
        sprintf(buffer,"%s",dh_q);
        printf("-> %s\n",buffer);
		n = write(s,buffer,strlen(buffer));
		printf("Wrote %d bytes\n",n);

//Try to receive client "public" key.
		bzero(buffer,256);
		n = read(s,buffer,255);
		if(n>=0)
            		buffer[n] = '\0';
		printf("Read %d bytes: %s\n",n,buffer);
		strcpy(client_public, buffer);
		printf("Client public key: %s\n", client_public);

//If the client public key was found to be zero, then restart the process.
//if(strcmp(client_public, "0") == 0)
if(atoi(client_public) <= 1)
{
	printf("The client public key was too low! Restarting the exchange.\n\n");
	goto begin;
}

//Try to send server "public" key.
		server_private_int = custom_rand();
		sprintf(server_private, "%d", server_private_int);
		printf("Generated server private key: %s\n", server_private);
		sprintf(server_public, "%d", mpmod(atoi(dh_q), server_private_int, atoi(dh_p)));
		printf("Calculated server public key: %s\n", server_public);
		sprintf(buffer, "%s", server_public);
		printf("-> %s\n",buffer);
		n = write(s,buffer,strlen(buffer));
		printf("Wrote %d bytes\n",n);

//If the server public key was found to be zero, then restart the process.
//if(strcmp(server_public, "0") == 0)
if(atoi(server_public) <= 1)
{
	printf("The server public key was too low! Restarting the exchange.\n\n");
	goto begin;
}


//Calculate the shared secret.
		//sprintf(dh_secret, "%d", (int)fmod((powl((double)(atoi(client_public)%15),(double)(server_private_int%5))), (double)atoi(dh_p)));
		sprintf(dh_secret, "%d", mpmod(atoi(client_public), server_private_int, atoi(dh_p)));
		printf("Diffie-Hellman secret: %s\n", dh_secret);
		close(s);
	}

     close(listenSocketDescriptor);
     return 0;
}
