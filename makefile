CC = g++
EXECUTABLE = tcp_server tcp_client

all: tcp_server tcp_client client monitor

tcp_server: src/tcp_server.cpp
	g++ -o tcp_server src/tcp_server.cpp -pthread -std=c++11 -g

tcp_client: src/tcp_client.cpp
	g++ -o tcp_client src/tcp_client.cpp -pthread -std=c++11 -g

clean:
	@echo "\033[31mCleaning obj directory... \033[0m"
	@rm $(EXECUTABLE) -f