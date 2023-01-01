
#include "client.h"

using namespace std;

/**
 * constructor for a TCP Client. both args provided by user.
 * @param ip - ip address of server.
 * @param port - port of the server.
 */
TCPClient::TCPClient(char *ip, int port) {
    this->ip = ip;
    this->port = port;
}

/**
 * this function will run client side of TCP communication, using the ip and port provided by user.
 * It will create a connection and will send user's input, until input is -1, than it will close itself.
 * @param ip_address - ip address of the servet we want to connect.
 * @param port - the port of the server.
 */
void TCPClient::runClient() {
    int sock  = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(-1);
    }

    /* creating the struct for the address */
    struct sockaddr_in client_sin;      /* struct for the address */
    memset(&client_sin, 0, sizeof (client_sin)); /* Resets object: It copies a single character for a specified number
    * of times to an object (sin)*/
    client_sin.sin_family = AF_INET;    /* address protocol type */
    client_sin.sin_addr.s_addr = inet_addr(this->ip);    /* ip address of client */
    client_sin.sin_port = htons(this->port);   /* address port */
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
            cout << "invalid input" << endl;
            continue;
        }

        int data_len = data.size();
        // sending the user message to the server
        // c_str() converts 'data' from string to *char, because 'send' function needs *char
        int sent_bytes = send(sock, data.c_str(), data_len, 0);
        if (sent_bytes < 0) {
            /* if we couldn't send the message, an error has occurred. We should try again. */
            perror("error sending the message");
            continue;
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
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

/**
 * main function of client side. Gets args from user, and performs input check on it.
 * Than it initializes TCPClient object, and runs it.
 * @param argc - number of input args.
 * @param argv - char* array of user's input.
 * @return
 */
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
    TCPClient client = TCPClient(ip, stoi(port));
    client.runClient();
    return 0;
}
