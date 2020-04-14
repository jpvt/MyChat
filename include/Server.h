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
#include <vector>
#include <signal.h>

#define MAX_CLIENTS 100
#define MSG_SIZE 1024

Monitor chat_log("chat_log.txt");
Monitor error_log("error_log.txt");


class Server{

    int server_port, listening;
    string server_name;
    sockaddr_in server_addr;
    int address_size;

    struct ClientInfo{
        int file_descriptor;
        sockaddr_in address;
    };

    vector<pair<thread, ClientInfo *>> thread_client;
    mutex server_mutex;

    public:
        Server(string name, int port);
        void manage(ClientInfo * client);
        void sendToClients(const char *msg);
        void run_server();
};

Server::Server(string name, int port){
    this->server_port = port;
    this->server_name = name;


    cout << "Starting chat " << this->server_name << " on port " << this->server_port << endl;    
    //Listening configs
    cout << "Preparing listening configs\n";
    this->listening = socket(AF_INET, SOCK_STREAM, 0);
	if(this->listening == -1){
        error_log.MonitorWrite("ERROR: Can't Create Socket");
        exit(EXIT_FAILURE);
	}

    // Bind the socket to IP/Port
    cout << "Binding the socket to IP/Port\n";
    this->server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    this->server_addr.sin_port = htons(this->server_port);

    if(bind(listening, (sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		error_log.MonitorWrite("ERROR: Can't bind to IP/Port");
        exit(EXIT_FAILURE);
	}

    //Marks the socket for listening
    cout << "Marking the socket for listening\n";
	if(listen(this->listening, MAX_CLIENTS)){
		error_log.MonitorWrite("ERROR: Can't listen");
        exit(EXIT_FAILURE);
	}

    cout << "Chat ready for running !" << endl;
}
inline void Server::sendToClients(const char *msg){
    for(u_int i = 0; i  < thread_client.size(); i++)
        send(thread_client[i].second->file_descriptor, msg, strlen(msg)+1, 0);
}
void Server::manage( ClientInfo * client){
    
    char msg[MSG_SIZE];
    char tmp[MSG_SIZE];
    memset(msg, 0, MSG_SIZE);

    // Lendo o nome de usuario
    read(client->file_descriptor, msg, 25);
    // Informando aos clientes novo usuario
    strcpy(tmp, "User ");
    strcat(tmp, msg);
    strcat(tmp, " has connected !\n");
    //sendToClients(tmp); BUGADO

    // Printando no console (com exclusao mutua)
    server_mutex.lock();
    std::cout << "User " << msg << " with IP " << inet_ntoa(client->address.sin_addr) << " joined!\n";
    server_mutex.unlock();


    while(true){
        memset(msg, 0, MSG_SIZE);
        int result = read(client->file_descriptor, msg, MSG_SIZE);
        if(result <= 0)
            continue;

        sendToClients(msg);
        chat_log.MonitorWrite(string(msg));
    }
}
void Server::run_server(){

    while(true){
        ClientInfo *client = new ClientInfo;
        client->file_descriptor = accept(listening, (sockaddr*)&client->address, (socklen_t*)&address_size);

        //Push to Pair Thread-Client the current thread+client
        this->thread_client.push_back( make_pair(thread(&Server::manage, this, client), client));

    }
    for(int i = 0; i < thread_client.size(); i++){
        thread_client[i].first.join();
    }
}