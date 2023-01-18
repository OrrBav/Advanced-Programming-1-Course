
#include "client.h"
#include "io.h"
#include <stdio.h>

using namespace std;

// return true if should wait for user input
bool handleServerInput(SocketIO sio, string serverInput) {
    if (serverInput == "CLIENT_CMD_UPLOAD") {
        cout << "Please upload your local train CSV file." << endl;
        string trainFilePath;
        getline(cin, trainFilePath);
        // finish early if an error occurred during upload OR during file parsing
        if (!uploadFileLine(&sio, trainFilePath) || sio.read() == "CLIENT_CMD_ABORT") {
            cout << "invalid input" << endl;
            return false;
        }
        cout << "Upload complete." << endl;

        cout << "Please upload your local test CSV file." << endl;
        string testFilePath;
        getline(cin, testFilePath);
        if (!uploadFileLine(&sio, testFilePath) || sio.read() == "CLIENT_CMD_ABORT") {
            cout << "invalid input" << endl;
            return false;
        }
        cout << "Upload complete." << endl;

        return false;
    } else if (serverInput == "CLIENT_CMD_RESULTS") {
        string result;
        do {
            result = sio.read();
            cout << result << endl;
        } while (result != "Done.");
        return false;
    } else if (serverInput == "CLIENT_CMD_DOWNLOAD") {
        cout << "Please enter path to the new file:" << endl;
        string path;
        getline(cin, path);
        downloadFile(sio, path);
        return false;
    } else if (serverInput == "CLIENT_CMD_ABORT") {
        return false;
    } else {
        cout << serverInput << endl;
    }
    return true;
}

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

    SocketIO sio(sock);
    /* client runs in a loop infinitely until stopped */
    while (true) {
        string serverInput = sio.read();
        // if sio returns "" it means read_bytes <= 0
        if (serverInput == "") {
            cout << "connection is closed" << endl;
            break;
        }

        if (handleServerInput(sio, serverInput)) {
            string data;
            getline(cin, data);
            sio.write(data);
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
