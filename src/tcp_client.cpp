#include <iostream>
#include <unistd.h>
// SOCKETS ///////////////
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//////////////////////////
#include <time.h>
#include <string.h>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>

#define BUFFER_SIZE 4096

#include "../include/Client.h"
#include "../include/Monitor.h"
#include "../include/Server.h"

/*
Create a socket;
Create a Server Address Structure for the server we're connecting with;
Connect to the server on the socket;
While loop:
    Enter lines of text;
    Send to server;
    Wait for response;
    Display response;
Close the socket;
*/

using namespace std;

int main(int argc, char ** argv){
    //Client Execution : ./client CLIENT_IP SERVER_PORT CLIENT_NAME
    string client_ip = string(argv[1]);
    int port = atoi(argv[2]);
	string username = string(argv[3]);

    if(argc != 4){
        cerr << "ERROR: Failed to Execute, Invalid Parameters\n" << "Params Example: ./client CLIENT_IP SERVER_PORT CLIENT_NAME\n";
		return 1;
    }

    Client client(username, client_ip, port);
    client.run();


    return 0;
}
