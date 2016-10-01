#include "security/cryptmath.hpp"
#include "security/cryptstr.hpp"
#include "security/securesocket.hpp"
class DHExchange_clientContainer
{
private:
    bool valid;
    int client_private;
    int client_public;
    int server_public;
    int shared_secret;
public:
    DHExchange_clientContainer();
    bool get_validity();
    bool set_validity(bool validity);
	int get_client_private();
    void set_client_private(int new_client_private);
    int get_client_public();
    void set_client_public(int new_client_public);
    int get_server_public();
    void set_server_public(int new_server_public);
    int get_shared_secret();
    void set_shared_secret(int new_shared_secret);
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
    DHExchange_serverContainer();
    bool get_validity();
    bool set_validity(bool validity);
    int get_server_private();
    void set_server_private(int new_server_private);
    int get_client_public();
    void set_client_public(int new_client_public);
    int get_server_public();
    void set_server_public(int new_server_public);
    int get_shared_secret();
    void set_shared_secret(int new_shared_secret);
};

class Client_DHExchange
{
private:
    DHExchange_clientContainer client_keys_container;
public:
    int perform_key_exchange(std::string server_ip_address, std::string server_port);
    DHExchange_clientContainer get_key_container();
};

class Server_DHExchange
{
private:
    DHExchange_serverContainer server_keys_container;
public:
    int perform_key_exchange(std::string server_ip_address, std::string server_port, int number_of_exchanges);
    DHExchange_serverContainer get_key_container();
};
