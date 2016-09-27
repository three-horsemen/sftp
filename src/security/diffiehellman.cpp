#include "security/diffiehellman.hpp"

DHExchange_clientContainer::DHExchange_clientContainer()
{
    valid = false;
}
bool DHExchange_clientContainer::get_validity()
{
    return valid;
}
bool DHExchange_clientContainer::set_validity(bool validity)
{
    valid = validity;
}
int DHExchange_clientContainer::get_client_private()
{
    return client_private;
}
void DHExchange_clientContainer::set_client_private(int new_client_private)
{
    client_private = new_client_private;
}
int DHExchange_clientContainer::get_client_public()
{
    return client_public;
}
void DHExchange_clientContainer::set_client_public(int new_client_public)
{
    client_public = new_client_public;
}
int DHExchange_clientContainer::get_server_public()
{
    return server_public;
}
void DHExchange_clientContainer::set_server_public(int new_server_public)
{
    server_public = new_server_public;
}
int DHExchange_clientContainer::get_shared_secret()
{
    return shared_secret;
}
void DHExchange_clientContainer::set_shared_secret(int new_shared_secret)
{
    shared_secret = new_shared_secret;
}

DHExchange_serverContainer::DHExchange_serverContainer()
{
    valid = false;
}
bool DHExchange_serverContainer::get_validity()
{
    return valid;
}
bool DHExchange_serverContainer::set_validity(bool validity)
{
    valid = validity;
}
int DHExchange_serverContainer::get_server_private()
{
    return server_private;
}
void DHExchange_serverContainer::set_server_private(int new_server_private)
{
    server_private = new_server_private;
}
int DHExchange_serverContainer::get_client_public()
{
    return client_public;
}
void DHExchange_serverContainer::set_client_public(int new_client_public)
{
    client_public = new_client_public;
}
int DHExchange_serverContainer::get_server_public()
{
    return server_public;
}
void DHExchange_serverContainer::set_server_public(int new_server_public)
{
    server_public = new_server_public;
}
int DHExchange_serverContainer::get_shared_secret()
{
    return shared_secret;
}
void DHExchange_serverContainer::set_shared_secret(int new_shared_secret)
{
    shared_secret = new_shared_secret;
}


//int Client_DHExchange::perform_key_exchange(char *server_ip_address, int server_port)
int Client_DHExchange::perform_key_exchange(string server_ip_address__str, int server_port)
{
    char* server_ip_address = string_to_charArray(server_ip_address__str);
    client_keys_container.set_validity(false);
	int client_private_int;
	char server_public[256];
	char client_private[256];
	char client_public[256];
	char dh_p[256];
	char dh_q[256];
    int dh_p_int;
    int dh_q_int;
	char dh_secret[256];

    int socket_descriptor, len;
    struct sockaddr_in server_address;

    char buffer[256];

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

    ///These lines were added to ensure a port can be reused, if the server is restarted.
    int force_reuse_socket_port__yes = 1;
    if (setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &force_reuse_socket_port__yes, sizeof(force_reuse_socket_port__yes)) == -1)
    {
        perror("setsockopt");
        return 1;
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
        bool hash_seen_flag = false;
        dh_p_int = 0;
        dh_q_int = 0;
        for(int index = 0; index < len; index++)
        {
            if(buffer[index] != '#')
            {
                if(hash_seen_flag == false)
                {
                    dh_p_int *= 10;
                    dh_p_int += buffer[index]-48;
                }
                else
                {
                    dh_q_int *= 10;
                    dh_q_int += buffer[index]-48;
                }
            }
            else
            {
                hash_seen_flag = true;
            }
        }
	}
	client_private_int = custom_rand(100);
	sprintf(client_private, "%d", client_private_int);
	sprintf(client_public, "%d", mpmod(dh_q_int, client_private_int, dh_p_int));
	sprintf(buffer, "%s", client_public);
    len = write(socket_descriptor, buffer, strlen(buffer));
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
	    buffer[len] = '\0';
		strcpy(server_public, buffer);

        ///If the server public key was found to be zero or one, then restart the process.
        if(atoi(server_public) <= 1)
        {
        	//printf("The server public key was too low! Restarting the exchange.\n\n");
        	goto begin;
        }
	}

    int dh_secret_int = mpmod(atoi(server_public), client_private_int, dh_p_int);
    ///If the shared secret was found to be less than 10, then restart the process.
    if(dh_secret_int < 10)
    {
        //printf("The shared secret was too low! Restarting the process.\n\n");
        goto begin;
    }

	sprintf(dh_secret, "%d", dh_secret_int);
	//printf("Diffie-Hellman secret: %s\n\n", dh_secret);

    close(socket_descriptor);

    client_keys_container.set_validity(true);
    client_keys_container.set_client_private(client_private_int);
    client_keys_container.set_client_public(atoi(client_public));
    client_keys_container.set_server_public(atoi(server_public));
    client_keys_container.set_shared_secret(atoi(dh_secret));

    return 0;
}

