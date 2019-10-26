#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <netdb.h>

#define MAX_BYTES   65536
#define NUM_CLIENTS 2
#define DEBUG   1


class serverSocket {

    public:

        /**
         * Constructor
         * 
         * @param port - the port the listener socket will be initialized on
         **/
        serverSocket(int port);

        /**
         * Class deconstructor
         * 
         * Closes all open sockets (clients and listener)
         **/
        ~serverSocket();

        /**
         * Sends the message to both clients
         * 
         * @param msg - The string to be sent to both clients
         **/
        void deliver(char *msg);

        /**
         * Reads data from client socket.
         * Does not block in the event of no data in the buffer.
         * 
         * @param buffer - buffer of size MAX_BYTES to read data into
         * @returns - the number of bytes read from the socket
         **/
        size_t receive1(char *buffer);
        size_t receive2(char *buffer);

        /**
         * Closes the respective client's socket
         **/
        void closeClient1();
        void closeClient2();

        /**
         * Listens to socket waiting for two clients to connect.
         * Blocks until both client sockets open.
         * Initializes client sockets in non-blocking mode
         **/
        void waitForClients();

    private:

        char *ip;
        int port;
        int addrlen;
        int listener;
        int clients[NUM_CLIENTS] = {0};
        struct sockaddr_in server_address;

        /**
         * Initializes the listener socket and binds it to given port
         **/
        void init();

        /**
         * Reads data from specified socket
         * 
         * @param buffer - the buffer to store the response
         * @param id - the client id to read (0 or 1)
        **/
        size_t receive(char buffer[MAX_BYTES], int id);

        /**
         * Prints the given message upon error and exits with exitCode
         * 
         * @param msg - the message to print out
         * @param exitCode - the exit code to issue upon exit
         **/
        void error(char const *msg, int exitCode);

};

#endif