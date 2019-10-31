#include "../headers/clientSocket.h"

clientSocket::clientSocket(char const *ip, int port) {
    this->ip = ip;
    this->port = port;

    std::cout << this->ip << ":" << this->port << std::endl;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    addrlen = sizeof(server_address);

    init();
}

clientSocket::~clientSocket() {
    connected = 0;      // should also be set in a standalone close function
                        // to support the case where a user disconnects from
                        // from the server but still has the client open
    close(sock);
}

void clientSocket::deliver(const char *msg) {
    std::cout << "Msg size: " << strlen(msg) << std::endl;
    send(sock, msg, strlen(msg), 0);
}

size_t clientSocket::receive(char buffer[MAX_BYTES]) {

    char temp[MAX_BYTES];
    int total = 0, current = 0;
    int i=0;

    do {
        // read from the socket
        current = recv(sock, temp, sizeof temp, 0);
        
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

void clientSocket::init() {

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Client failed to initialize.", 1);
    }

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ip, &server_address.sin_addr)<=0)
    { 
        error("Invalid address/ Address not supported", 1);
    } 

    // connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, addrlen) < 0) {
        error("Failed to connect to server", 1);
    }

    // Test if the socket is in non-blocking mode:
    if(fcntl(sock, F_GETFL) & O_NONBLOCK) {
        // socket is non-blocking
    }
    else {
        // Put the socket in non-blocking mode:
        if(fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK) < 0) {
            error("Failed to set socket as non-blocking", 1);
        }
    }

    connected = 1;

}

void clientSocket::error(char const *msg, int exitCode) {
    std::cout << msg << std::endl;
    exit(exitCode);
}

bool clientSocket::getConnection() {
    return connected;
}