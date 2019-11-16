#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <netdb.h>

#define MAX_BYTES   65536


class clientSocket {

    public:

        /**
         * Constructor
         * 
         * @param ip - the ip address to connect to
         * @param port - the port to connect to
         **/
        clientSocket(char const *ip, int port);

        /**
         * Class deconstructor
         * 
         * Closes the socket
         **/
        ~clientSocket();

        /**
         * Sends the message to both clients
         * 
         * @param msg - The string to be sent to the server
         **/
        void deliver(const char *msg);

        /**
         * Reads data from the server.
         * Does not block in the event of no data in the buffer.
         * 
         * @param buffer - buffer of size MAX_BYTES to read data into
         * @returns - the number of bytes read from the socket
         **/
        size_t receive(char buffer[MAX_BYTES]);

        /**
         * Reads data from the server.
         * Blocks data until the expected data has been received
         * 
         * @param buffer - buffer of size MAX_BYTES to read data into
         * @returns - the number of bytes read from the socket
         **/
        size_t receive(char *buffer, int size);

        /**
         * Reads data from the server.
         * Blocks until data is read and the buffer is empty again
         * 
         * @param buffer - buffer of size MAX_BYTES to read data into
         * @returns - the number of bytes read from the socket
         **/
        size_t receiveBlock(char buffer[MAX_BYTES]);

        bool getConnection();

        void clearBuffer();

    private:

        int port;
        int sock;
        int addrlen;
        char const *ip;
        bool connected;
        struct sockaddr_in server_address;

        /**
         * Initializes the socket in non-blocking mode and connects it to the server
         **/
        void init();

        /**
         * Prints the given message upon error and exits with exitCode
         * 
         * @param msg - the message to print out
         * @param exitCode - the exit code to issue upon exit
         **/
        void error(char const *msg, int exitCode);

};

#endif