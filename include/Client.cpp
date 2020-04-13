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

#include "Client.h"

Client::Client(int c_sock, string username, string ip_address){
   setClientSocket(c_sock);
   setUsername(username);
   setIP(ip_address);
}

Client::Client(){
   setClientSocket(-1);
   setUsername("None");
   setIP("None");
}

void Client::setClientSocket(int c_sock){
    this->client_socket = c_sock;
}

void Client::setUsername(string name){
    this->username = name;
}

void Client::setIP(string ip){
    this->ip_address = ip;
}

int Client::getClientSocket(){
    return this->client_socket
}

string Client::getUsername(){
    return this->username
}

string Client::getIP(){
    return this->ip_address
}

