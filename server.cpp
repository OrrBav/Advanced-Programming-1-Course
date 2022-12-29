
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include "knn.h"
#include "readFromFile.h"
# include "function.h"

using namespace std;


/**
 * function creates and runs a server, according to its initialized port. It first creates a socket, binds it,
 * and than endlessly listens to input from clients.
 * If the message from client is valid, the server will classify it using the KNN algorithm
 * and return to the client the string classification, according to the CSV file.
 * @param port - port of the server.
 * @param reader - readFromFile object that holds the data from input csv.
 * @return
 */
int runServer(int port, readFromFile& reader){
    
    const int server_port = port;
    // socket creation, sock_stream is a const for TCP
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(-1);
    }

    /* creating the struct for the address */
    struct sockaddr_in server_sin;     /* struct for the address */
    memset(&server_sin, 0, sizeof (server_sin));  /* It copies a single character for a specified number
    * of times to an object (sin) */
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
    
    // the server remains open (even when client side closes)
    while (true) {
        struct sockaddr_in client_sin; /* address struct for the sender info */
        unsigned int addr_len = sizeof (client_sin);
        /* accept creates a new client socket for the connecting client */
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("Error accepting client");
            exit(-1);
        }

        // now "work" only with this client 
        while (true) {
            char messageBuffer[4096]; // creates a buffer to receive the message from the client
            int expected_data_len = sizeof (messageBuffer); /* maximum length of received data */

            // receive the message from the clients socket into 'messageBuffer'
            int read_bytes = recv(client_sock, messageBuffer, expected_data_len, 0);
            cout << "server receive: " << messageBuffer << endl;  // TEST
            if (read_bytes == 0) {
                perror("Connection is closed");
                break;  // finish working with this client
            } else if (read_bytes < 0) {
                perror("Error");
                break;  // finish working with this client
            } else {                                
                string sendMessage;
                // if message received from client is invalid, return "invalid input" and continue
                if (!checkInputData(messageBuffer)) {
                    sendMessage = "invalid input";
                }
                else {
                    // split tne received buffer
                    vector<string> words = splitString(messageBuffer, ' ');
                    
                    // extract k, vector and dist
                    int k = stoi(words.back());
                    words.pop_back();
                    string distanceMatric = words.back();
                    words.pop_back();
                    vector<float> inputVector;
                    // by now only "the vector" is in words
                    // for each number in words.....
                    for (string& str : words) {
                        float feature = stof(str);
                        inputVector.push_back(feature);
                    }             

                    string prediction;

                    /* Should perform input check on k (<= .y_train.size) and inputVector (= reader.featuresPerLine).
                    * This is the only place we can check it!*/
                    /* make sure k value is smaller than the number of samples in given file. */
                    
                    if (k >= reader.y_train.size()) {
                        prediction = "invalid input";
                        //exit(-1);
                    } else if (inputVector.size() != reader.featuresPerLine) {
                        prediction = "invalid input";
                        //exit(-1);
                    } else {        /* valid input from user */
                        Knn knn = Knn(k, distanceMatric, reader.X_train, reader.y_train);
                        prediction = knn.predict(inputVector);
                    }

                    // knn returns a string, and send receives a char[]
                    sendMessage = &prediction[0];
                }
                
                int sizeOfMessage = sendMessage.size();
                // send the prediction/message back to client. ( c_str converts string into char* )
                cout << "server send: " << sendMessage << endl;  // TEST
                int sent_bytes = send(client_sock, sendMessage.c_str(), sizeOfMessage, 0);
                if (sent_bytes < 0) {
                    cout << "error sending to client." << endl;
                }
            }
        }
    }

    // closes the server socket
    close(sock);
    return 0;
}

/* extract port number and csv file from argv and perform input checks on them
    */
int main (int argc, char *argv[]) {

    if (argc != 3) {
    cout << "Should have received " << 3 << " arguments, but received " << argc << " instead" << endl;
    exit(-1);
    }

    string filename = argv[1];
    // check input csv file is valid and extract all its data to reader object
    readFromFile reader(filename);
    reader.read();

    // check input port is valid
    string port = argv[2];
    if (!checkPort(port)) {
        cout << "invalid port address" << endl;
        exit(-1);
    }

    runServer(stoi(port),reader);
}
