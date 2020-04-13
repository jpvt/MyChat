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

#include "Monitor.cpp"

using namespace std;

class Monitor{

    private:
        fstream file;
        string datapath;

    public:
        mutex mutex_monitor;

        Monitor();
        Monitor(string datapath);


        // SET
        void setFile(fstream file);
        void setPath(string datapath);

        // GET
        fstream getFile();
        string getPath();

        //Other Methods
        void MonitorWrite(string data);
        void MonitorDisplay();

};