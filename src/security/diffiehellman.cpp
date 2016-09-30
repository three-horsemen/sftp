#include "security/diffiehellman.hpp"

#include <iostream>
using namespace std;

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


int Client_DHExchange::perform_key_exchange(string server_ip_address__str, string server_port)
{
    SecureDataSocket clientSecureDataSocket;
    clientSecureDataSocket.setTargetIPAddress(server_ip_address__str);
    clientSecureDataSocket.setTargetPortNumber(server_port);
    clientSecureDataSocket.initSecureSocket();

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

    int len;
    if(clientSecureDataSocket.getValidity() == false)
    {
        perror("Error: Socket failed! >>socket()");
        return -1;
    }
    else
    {
        cout << "The client's socket was successfully created: " << clientSecureDataSocket.getSocketDescriptor() << endl;
    }

    cout << "The client is attempting to connect." << endl;
    if(clientSecureDataSocket.connectSecureSocket() < 0)
    {
        perror("Error: Client Connection failed! >>connect()");
        return 1;
    }
    else
    {
        //printf("Successfully connected to socket: %d\n", socket_descriptor);
    }

    ///Hello to server.
    clientSecureDataSocket.setBuffer("hello_exchangeDH");
    cout << endl << clientSecureDataSocket.getBuffer() << endl << endl;
cout << "ClientMark1" << endl;
    clientSecureDataSocket.writeSecureSocket();
cout << "ClientMark2" << endl;
	begin:
cout << "ClientMark2.1" << endl;
    ///Try to receive p.
    len = clientSecureDataSocket.readSecureSocket();
cout << "ClientMark3" << endl;
    if(len < 0)
	{
        printf("Error: Received: %d bytes!\n",len);
        return 1;
    }
	else
	{
        string buffer = clientSecureDataSocket.getBuffer();
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
    char buffer_charArray[256];
	client_private_int = custom_rand(100);
	sprintf(client_private, "%d", client_private_int);
	sprintf(client_public, "%d", mpmod(dh_q_int, client_private_int, dh_p_int));
    clientSecureDataSocket.setBuffer(charArray_to_string(buffer_charArray, strlen(buffer_charArray)));
    len = clientSecureDataSocket.writeSecureSocket();
cout << "ClientMark4" << endl;
    ///If the client public key was found to be zero or one, then restart the process.
    if(atoi(client_public) <= 1)
    {
    	//printf("The client public key was too low! Restarting the exchange.\n\n");
    	goto begin;
    }

    len = clientSecureDataSocket.readSecureSocket();
cout << "ClientMark5" << endl;
    if(len < 0)
	{
        cout << "ClientMark5.1" << endl;
        //printf("Error: Received: %d bytes!\n",len);
        return 1;
    }
	else
	{
        cout << "ClientMark5.2" << endl;
        char* temp = string_to_charArray(clientSecureDataSocket.getBuffer());
		strcpy(server_public, temp);
        free(temp);
cout << "ClientMark5.3" << endl;
        ///If the server public key was found to be zero or one, then restart the process.
        if(atoi(server_public) <= 1)
        {
            cout << "ClientMark5.4" << endl;
        	//printf("The server public key was too low! Restarting the exchange.\n\n");
        	goto begin;
            cout << "ClientMark5.5" << endl;
        }
	}
    int dh_secret_int = mpmod(atoi(server_public), client_private_int, dh_p_int);
    ///If the shared secret was found to be less than 10, then restart the process.
    if(dh_secret_int < 10)
    {
        cout << "ClientMark5.6" << endl;
        //printf("The shared secret was too low! Restarting the process.\n\n");
        goto begin;
        cout << "ClientMark5.7" << endl;
    }
	sprintf(dh_secret, "%d", dh_secret_int);
	//printf("Diffie-Hellman secret: %s\n\n", dh_secret);

cout << "ClientMark6" << endl;
    clientSecureDataSocket.destroySecureSocket();
cout << "ClientMark7" << endl;
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


// int Server_DHExchange::perform_key_exchange(string server_ip_address__str, int server_port, int number_of_exchanges)
int Server_DHExchange::perform_key_exchange(string server_ip_address__str, string server_port, int number_of_exchanges)
{
    SecureListenSocket serverSecureListenSocket;
    serverSecureListenSocket.setSourceIPAddress(server_ip_address__str);
    serverSecureListenSocket.setSourcePortNumber(server_port);


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
	char buffer_charArray[256];
    string buffer;
    char buffer_char[256];

	struct sockaddr_in servAddr, clientAddr;
	int n;


	//listenSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);

	if(serverSecureListenSocket.initSecureSocket()<0)
	{
		printf("Error: Server socket failed!\n");
		return 1;
	}
	else
	{
		//printf("Successfully created socket: %d\n",listenSocketDescriptor);
        cout << "Socket creation successful for the server: " << serverSecureListenSocket.getSocketDescriptor() << endl;
	}
/*
	memset(&servAddr,0,sizeof(servAddr));
    //printf("Port number: %d\n", server_port);
    //printf("Server IP address: %s\n", server_ip_address);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(server_ip_address);
    servAddr.sin_port = htons(server_port);
*/
	//if(bind(listenSocketDescriptor,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
    if(serverSecureListenSocket.bindSecureSocket()<0)
	{
		printf("Error: Bind failed!\n");
		return 1;
	}
	else
	{
		//printf("Successfully performed bind on socket\n");
        cout << "Bind was successfully performed for the server." << endl;
	}

	//if(listen(listenSocketDescriptor,queueSize)<0)
    if(serverSecureListenSocket.listenSecureSocket()<0)
    {
		printf("Error: Listen failed!\n");
		return 1;
	}
	else
	{
		//printf("Successfully listening to socket\n");
        cout << "Listen mode activated for the server." << endl;
	}
	clientAddrLen = sizeof(clientAddr);


    SecureDataSocket newSecureDataSocket;
	while(number_of_exchanges > 0)
	{
		//printf("Waiting for connection\n");
		//if((s = accept(listenSocketDescriptor,(struct sockaddr *) &clientAddr,&clientAddrLen))<0)
        newSecureDataSocket = serverSecureListenSocket.acceptSecureSocket();
        if(newSecureDataSocket.getValidity() == false)
		{
			printf("Error: Connection was not accepted: %d!\n",s);
			return 1;
		}
		else
		{
			//printf("Successfully accepted socket\n");
		}

        ///Try to read a HELLO request from a client.
		//bzero(buffer,256);
		//if((n = read(s,buffer,255))>=0)
        if((n = newSecureDataSocket.readSecureSocket())<=0)
			cout << "Something went wrong with the read!" << endl;

		//if(strcmp(buffer, "hello_exchangeDH") != 0)
        if(newSecureDataSocket.getBuffer() == "hello_exchangeDH")
		{
			printf("Invalid HELLO request from client.\n");
			//close(s);
            newSecureDataSocket.destroySecureSocket();
			continue;
		}
		//printf("HELLO request from client recognized.\n");
		//printf("Read %d bytes: %s\n",n,buffer);
	    begin:
        ///Try to send p and q.
        dh_p_int = next_pr(custom_rand(100));
        dh_q_int = custom_rand(dh_p_int);
        sprintf(buffer_char,"%d#%d", dh_p_int, dh_q_int);
		//n = write(s,buffer,strlen(buffer));
        newSecureDataSocket.setBuffer(charArray_to_string(buffer_char));
        n = newSecureDataSocket.writeSecureSocket();
        ///Try to receive client "public" key.
		//bzero(buffer_char,256);
		//if((n = read(s,buffer,255))>=0)
        if((n = newSecureDataSocket.readSecureSocket())<=0)
            cout << "Something went wrong with the read!" << endl;
		//strcpy(client_public, buffer);
        string client_public_str = newSecureDataSocket.getBuffer();

        ///If the client public key was found to be zero or one, then restart the process.
        if(atoi(string_to_charArray(client_public_str)) <= 1)
        {
        	//printf("Server: The client public key was too low! Restarting the exchange.\n\n");
        	goto begin;
        }

        ///Try to send server "public" key.
		server_private_int = custom_rand(100);
		sprintf(server_private, "%d", server_private_int);
		sprintf(server_public, "%d", mpmod(dh_q_int, server_private_int, dh_p_int));
		sprintf(buffer_char, "%s", server_public);
		//n = write(s,buffer,strlen(buffer));
        newSecureDataSocket.setBuffer(charArray_to_string(buffer_char));
        n = newSecureDataSocket.writeSecureSocket();

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
		//close(s);
        newSecureDataSocket.destroySecureSocket();

        number_of_exchanges--;
	}
    //close(listenSocketDescriptor);
    serverSecureListenSocket.destroySecureSocket();

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
