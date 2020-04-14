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

class Monitor{

    private:
        string datapath;

    public:
        Monitor();
        Monitor(string datapath);
        mutex mutex_monitor;
        fstream file;


        // SET
        void setPath(string datapath);

        // GET
        string getPath();

        //Other Methods
        void MonitorWrite(string data);
        void MonitorDisplay();

};


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

    this->setPath(string("logs/"+datetime + " - " + datapath));

}

void Monitor::MonitorWrite(string data){

    mutex_monitor.lock();
    
    this->file.open(this->datapath, ios::app);
	
    time_t tempo = time(NULL);
    char * hour = ctime(&tempo);
    int endStr = strlen(hour) - 1;
    hour[endStr] = '\0';
    string datetime(hour);
    this->file << datetime << ": " << data << "\n";
	
    this->file.close();
    
    mutex_monitor.unlock();

}

void Monitor::MonitorDisplay(){
    string line;
    this->file.open(this->getPath(), ios::in);

    while(getline(this->file,line))
        cout << line << '\n';
}

void Monitor::setPath(string path){
    this->datapath = path;
}

string Monitor::getPath(){
    return this->datapath;
}