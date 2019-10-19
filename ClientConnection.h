//
// Created by Devin Gendron on 2019-10-18.
//

#ifndef CS463_CLIENTCONNECTION_H
#define CS463_CLIENTCONNECTION_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>

class ClientConnection {
private:
    int ip = 0;
    int port = 0;
protected:
public:
    int socketFD, portNumber, currentState, connectionState;
    struct addrinfo hints;
    struct addrinfo *clientToServer;

    ClientConnection();
    ~ClientConnection();

    int setupConnectionSocket();
    void sendToServer();
    void receiveFromServer();
};


#endif //CS463_CLIENTCONNECTION_H
