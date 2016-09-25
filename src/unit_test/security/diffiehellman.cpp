#include <iostream>
#include "security/diffiehellman.hpp"

using namespace std;

int main()
{
    char* server_ip_address = "127.0.0.1";
    int server_port = 8082;

    int child_pid;
    if(child_pid = fork()) ///The parent.
    {
        Server_DHExchange server_dhexchange;
        server_dhexchange.perform_key_exchange(server_ip_address, server_port, 1);

        if(server_dhexchange.get_key_container().get_validity())
            cout << "Unit tester: The shared secret with the server is " << server_dhexchange.get_key_container().get_shared_secret() << endl;
        else
            cout << "Unit tester: The server's shared secret wasn't set." << endl;
    }
    else ///The child.
    {
        Client_DHExchange client_dhexchange;
        client_dhexchange.perform_key_exchange(server_ip_address, server_port);

        if(client_dhexchange.get_key_container().get_validity())
            cout << "Unit tester: The shared secret with the client is " << client_dhexchange.get_key_container().get_shared_secret() << endl;
        else
            cout << "Unit tester: The client's shared secret wasn't set." << endl;
        exit(0);
    }

    if(getpid() != child_pid)
        wait();

    return 0;
}
