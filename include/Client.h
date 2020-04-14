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

//#include "Client.cpp"
#define MSG_SIZE 1024


using namespace std;

class Client{

    public:
        int client_socket, port;
        string username, ip_address;


        thread t_rcv;
        sockaddr_in client_addr;
        int client_addr_len;   
        //Constructor
        Client();
        Client(string username, string ip_address, int port);

        // GET
        int getClientSocket();
        int getPort();
        string getUsername();
        string getIP();

        // SET
        void setClientSocket(int c_sock);
        void setUsername(string name);
        void setIP(string ip);
        void setPort(int s_port);

        // Other Methods
        void response();
        void run();


};

Client::Client(string name, string ip, int port){
    //Create a socket
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    setUsername(name);
    setIP(ip);
    setPort(port);

    //Create a Server Address Structure for the server we're connecting with;
    this->client_addr.sin_family = AF_INET;
    this->client_addr.sin_port = htons(port);
    inet_aton(ip.c_str(), &client_addr.sin_addr);
    this->client_addr_len = sizeof(client_addr);

}

void Client::response(){
    char buf[MSG_SIZE];
    
    while(true){
        memset(buf,0, MSG_SIZE);
        if(read(client_socket, buf, MSG_SIZE) > 0){
            cout << string(buf) << "\r\n";
        }
    }
}


void Client::run(){
    char msg[MSG_SIZE];
	string aux;

    //Connect to the server on the socket;
    if(connect(client_socket, (struct sockaddr*) &client_addr, (socklen_t) client_addr_len)){
        cerr << "ERROR: Failed to connect to server !\nERRO: Falha ao conectar com servidor\n";
        exit(EXIT_FAILURE);
    }


	this->t_rcv = thread(&Client::response, this);

	// Sending name
	int send_result = send(this->client_socket, msg, strlen(msg) + 1, 0);

    if(send_result == -1){
        cerr <<"Failed to send name\r\nERRO: Falha ao enviar nome\r\n";
        exit(EXIT_FAILURE);
    }

	while(true) {
		memset(msg, 0, MSG_SIZE);
        cout << " >";
		fgets(msg, MSG_SIZE, stdin);

        aux = this->getUsername() + ": " + string(msg);
        send_result = send(this->getClientSocket(), aux.c_str(), aux.size() + 1, 0);
        if(send_result == -1){
            cerr <<"Failed to send message\r\nERRO: Falha ao enviar mensagem\r\n";
            continue;
        }
	}
}

void Client::setClientSocket(int c_sock){
    this->client_socket = c_sock;
}

void Client::setPort(int s_port){
    this->port = s_port;
}

void Client::setUsername(string name){
    this->username = name;
}

void Client::setIP(string ip){
    this->ip_address = ip;
}

int Client::getClientSocket(){
    return this->client_socket;
}
int Client::getPort(){
    return this->port;
}

string Client::getUsername(){
    return this->username;
}

string Client::getIP(){
    return this->ip_address;
}
