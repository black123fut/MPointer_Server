#ifndef MPOINTER_SERVER_SERVER_H
#define MPOINTER_SERVER_SERVER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080


class Server {
public:
    Server(int);
    void run();
private:
    int size_heap;
    int contador_direcciones;
    int IDs;

    int server_fd;
    int new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
};


#endif //MPOINTER_SERVER_SERVER_H
