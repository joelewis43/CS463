//
// Created by Devin Gendron on 2019-10-18.
//

#include "ClientConnection.h"

ClientConnection::ClientConnection()
{

}

ClientConnection::~ClientConnection()
{

}

int ClientConnection::setupConnectionSocket()
{
    memset((char*)&hints, '\0', sizeof(hints));     // Clear out the address struct
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Setup Addr
    //currentState = getaddrinfo(ip, port, &hints, &clientToServer);
    if (currentState != 0) {
        fprintf(stderr, "Error Msg: %s\n", gai_strerror(currentState));
        exit(EXIT_FAILURE);
    }

    // Setup Socket
    socketFD = socket(clientToServer->ai_family, clientToServer->ai_socktype, clientToServer->ai_protocol);
    if(socketFD < 0)
    {
        printf("Errors Setting up Socket...\n");
        return 0;
    }

    // Connect
    connectionState = connect(socketFD, clientToServer->ai_addr, clientToServer->ai_addrlen);
    if (connectionState != 0) {
        fprintf(stderr, "connectionState: %s\n", gai_strerror(currentState));
        exit(EXIT_FAILURE);
    }
    if(connectionState < 0)
    {
        printf("Errors Setting up Connection...\n");
        gai_strerror(connectionState);
        return 0;
    }
}

void ClientConnection::sendToServer()
{
    //std::string message;
    // Send message to server
    //int charsWritten = send(socketFD, message, message.size(), 0); // Write to the server
    //if (charsWritten < 0) printf("CLIENT: ERROR writing to socket.\n");

    // Check that Data is fully sent
    int checkSend = -5;  // Bytes remaining in send buffer
    do {
        ioctl(socketFD, TIOCOUTQ, &checkSend);  // Check the send buffer for this socket
    } while (checkSend > 0);  // Loop forever until send buffer for this socket is empty
}

void ClientConnection::receiveFromServer()
{
    char buffer[501];    // 501

    // Get return message from server
    memset(buffer, '\0', sizeof(buffer));                       // Clear out the buffer again for reuse
    int charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);  // Read data from the socket, leaving \0 at end
    if (charsRead < 0)                                          // Error check on characters read
        printf("CLIENT: ERROR reading from socket.\n");
}