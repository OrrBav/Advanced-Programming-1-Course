//
// Created by orrbb on 24/12/2022.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int runServer(int port, string csv){
    const int server_port = port;
    /*socket creation, sock_stream is a const for TCP */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(-1);
    }
    /* creating the struct for the address */
    struct sockaddr_in server_sin;     /* struct for the address */
    memset(&server_sin, 0, sizeof (server_sin));  /* It copies a single character for a specified number
    * of times to an object (sin)*/
    server_sin.sin_family = AF_INET;   /* address protocol type */
    server_sin.sin_addr.s_addr = INADDR_ANY; /* const for any address */
    server_sin.sin_port = htons(server_port); /* defines the port */
    /* binding the socket to the port and ip_address, while checking it can be done */
    if (bind(sock, (struct sockaddr *) &server_sin, sizeof (server_sin)) < 0) {
        perror("Error binding socket");
        exit(-1);
    }
    /* listens up to 5 clients at a time */
    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket");
        exit(-1);
    }
    while (true) {      /* we were instructed not to close the server. */
        struct sockaddr_in client_sin; /* address struct for the sender info */
        unsigned int addr_len = sizeof (client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len); /* accept creates a nre socket
        * for the connecting client */
        if (client_sock < 0) {
            perror("Error accepting client");
            exit(-1);
        }
        char messageBuffer[4096]; /* creates a buffer for the client */
        int expected_data_len = sizeof (messageBuffer); /* maximum length of received data */
        int read_bytes = recv(client_sock, messageBuffer, expected_data_len, 0); /* recieve a message from the clients
        * socket into the buffer. */
        if (read_bytes == 0) {
            perror("Connection is closes");
        } else if (read_bytes < 0) {
            perror("Error");
        } else {
            /* if message is -1 we should close client */
            /* if message is invalid, return "invalid input" and continue */

            // classify vector according to file

            //send it back to client.

        }
    }

    /* closes the server socket */
    close(sock);
    return 0;
}

int main (int argc, char *argv[]) {
    // should extract csv from arvg, and perform input checks on it

    // should extract port from argv, and perform input checks on it

    string cvs = argv[1];
    int port = atoi(argv[2]);

}