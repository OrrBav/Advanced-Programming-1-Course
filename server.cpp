
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

/**
 * function is responsible to handle the flow of Menu with the client, by creating a CLI object that will
 * loop, sending and receiving information from client, using CLI's start function. When user decide to end
 * program, client will send a message back to server that will end the loop in CLI::start function, where handleClient
 * function will delete its recourses and terminate.
 * @param client_sock - the sock that connects to client. Used to create SocketIO object.
 * @param port - the port that connect the server and the client.
 */
static void handleClient(int client_sock, int port) {
    SocketIO *sio = new SocketIO(client_sock);
    CLI *cli = new CLI(sio, client_sock, port);
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
    int sock = listenToPort(this->port);
    // the server remains open (even when client side closes)
    while (true) {
        int client_sock = acceptClient(sock);
        thread client_thread(handleClient, client_sock, this->port);
        // Detach the thread so that it can run independently
        client_thread.detach();
    }
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
