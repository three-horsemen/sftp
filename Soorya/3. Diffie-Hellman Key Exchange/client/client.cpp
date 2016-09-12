#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <time.h>
#include <math.h>

#include <iostream>
#include <string>
using namespace std;

int custom_rand()
{
	return (((time(NULL)%10)*(time(NULL)%100))%50)+1;
}


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


int main(int argc, char *argv[])
{
	int client_private_int;
	char server_public[256];
	char client_private[256];
	char client_public[256];
	char dh_p[256];
	char dh_q[256];
	char dh_secret[256];

    int socketDescriptor, servPort, len;
    struct sockaddr_in serverAddr;

    char buffer[256];
    if (argc != 3) {
       fprintf(stderr,"Usage: %s <Server IP Address> <Server Port Number>\n", argv[0]);
       exit(0);
    }
    char* servName = argv[1];
    servPort = atoi(argv[2]);

printf("Port number: %d\n", servPort);
printf("Server IP address: %s\n", argv[1]);
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(servPort);
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	socketDescriptor = socket(PF_INET,SOCK_STREAM,0);
    if(socketDescriptor < 0)
	{
        printf("Error: Socket failed!\n");
        return 1;
    }
	else
	{
        printf("Successfully created socket: %d\n", socketDescriptor);
    }
    
	if(connect(socketDescriptor,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0)
	{
        perror("Error: Connection failed!");
        return 1;
    }
	else
	{
        printf("Successfully connected to socket: %d\n", socketDescriptor);
    }



//Hello to server.
	strcpy(buffer, "hello_exchangeDH");

    printf("-> %s\n", buffer);
    len = write(socketDescriptor, buffer, strlen(buffer));
    printf("Sent %d bytes.\n", len);


	begin:
//Try to receive p.
    len = read(socketDescriptor, buffer, sizeof(buffer));
    if(len < 0)
	{
        printf("Error: Received: %d bytes!\n",len);
        return 1;
    }
	else
	{
	    printf("Received %d bytes for p.\n",len);
	    buffer[len] = '\0';
	    printf("<- ");
	    fputs(buffer,stdout);
		printf("\n");
		
		strcpy(dh_p, buffer);
		printf("Diffie-Hellman parameter, p: %s\n", dh_p);
	}

//Try to receive q.
    len = read(socketDescriptor, buffer, sizeof(buffer));
    if(len < 0)
	{
        printf("Error: Received: %d bytes!\n",len);
        return 1;
    }
	else
	{
	    printf("Received %d bytes for q.\n",len);
	    buffer[len] = '\0';
	    printf("<- ");
	    fputs(buffer,stdout);
		printf("\n");

		strcpy(dh_q, buffer);
		printf("Diffie-Hellman parameter, q: %s\n", dh_q);
	}

	client_private_int = custom_rand();
	sprintf(client_private, "%d", client_private_int);
	printf("Generated client private key: %s\n", client_private);
	//sprintf(client_public, "%d", (int)fmod((powl((double)(atoi(dh_q)%15),(double)(client_private_int%5))), (double)atoi(dh_p)));
	sprintf(client_public, "%d", mpmod(atoi(dh_q), client_private_int, atoi(dh_p)));
	printf("Calculated client public key: %s\n", client_public);
	sprintf(buffer, "%s", client_public);

    printf("-> %s\n", buffer);
    len = write(socketDescriptor, buffer, strlen(buffer));
    printf("Sent %d bytes.\n",len);

//If the client public key was found to be zero, then restart the process.
//if(strcmp(client_public, "0") == 0)
if(atoi(client_public) <= 1)
{
	printf("The client public key was too low! Restarting the exchange.\n\n");
	goto begin;
}

    len = read(socketDescriptor, buffer, sizeof(buffer));
    if(len < 0)
	{
        printf("Error: Received: %d bytes!\n",len);
        return 1;
    }
	else
	{
	    printf("Received %d bytes.\n",len);
	    buffer[len] = '\0';
	    printf("<- ");
		fputs(buffer, stdout);
		printf("\n");
		strcpy(server_public, buffer);
		printf("Server public key: %s\n", server_public);
		
//If the server public key was found to be zero, then restart the process.
//if(strcmp(server_public, "0") == 0)
if(atoi(server_public) <= 1)
{
	printf("The server public key was too low! Restarting the exchange.\n\n");
	goto begin;
}
	}

	//sprintf(dh_secret, "%d", (int)fmod((powl((double)(atoi(server_public)%15),(double)(client_private_int%5))), (double)atoi(dh_p)));
	sprintf(dh_secret, "%d", mpmod(atoi(server_public), client_private_int, atoi(dh_p)));
	printf("Diffie-Hellman secret: %s\n", dh_secret);

    printf("\n");
    close(socketDescriptor);

    return 0;
}
