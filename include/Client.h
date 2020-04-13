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

#include "Client.cpp"

using namespace std;

class Client{

    private:
        int client_socket;
        string username, ip_address;

    public:
        //Constructor
        Client();
        Client(int c_sock, string username, string ip_address);

        // GET
        int getClientSocket();
        string getUsername();
        string getIP();

        // SET
        void setClientSocket(int c_sock);
        void setUsername(string username);
        void setIP(string ip);


};