#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int custom_rand()
{
	return (((time(NULL)%10)*(time(NULL)%100))%80)+1;
}

int mpmod(int base, int exponent, int modulus)
{
    if ((base < 1) || (exponent < 0) || (modulus < 1))
    {
        return(-1);
    }
    long result = 1;
    while (exponent > 0)
    {
        if ((exponent % 2) == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = (int)(exponent / 2);
    }
    return (result);
}

int is_prime(int num)
{
    if((num & 1)==0)
        return num == 2;
    else
    {
        int i, limit = num/2 + 1;
        for (i = 3; i <= limit; i+=2){
            if (num % i == 0)
                return 0;
        }
    }
    return 1;
}

int next_pr(int num)
{
    int c;
    if(num < 2)
        c = 2;
    else if (num == 2)
        c = 3;
    else if(num & 1)
    {
        num += 2;
        c = is_prime(num) ? num : next_pr(num);
    }
    else
        c = next_pr(num-1);
    return c;
}

class DHExchange_clientContainer
{
private:
    bool valid;
    int client_private;
    int client_public;
    int server_public;
    int shared_secret;
public:
    DHExchange_clientContainer()
    {
        valid = false;
    }
    bool get_validity()
    {
        return valid;
    }
    bool set_validity(bool validity)
    {
        valid = validity;
    }
    int get_client_private()
    {
        return client_private;
    }
    void set_client_private(int new_client_private)
    {
        client_private = new_client_private;
    }
    int get_client_public()
    {
        return client_public;
    }
    void set_client_public(int new_client_public)
    {
        client_public = new_client_public;
    }
    int get_server_public()
    {
        return server_public;
    }
    void set_server_public(int new_server_public)
    {
        server_public = new_server_public;
    }
    int get_shared_secret()
    {
        return shared_secret;
    }
    void set_shared_secret(int new_shared_secret)
    {
        shared_secret = new_shared_secret;
    }
};

class DHExchange_serverContainer
{
private:
    bool valid;
    int server_private;
    int client_public;
    int server_public;
    int shared_secret;
public:
    DHExchange_serverContainer()
    {
        valid = false;
    }
    bool get_validity()
    {
        return valid;
    }
    bool set_validity(bool validity)
    {
        valid = validity;
    }
    int get_server_private()
    {
        return server_private;
    }
    void set_server_private(int new_server_private)
    {
        server_private = new_server_private;
    }
    int get_client_public()
    {
        return client_public;
    }
    void set_client_public(int new_client_public)
    {
        client_public = new_client_public;
    }
    int get_server_public()
    {
        return server_public;
    }
    void set_server_public(int new_server_public)
    {
        server_public = new_server_public;
    }
    int get_shared_secret()
    {
        return shared_secret;
    }
    void set_shared_secret(int new_shared_secret)
    {
        shared_secret = new_shared_secret;
    }
};


class Client_DHExchange
{
private:
    DHExchange_clientContainer client_keys_container;
public:
    int perform_key_exchange(char *server_ip_address, int server_port)
    {
        client_keys_container.set_validity(false);
    	int client_private_int;
    	char server_public[256];
    	char client_private[256];
    	char client_public[256];
    	char dh_p[256];
    	char dh_q[256];
    	char dh_secret[256];

        int socket_descriptor, len;
        struct sockaddr_in server_address;

        char buffer[256];

        //printf("Port number: %d\n", server_port);
        //printf("Server IP address: %s\n", server_ip_address);
    	memset(&server_address,0,sizeof(server_address));
    	server_address.sin_family = AF_INET;
    	server_address.sin_port = htons(server_port);
        server_address.sin_addr.s_addr = inet_addr(server_ip_address);
        if((socket_descriptor = socket(PF_INET,SOCK_STREAM,0)) < 0)
    	{
            perror("Error: Socket failed! >>socket()");
            return 1;
        }
    	else
    	{
            //printf("Successfully created socket: %d\n", socket_descriptor);
        }
    	if(connect(socket_descriptor,(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
    	{
            perror("Error: Connection failed! >>connect()");
            return 1;
        }
    	else
    	{
            //printf("Successfully connected to socket: %d\n", socket_descriptor);
        }

        ///Hello to server.
    	strcpy(buffer, "hello_exchangeDH");
        //printf("-> %s\n", buffer);
        len = write(socket_descriptor, buffer, strlen(buffer));
        //printf("Sent %d bytes.\n", len);

    	begin:
        ///Try to receive p.
        len = read(socket_descriptor, buffer, sizeof(buffer));
        if(len < 0)
    	{
            printf("Error: Received: %d bytes!\n",len);
            return 1;
        }
    	else
    	{
    	    //printf("Received %d bytes for p.\n",len);
    	    buffer[len] = '\0';
    	    //printf("<- ");
    	    //fputs(buffer,stdout);
    		//printf("\n");

    		strcpy(dh_p, buffer);
    		//printf("Diffie-Hellman parameter, p: %s\n", dh_p);
    	}

        ///Try to receive q.
        len = read(socket_descriptor, buffer, sizeof(buffer));
        if(len < 0)
    	{
            printf("Error: Received: %d bytes!\n",len);
            return 1;
        }
    	else
    	{
    	    //printf("Received %d bytes for q.\n",len);
    	    buffer[len] = '\0';
    	    //printf("<- ");
    	    //fputs(buffer,stdout);
    		//printf("\n");

    		strcpy(dh_q, buffer);
    		//printf("Diffie-Hellman parameter, q: %s\n", dh_q);
    	}

    	client_private_int = custom_rand();
    	sprintf(client_private, "%d", client_private_int);
    	//printf("Generated client private key: %s\n", client_private);
    	sprintf(client_public, "%d", mpmod(atoi(dh_q), client_private_int, atoi(dh_p)));
    	//printf("Calculated client public key: %s\n", client_public);
    	sprintf(buffer, "%s", client_public);

        //printf("-> %s\n", buffer);
        len = write(socket_descriptor, buffer, strlen(buffer));
        //printf("Sent %d bytes.\n",len);

        ///If the client public key was found to be zero or one, then restart the process.
        if(atoi(client_public) <= 1)
        {
        	//printf("The client public key was too low! Restarting the exchange.\n\n");
        	goto begin;
        }

        len = read(socket_descriptor, buffer, sizeof(buffer));
        if(len < 0)
    	{
            //printf("Error: Received: %d bytes!\n",len);
            return 1;
        }
    	else
    	{
    	    //printf("Received %d bytes.\n",len);
    	    buffer[len] = '\0';
    	    //printf("<- ");
    		//fputs(buffer, stdout);
    		//printf("\n");
    		strcpy(server_public, buffer);
    		//printf("Server public key: %s\n", server_public);

            ///If the server public key was found to be zero or one, then restart the process.
            if(atoi(server_public) <= 1)
            {
            	//printf("The server public key was too low! Restarting the exchange.\n\n");
            	goto begin;
            }
    	}

    	sprintf(dh_secret, "%d", mpmod(atoi(server_public), client_private_int, atoi(dh_p)));
    	//printf("Diffie-Hellman secret: %s\n\n", dh_secret);

        close(socket_descriptor);

        client_keys_container.set_validity(true);
        client_keys_container.set_client_private(client_private_int);
        client_keys_container.set_client_public(atoi(client_public));
        client_keys_container.set_server_public(atoi(server_public));
        client_keys_container.set_shared_secret(atoi(dh_secret));

        return 0;
    }

    DHExchange_clientContainer get_key_container()
    {
        return client_keys_container;
    }
};

class Server_DHExchange
{
private:
    DHExchange_serverContainer server_keys_container;
public:
    int perform_key_exchange(char *server_ip_address, int server_port, int number_of_exchanges)
    {
        server_keys_container.set_validity(false);

        int queueSize = 16;
    	int server_private_int;
    	char server_private[256];
    	char server_public[256];
    	char client_public[256];
    	char dh_p[256];
    	char dh_q[256];
    	char dh_secret[256];

    	int listenSocketDescriptor, s;
    	socklen_t clientAddrLen;
    	char buffer[256];

    	struct sockaddr_in servAddr, clientAddr;
    	int n;


    	listenSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
    	if(listenSocketDescriptor<0)
    	{
    		printf("Error: Socket failed!\n");
    		return 1;
    	}
    	else
    	{
    		//printf("Successfully created socket: %d\n",listenSocketDescriptor);
    	}

        ///These lines were added to ensure a port can be reused, if the server is restarted.
        int force_reuse_socket_port__yes = 1;
        if (setsockopt(listenSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes, sizeof(force_reuse_socket_port__yes)) == -1)
        {
            perror("setsockopt");
            return 1;
        }

    	memset(&servAddr,0,sizeof(servAddr));
        //printf("Port number: %d\n", server_port);
        //printf("Server IP address: %s\n", server_ip_address);
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = inet_addr(server_ip_address);
        servAddr.sin_port = htons(server_port);

    	if(bind(listenSocketDescriptor,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
    	{
    		printf("Error: Bind failed!\n");
    		return 1;
    	}
    	else
    	{
    		//printf("Successfully performed bind on socket\n");
    	}

    	if(listen(listenSocketDescriptor,queueSize)<0){
    		printf("Error: Listen failed!\n");
    		return 1;
    	}
    	else
    	{
    		//printf("Successfully listening to socket\n");
    	}
    	clientAddrLen = sizeof(clientAddr);

    	while(number_of_exchanges > 0)
    	{
    		//printf("Waiting for connection\n");
    		if((s = accept(listenSocketDescriptor,(struct sockaddr *) &clientAddr,&clientAddrLen))<0)
    		{
    			printf("Error: Connection was not accepted: %d!\n",s);
    			return 1;
    		}
    		else
    		{
    			//printf("Successfully accepted socket\n");
    		}

            ///Try to read a HELLO request from a client.
    		bzero(buffer,256);
    		if((n = read(s,buffer,255))>=0)
    			buffer[n] = '\0';
    		if(strcmp(buffer, "hello_exchangeDH") != 0)
    		{
    			printf("Invalid HELLO request from client.\n");
    			close(s);
    			continue;
    		}
    		//printf("HELLO request from client recognized.\n");
    		//printf("Read %d bytes: %s\n",n,buffer);
    	    begin:
            ///Try to send p.
    		sprintf(dh_p, "%d", next_pr(custom_rand()));
    		//printf("Generated random number p: %d\n", server_private);
    		//printf("Generated random number p: %s\n", dh_p);
            sprintf(buffer,"%s",dh_p);
            //printf("-> %s\n",buffer);
    		n = write(s,buffer,strlen(buffer));
    		//printf("Wrote %d bytes\n",n);
            sleep(1);

            ///Try to send q.
    		sprintf(dh_q, "%d", (custom_rand()%atoi(dh_p))+1);
    		//printf("Generated random number q: %s\n", dh_q);
    		//printf("Generated random number q: %d\n", server_private);
            sprintf(buffer,"%s",dh_q);
            //printf("-> %s\n",buffer);
    		n = write(s,buffer,strlen(buffer));
    		//printf("Wrote %d bytes\n",n);

            ///Try to receive client "public" key.
    		bzero(buffer,256);
    		if((n = read(s,buffer,255))>=0)
                buffer[n] = '\0';
    		//printf("Read %d bytes: %s\n",n,buffer);
    		strcpy(client_public, buffer);
    		//printf("Client public key: %s\n", client_public);

            ///If the client public key was found to be zero or one, then restart the process.
            if(atoi(client_public) <= 1)
            {
            	//printf("The client public key was too low! Restarting the exchange.\n\n");
            	goto begin;
            }

            ///Try to send server "public" key.
    		server_private_int = custom_rand();
    		sprintf(server_private, "%d", server_private_int);
    		//printf("Generated server private key: %s\n", server_private);
    		sprintf(server_public, "%d", mpmod(atoi(dh_q), server_private_int, atoi(dh_p)));
    		//printf("Calculated server public key: %s\n", server_public);
    		sprintf(buffer, "%s", server_public);
    		//printf("-> %s\n",buffer);
    		n = write(s,buffer,strlen(buffer));
    		//printf("Wrote %d bytes\n",n);

            ///If the server public key was found to be zero, then restart the process.
            //if(strcmp(server_public, "0") == 0)
            if(atoi(server_public) <= 1)
            {
            	//printf("The server public key was too low! Restarting the exchange.\n\n");
            	goto begin;
            }

            ///Calculate the shared secret.
    		sprintf(dh_secret, "%d", mpmod(atoi(client_public), server_private_int, atoi(dh_p)));
    		//printf("Diffie-Hellman secret: %s\n", dh_secret);
    		close(s);

            number_of_exchanges--;
    	}

        close(listenSocketDescriptor);

        server_keys_container.set_validity(true);
        server_keys_container.set_server_private(server_private_int);
        server_keys_container.set_client_public(atoi(client_public));
        server_keys_container.set_server_public(atoi(server_public));
        server_keys_container.set_shared_secret(atoi(dh_secret));

        return 0;
    }

    DHExchange_serverContainer get_key_container()
    {
        return server_keys_container;
    }
};
