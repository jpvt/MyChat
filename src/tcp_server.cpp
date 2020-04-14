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

using namespace std;

#include "../include/Client.h"
#include "../include/Monitor.h"
#include "../include/Server.h"

#define BUFFER_SIZE 4096

using namespace std;

int main(int argc, char ** argv){
	//Server Execution : ./server SERVER_PORT SERVER_NAME
	int server_port = atoi(argv[1]);
	string server_name = string(argv[2]);

	if(argc != 3){
		cerr << "ERROR: Failed to Execute, Invalid Parameters\n" << "Params Example: ./server SERVER_PORT SERVER_NAME\n";
		return 1;
	}

	Server server(server_name, server_port);
	server.run_server();

	return 0;
}