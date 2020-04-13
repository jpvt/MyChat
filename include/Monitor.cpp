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

#include "Monitor.h"


Monitor::Monitor(){
    Monitor("log.txt");
}

Monitor::Monitor(string datapath){
    time_t tempo = time(NULL);
    char * hour = ctime(&tempo);
    int endStr = strlen(hour) - 1;
    int i = 0;
    
    hour[endStr] = '\0';
    while(hour[i] != '\0'){

        if(hour[i] == ' ')
            hour[i] = '-';

        i++;
    }

    string datetime(hour);

    this->setPath(string(datetime + " - " + datapath));

}

void Monitor::MonitorWrite(string data){

    mutex_monitor.lock();
    
    this->getFile().open(this->datapath, ios::app);
	
    time_t tempo = time(NULL);
    char * hour = ctime(&tempo);
    int endStr = strlen(hour) - 1;
    hour[endStr] = '\0';
    string datetime(hour);
    this->getFile() << datetime << ": " << data << "\n";
	
    this->getFile().close();
    
    mutex_monitor.unlock();

}

void Monitor::MonitorDisplay(){
    string line;
    this->getFile().open(this->getPath(), ios::in);

    while(getline(this->getFile(),line))
        cout << line << '\n';
}

void Monitor::setFile(fstream f){
    this->file = f;
}

void Monitor::setPath(string path){
    this->datapath = path;
}

fstream Monitor::getFile(){
    return this->file;
}

string Monitor::getPath(){
    return this->datapath;
}