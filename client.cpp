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

int runClient(char* ip_address, int port) {
    while (true) {      /* client was instructed to loop infinitely */
        int sock  = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("error creating socket");
            exit(-1);
        }
        /* creating the struct for the address */
        struct sockaddr_in client_sin;      /* struct for the address */
        memset(&client_sin, 0, sizeof (client_sin)); /* It copies a single character for a specified number
        * of times to an object (sin)*/
        client_sin.sin_family = AF_INET;    /* address protocol type */
        client_sin.sin_addr.s_addr = inet_addr(ip_address);    /* ip address of client */
        client_sin.sin_port = htons(port);   /* address port */
        if (connect (sock, (struct sockaddr *) &client_sin, sizeof(client_sin)) < 0 ) {
            perror("error connecting to server");
            exit (-1);
        }
        /* creating message for server from the user */
        char data[] = "im a message";
        // sending the message to the server

        int data_len = strlen(data);
        int sent_bytes = send(sock, data, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending the message");
            // exit (-1)
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
        } else if (read_bytes < 0) {
            perror("error has occurred");
        } else {
            // printing the message from server. buffer variable holds it
            // cout << buffer << endl;
        }
        // if message/data is -1 -> close the socket
    }

}

int main (int argc, char *argv[]) {
    // should extract ip from arvg, and perform input checks on it

    // should extract port from argv, and perform input checks on it

    const char* ip = argv[1];
    int port = atoi(argv[2]);

}