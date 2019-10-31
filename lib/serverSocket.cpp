#include "../headers/serverSocket.h"

serverSocket::serverSocket(int port) {
    this->port = port;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    addrlen = sizeof(server_address);

    init();
}

serverSocket::~serverSocket() {
    closeClient1();
    closeClient2();
    close(listener);
}

void serverSocket::closeClient1() {
    close(clients[0]);
    clients[0] = 0;
}

void serverSocket::closeClient2() {
    close(clients[1]);
    clients[1] = 0;
}

void serverSocket::waitForClients() {

    if (DEBUG)
        std::cout << "Waiting for Clients to connect!\n";

    for (int i=0; i<NUM_CLIENTS; i++) {

        // skip active clients
        if (clients[i] != 0) {
            if (DEBUG)
                std::cout << "Client-" << i+1 << " connection already established\n";
            continue;
        }

        // block until someone connects
        if (listen(listener, 2) < 0) {
            error("Listening error", 1);
        }

        // accept the new client
        if ((clients[i] = accept(listener, (struct sockaddr *)&server_address, (socklen_t*)&addrlen)) < 0) {
            error("Failed to accept connection", 1);
        }

        // Test if the socket is in non-blocking mode:
        if(fcntl(clients[i], F_GETFL) & O_NONBLOCK) {
            // socket is non-blocking
        }
        else {
            // Put the socket in non-blocking mode:
            if(fcntl(clients[i], F_SETFL, fcntl(clients[i], F_GETFL) | O_NONBLOCK) < 0) {
                error("Failed to set socket as non-blocking", 1);
            }
        }

        if (DEBUG)
            std::cout << "Client-" << i+1 << " connection established!\n";

    }

}

void serverSocket::init() {

    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Listener failed to initialize.", 1);
    }

    if (bind(listener, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        error("Listener failed to bind", 1);
    }

}

bool serverSocket::getConnection() {

    if (clients[0] == 0 || clients[1] == 0)
        return 0;

    return 1;

}

void serverSocket::error(char const *msg, int exitCode) {
    std::cout << msg << std::endl;
    exit(exitCode);
}

void serverSocket::deliver(char *msg) {

    send(clients[0], msg, strlen(msg), 0);
    send(clients[1], msg, strlen(msg), 0);

}

size_t serverSocket::receive1(char b[MAX_BYTES]) {
    return receive(b, 0);
}

size_t serverSocket::receive2(char b[MAX_BYTES]) {
    return receive(b, 1);
}

size_t serverSocket::receive(char buffer[MAX_BYTES], int clientID) {
    
    char temp[MAX_BYTES];
    int total = 0, current = 0;
    int i=0;

    do {
        // read from the socket
        current = recv(clients[clientID], temp, sizeof temp, 0);
        
        if (current > 0) { 

            // add the new bytes to total
            total += current;

            // append the temp string to buffer
            for (int x=0; x < strlen(temp); x++) {
                buffer[i] = temp[x];
                i++;
                // SHOULD REALLY CHECK IF i IS APPROACHING MAX_BYTES
            }
        }
    } while(current > 0);

    if (total < 0)
        return 0;

    return total;
}