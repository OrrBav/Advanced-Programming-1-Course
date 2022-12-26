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
#include <string>
#include <vector>

using namespace std;

bool checkIP(string str_ip) {
    char single_cut;
    string new_num;
    int dot_count = 0;
    vector <int> ipNumbers;
    for (int i = 0; i < str_ip.length(); i++) {
        if (isdigit(str_ip[i])) {
            /* converts input_srt[i] from char to string, and enables stoi check */
            single_cut = str_ip[i];
            string string_cut{ single_cut };
            new_num += string_cut;
        }
            /* char is not a digit: can only be a dot. */
        else {
            if (str_ip[i] == '.') {
                dot_count++;
                /* more than 3 digits are invalid ip address. */
                if (new_num.length() > 3) {
                    return false;
                }
                ipNumbers.push_back(stoi(new_num));
                new_num = "";
            }
                /* invalid char: not a digit or a dot. */
            else {
                return false;
            }
        }
    }
    /* we check new_num length again for the last octate in the ip address. */
    if (dot_count != 3 || new_num.length() > 3) {
        return false;
    }
    ipNumbers.push_back(stoi(new_num));
    for (int i = 0; i < ipNumbers.size(); i++) {
        if (ipNumbers[i] < 0 || ipNumbers[i] > 255) {
            return false;
        }
    }
    return true;
}

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
        /* creating message for server from the user.
         * should perform input checks on it: vector, distanceMat, k*
         * if invalid, print "invalid input" and continue */


        char data[] = "im a message";
        // sending the message to the server

        int data_len = strlen(data);
        /* should ensure data_len < buffer> */
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
    /* maybe const ARGC like in main.cpp */
    if (argc != 3) {
        cout << "Should have received " << 3 << " arguments, but received " << argc << " instead" << endl;
        exit(-1);
    }
    /* extract ip from arvg, and perform input checks on it. */
    const char* ip = argv[1];
    string check_ip = ip;
    if (!checkIP(check_ip)) {
        cout << "invalid ip address.";
        exit(-1);
    }
    // should extract port from argv, and perform input checks on it



    int port = atoi(argv[2]);

}