DHExchange_clientContainer Client_DHExchange::get_key_container()
{
    return client_keys_container;
}


int Server_DHExchange::perform_key_exchange(string server_ip_address__str, int server_port, int number_of_exchanges)
{
    char* server_ip_address = string_to_charArray(server_ip_address__str);

    server_keys_container.set_validity(false);

    int queueSize = 16;
	int server_private_int;
	char server_private[256];
	char server_public[256];
	char client_public[256];
    int dh_p_int;
    int dh_q_int;
    int dh_secret_int;
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
        ///Try to send p and q.
        dh_p_int = next_pr(custom_rand(100));
		//sprintf(dh_p, "%d", next_pr(custom_rand(100)));
        sprintf(buffer,"%d",dh_p_int);
        dh_q_int = custom_rand(dh_p_int);
        //sprintf(dh_q, "%d", custom_rand(atoi(dh_p)));
        sprintf(buffer,"%d#%d", dh_p_int, dh_q_int);
		n = write(s,buffer,strlen(buffer));
        ///Try to receive client "public" key.
		bzero(buffer,256);
		if((n = read(s,buffer,255))>=0)
            buffer[n] = '\0';
		strcpy(client_public, buffer);

        ///If the client public key was found to be zero or one, then restart the process.
        if(atoi(client_public) <= 1)
        {
        	//printf("Server: The client public key was too low! Restarting the exchange.\n\n");
        	goto begin;
        }

        ///Try to send server "public" key.
		server_private_int = custom_rand(100);
		sprintf(server_private, "%d", server_private_int);
		sprintf(server_public, "%d", mpmod(dh_q_int, server_private_int, dh_p_int));
		sprintf(buffer, "%s", server_public);
		n = write(s,buffer,strlen(buffer));

        ///If the server public key was found to be zero, then restart the process.
        if(atoi(server_public) <= 1)
        {
        	//printf("The server public key was too low! Restarting the exchange.\n\n");
        	goto begin;
        }

        dh_secret_int = mpmod(atoi(client_public), server_private_int, dh_p_int);

        ///If the shared secret was found to be less than 10, then restart the process.
        if(dh_secret_int < 10)
        {
            //printf("The shared secret was too low! Restarting the process.\n\n");
            goto begin;
        }

        ///Calculate the shared secret.
		close(s);

        number_of_exchanges--;
	}
    close(listenSocketDescriptor);

    server_keys_container.set_validity(true);
    server_keys_container.set_server_private(server_private_int);
    server_keys_container.set_client_public(atoi(client_public));
    server_keys_container.set_server_public(atoi(server_public));
    server_keys_container.set_shared_secret(dh_secret_int);

    return 0;
}

DHExchange_serverContainer Server_DHExchange::get_key_container()
{
    return server_keys_container;
}
