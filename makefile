CC = g++

all: tcp_server tcp_client client monitor

tcp_server: src/tcp_server.cpp
	g++ -o tcp_server src/tcp_server.cpp -pthread -std=c++11

tcp_client: src/tcp_client.cpp
	g++ -o tcp_client src/tcp_client.cpp -pthread -std=c++11

monitor: src/monitor.cpp
	g++ -o monitor src/monitor.cpp -pthread -std=c++11

client: src/client.cpp
	g++ -o client src/client.cpp -pthread -std=c++11