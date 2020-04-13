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

#define MAX_CLIENTS 100
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

	cout << "Starting chat " << server_name << "on port " << server_port << endl;

	//Listening configs
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == -1){
		cerr << "ERROR: Can't Create Socket\nERRO: Não conseguiu criar socket\n";
		return -1;
	}

	// Bind the socket to IP/Port
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr); //binding information

	if(bind(listening, (sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		cerr << "ERROR: Can't bind to IP/Port\nERRO: Não conseguiu conectar com IP/Porta\n";
		return -2;
	}

	//Marks the socket for listening
	if(listen(listening, MAX_CLIENTS)){
		cerr << "ERROR: Can't listen\nERRO: Não conseguiu escutar\n";
		return -3;
	}

	//Accept Call
	sockaddr_in client;
	socklen_t client_size = sizeof(client);
	char host[NI_MAXHOST]; //buffer that holds host name
	char svc[NI_MAXSERV]; //buffer that holds service name

	int client_socket = accept(listening, (sockaddr*)&client, &client_size);

	if(client_socket == -1){
		cerr << "ERROR: Can't connect with client\nERRO: Não conseguiu se conectar ao cliente\n";
		return -4;
	}
	//Close listening socket
	close(listening);
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	//Getting name of the computer
	int result = getnameinfo((sockaddr*)&client, 
							 client_size, 
							 host,
							 NI_MAXHOST,
							 svc,
							 NI_MAXSERV,
							 0);

	if(result){

		cout << host << " connected on " << svc << endl;
	}else{

		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on " << ntohs(client.sin_port) << endl;
	}

	//while receiving display message, echo message
	char buf[BUFFER_SIZE];
	while(true){
		//Clear the buffer
		memset(buf, 0, BUFFER_SIZE);

		//Wait for a message
		int bytes_recv = recv(client_socket, buf, BUFFER_SIZE, 0);
		
		if(bytes_recv == -1){
			cerr <<"ERROR: Connection failed\nERRO: Conexao falhou\n";
			break;
		}

		if(bytes_recv == 0){
			cout << "The client " << "Fulano" << " disconnected\n";
			break;
		}

		//Display message
		cout << "Received: " << string(buf, 0, bytes_recv) << endl;

		//Resend message
		send(client_socket, buf, bytes_recv + 1, 0); 
	}

	//Close Socket
	close(client_socket);

	



	return 0;
}