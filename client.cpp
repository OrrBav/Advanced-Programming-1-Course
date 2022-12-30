
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include "readFromFile.h"

using namespace std;

bool checkPort (char *port, string portNum) {
    int temp;
        if (isPositiveInteger(port)) {
            temp = stoi(portNum);
            if (1024 < temp < 65535) {
                return true;
            }
        }
        else {
           return false;
        }
}

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

        // get data input ("vector distance k") from the user
        string data;
        getline(cin, data);

        // check the data is valid. data = "vector distance k"
        // "vector distance k" splits to "vector", 'distance" ,"k"
        // example : "4 5.6 4.2 1 MAN 3" --> (4, 5.6, 4.2, 1) , "MAN", 3

        // parse input data into vector, distance metric, k
        // receives a pointer to the beginning of the data string and checks char after char

        bool parseInputData(char *str) {
            // check data is not empty
            if (*str == '\0')
                return false;
            if (*str == '0')
                return false;
            string inputVector;

            // check char after char in the given string
            while (*str != '\0') {
                // concatenating the current char (number, space or a dot) to the vector
                if (isdigit(*str) || (*str == " " || ".")) {
                    inputVector = inputVector + *str;
                }
                str++;
            }
            // .... TODO: fix
            return true;
        }


        // check input vector


        // check input distance metric
        string inputDistance;
        if (inputDistance != "AUC" && inputDistance != "MAN" && inputDistance == "CHB" &&
            inputDistance != "CAN" && inputDistance != "MIN" ) {
            cout << "received invalid distance metric (should be AUC/MAN/CHB/CAN/MIN)" << endl;
            exit(-1);
        }

        // check input k
        string inputK;
        int k;
        if (isPositiveInteger(inputK)) {
        k = stoi(inputK);
        }
        else {
            cout << "received invalid value for k: " << inputK << " (should be a positive integer)" << endl;
            exit(-1);
        }


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


        //char data[] = "im a message";
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
    char* ip = argv[1];     /* should be const? */
    string check_ip = ip;
    if (!checkIP(check_ip)) {
        cout << "invalid ip address.";
        exit(-1);
    }

    // check input port is valid
    string p = argv[2];
    if (!checkPort(argv[2],p)) {
        cout << "invalid port address" << endl;
        exit(-1);
    }

    runClient(ip, stoi(p));
}
/* following code is for input check. Should be further implemented.
string message = "1 2 3 4 MAN 302";
string messages[3];
string distance;
string k;
string user = "";
for (int i = 0; i < message.size(); i++) {
    if (isalpha(message[i])) {
        messages[0] = user;
        for (int j = i; j <= i + 2; j++) {
            distance = distance + message[j];
            }
        messages[1] = distance;
        for (int l = i + 4; l < message.size(); l++) {
            k = k + message[l];
        }
        messages[2] = k;
        break;
        }
    else {
        user = user + message[i];
    }
}
 */
