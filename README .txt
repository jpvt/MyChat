# MyChat
Project dedicated to Concurrent Programming Class.

**Resumo: Esse trabalho consiste na implementação de dois programas em C/C++ para a composição de um serviço de bate-papo remoto, sendo esses um cliente e outro um servidor. A aplicação servidor irá receber conexões de diversos clientes e replicar as mensagens para todos esses. A aplicação cliente se conectará a um servidor e irá receber e enviar mensagens. A implementação utilizará a biblioteca padrão de sockets em C/C++ e também programação concorrente(PThreads).**

**Abstract: This project consists on the implementation of two applications in C/C++ for the composition of a remote chat service, these being client and server. The server application will receive connections from several clients and replicate messages to all of them. The client application will connect to a server and will receive and send messages. The implementation will use the standard C/C++ socket library and PThreads.**


Para compilar basta utilizar o comando: make
Para limpar os objetos use : make clean

Aplicação servidor:
./tcp_server SERVER_PORT SERVER_NAME

Aplicação cliente:
./tcp_client IP PORT USERNAME