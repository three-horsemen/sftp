#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "security/diffiehellman.hpp"
#include "security/cryptstr.hpp"
using namespace std;

int main()
{
    ///We can use either the loopback address, or the IP address assigned to the system's interface (for debugging purposes).
    //char* server_ip_address = "172.16.0.2";
    string server_ip_address = "127.0.0.1";
    int server_port = 8082;
    string server_port_str = "8082";
    int child_pid;
    if(child_pid = fork()) ///The parent.
    {
        cout << "The server (parent process) is beginning: #" << getpid() << endl;
        Server_DHExchange server_dhexchange;
        server_dhexchange.perform_key_exchange(server_ip_address, server_port_str, 1);
        cout << "Server's job is done." << endl;
        if(server_dhexchange.get_key_container().get_validity())
            cout << "Unit tester: The shared secret with the server is " << server_dhexchange.get_key_container().get_shared_secret() << endl;
        else
            cout << "Unit tester: The server's shared secret wasn't set." << endl;
        wait();
    }
    else ///The child.
    {
        sleep(2);
        cout << "The client (child process) is beginning: #" << getpid() << endl;
        Client_DHExchange client_dhexchange;
        client_dhexchange.perform_key_exchange(server_ip_address, server_port_str);
        cout << "Client's job is done." << endl;
        if(client_dhexchange.get_key_container().get_validity())
            cout << "Unit tester: The shared secret with the client is " << client_dhexchange.get_key_container().get_shared_secret() << endl;
        else
            cout << "Unit tester: The client's shared secret wasn't set." << endl;
        //exit(0);
    }
    /*
    if(getpid() != child_pid) /// The parent.
        wait();
    */
    return 0;
}
