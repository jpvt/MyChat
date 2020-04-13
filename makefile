all: server

server: src/server.cpp
	g++ -o server src/server.cpp -pthread -std=c++11
