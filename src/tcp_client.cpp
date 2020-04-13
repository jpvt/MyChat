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

    //Create a socket;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		cerr << "ERROR: Can't Create Socket\nERRO: Não conseguiu criar socket\n";
		return -1;
	}

    //Create a Server Address Structure for the server we're connecting with;
    sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    inet_pton(AF_INET, client_ip.c_str(), &client_addr.sin_addr);

    //Connect to the server on the socket;
    int connect_result = connect(sock, (sockaddr *)&client_addr, sizeof(client_addr));

    if(connect_result == -1){
        cerr << "ERROR: Failed to connect to server !\nERRO: Falha ao conectar com servidor\n";
        return -2;
    }

    //While loop:
    char buf[BUFFER_SIZE];
    string msg;
    do{
        //Enter lines of text;
        cout <<"> ";
        getline(cin, msg);

        //Send to server;
        int send_result = send(sock, msg.c_str(), msg.size() + 1, 0);
        if(send_result == -1){
            cerr <<"Failed to send message\r\nERRO: Falha ao enviar mensagem\r\n";
            continue;
        }

        //Wait for response;
        memset(buf,0, BUFFER_SIZE);
        int bytes_received = recv(sock, buf, BUFFER_SIZE, 0);
        if(bytes_received == -1){
            cout << "ERROR: Error while getting response from server \r\nERRO: Erro ao receber resposta de servidor\r\n";
        }else{
            //Display response;
            cout << "SERVER> " <<string(buf, bytes_received) << "\r\n";
        }
    }while(true);

    //Close the socket;
    close(sock);

    return 0;
}
