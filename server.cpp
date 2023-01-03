
#include "server.h"

/**
 * constructor for the TCP server.
 * @param port - int between 1024-65535
 * @param file_reader - readFromFile object created from path to csv provided by user.
 * It holds information about csv file, we will later use for KNN implementation.
 */
TCPServer::TCPServer(int port, readFromFile& file_reader) : reader(file_reader) {
    this->port = port;
}

/**
 * function creates and runs a server, according to its initialized port. It first creates a socket, binds it,
 * and than endlessly listens to input from clients.
 * If the message from client is valid, the server will classify it using the KNN algorithm
 * and return to the client the string classification, according to the CSV file.
 * @param port - port of the server.
 * @param reader - readFromFile object that holds the data from input csv.
 * @return
 */
int TCPServer::runServer(){
    
    const int server_port = this->port;
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
            memset(messageBuffer,0,sizeof(messageBuffer));
            int expected_data_len = sizeof (messageBuffer); /* maximum length of received data */

            // receive the message from the clients socket into 'messageBuffer'
            int read_bytes = recv(client_sock, messageBuffer, expected_data_len, 0);
            if (read_bytes == 0) {
                perror("Connection is closed");
                break;  // finish working with this client
            } else if (read_bytes < 0) {
                perror("Error had occurred");
                break;  // finish working with this client
            } else {
                messageBuffer[read_bytes] = '\0'; // Null-terminate the message
                string prediction;
                // if message received from client is invalid, return "invalid input" and continue
                if (!checkInputData(messageBuffer)) {
                    prediction = "invalid input";
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
                    /* by now only "numbers vector" is in words object.
                    * for each number in words: */
                    for (string& str : words) {
                        float feature = stof(str);
                        inputVector.push_back(feature);
                    }
                    /* perform input check on k (<= .y_train.size) and inputVector (= reader.featuresPerLine).
                    * This is the only place we can check it! */
                    
                    if (k >= reader.y_train.size()) {
                        prediction = "invalid input";
                    } else if (inputVector.size() != reader.featuresPerLine) {
                        prediction = "invalid input";
                    } else {        /* valid input from user */
                        Knn knn = Knn(k, distanceMatric, reader.X_train, reader.y_train);
                        prediction = knn.predict(inputVector);
                    }

                }
                char* sendMessage = &prediction[0];
                int sizeOfMessage = sizeof(prediction);      /* alternative to .c_str(); */
                /* send the prediction/message back to client. c_str converts string into char* type. */
                int sent_bytes = send(client_sock, prediction.c_str(), sizeOfMessage + 1, 0); /* +1 for null
                * terminated char! */
                //int sent_bytes = send(client_sock, sendMessage, sizeOfMessage + 1, 0);
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
/**
 * main function of server side. Gets args from user, and performs input check on it.
 * Than it initializes TCPServer object, and runs it.
 * @param argc - number of input args.
 * @param argv - char* array of user's input.
 * @return - 0;
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
    TCPServer server = TCPServer(stoi(port), reader);
    server.runServer();
    return 0;
}
