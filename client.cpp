
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
#include "function.h"

using namespace std;

// TODO: maybe move it to helperFunctions
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

/**
 * this function will run client side of TCP communication, using the ip and port provided by user.
 * @param ip_address - ip address of the servet we want to connect.
 * @param port - the port of the server.
 */
void runClient(char* ip_address, int port) {
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

    /* client runs in a loop infinitely until stopped */
    while (true) {
        /* get data input ("vector distance k") from the user */
        string data;
        getline(cin, data);

        /* if user input is "-1" we close the client */
        if (data == "-1") {
            break;
        }

        /* perform input checks on user input to make sure the vector, distance metric and k are valid
        * i.e. vector holds numbers separated by spaces, distance metric is one of our options, and k is integer>0
        * if invalid continue to next new input from user */
        if(!checkInputData(data)) {
            cout << "user invalid input: " << data << endl;  // TEST
            cout << "invalid input" << endl;
            continue;
        }

        int data_len = data.size();
        // sending the user message to the server
        /* should ensure data_len < buffer> */
        // c_str() converts 'data' from string to *char, because 'send' function needs *char

        cout << "client send: " << data << endl;  // TEST
//        data += '\0';
//        char * sentdata = &data[0];
        int sent_bytes = send(sock, data.c_str(), data_len, 0);
        if (sent_bytes < 0) {
            /* if we couldn't send the message, an error has occurred. We should try again. */
            perror("error sending the message");
            // exit (-1)
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);

        cout << "client receive: " << buffer << endl;  // TEST

        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
        } else if (read_bytes < 0) {
            perror("error has occurred");
        } else {
            /* printing the message from server. buffer variable holds it. */
            cout << buffer << endl;
        }

    }
    close(sock);
}

int main (int argc, char *argv[]) {
   
    if (argc != 3) {
        cout << "Should have received " << 3 << " arguments, but received " << argc << " instead" << endl;
        exit(-1);
    }
    // extract ip from argv and perform input checks on it
    char* ip = argv[1];     /* should be const? */
    string check_ip = ip;
    if (!checkIP(check_ip)) {
        cout << "invalid ip address.";
        exit(-1);
    }

    // check input port is valid
    string port = argv[2];
    if (!checkPort(port)) {
        cout << "invalid port address" << endl;
        exit(-1);
    }

    runClient(ip, stoi(port));
    return 0;
}
