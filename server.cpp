
#include "server.h"


/**
 * constructor for the TCP server.
 * @param port - int between 1024-65535
 * @param file_reader - readFromFile object created from path to csv provided by user.
 * It holds information about csv file, we will later use for KNN implementation.
 */
TCPServer::TCPServer(int port){
    this->port = port;
}

static void handleClient(int client_sock) {
    SocketIO *sio = new SocketIO(client_sock);
    CLI *cli = new CLI(sio);
    cli->start();
    // if previous line is executed, client pressed 8 and connection should be closed.
    if (close(client_sock) < 0) {
        perror("Error closing socket");
    }
    delete sio;
    delete cli;
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
    // was <thread*>
    //vector<thread> open_threads;
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
        thread client_thread(handleClient, client_sock);
        // Detach the thread so that it can run independently
        client_thread.detach();
//        // creates a thread for client, and detaches it for multiple connections simultaneously.
//        open_threads.emplace_back(handleClient, client_sock);
//        open_threads.back().detach();
//        thread *t = new thread(handleClient, client_sock);
//        open_threads.push_back(t);
    }

//    // iterates through all open threads and delete them from heap
//    for (auto iter = open_threads.begin(); iter != open_threads.end(); iter++) {
//        thread *t = *iter;
//        // join makes sure the thread is done running and only then allow to delete it
//        t->join();  //(*t).join
//        delete t;
//    }
    // closes the server socket
    close(sock);
    return 0;
}


/**
 * main function of server side. Gets args from user, and performs input check on it.
 * Than it initializes TCPServer object, and runs it.
 * @param argc - number of input args.
 * @param argv - char* array of user's input.
 * @return - 0;
 */
int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Should have received " << 2 << " arguments, but received " << argc << " instead" << endl;
        exit(-1);
    }

    // check input port is valid
    string port = argv[1];
    if (!checkPort(port)) {
        cout << "invalid port address" << endl;
        exit(-1);
    }
    TCPServer server = TCPServer(stoi(port));
    server.runServer();
    return 0;
}
