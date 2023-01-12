#ifndef ADVANCED_PROGRAMMING_1_EX3_IO_H
#define ADVANCED_PROGRAMMING_1_EX3_IO_H

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

class DefaultIO {
public:
    // =0 enforces the child classes to override this function with their own implementation
    virtual string read() = 0;
    virtual void write(string input) = 0;
};

class StandardIO : public DefaultIO {
public:
    string read() {
        string input;
        getline(cin, input);
        return input;
    };

    void write(string input) {
        cout << input << endl;
    }
};

class SocketIO : public DefaultIO {
    int sock;
public:
    SocketIO(int sock) { this->sock = sock; }
    
    string read() {
        char messageBuffer[4096]; // creates a buffer to receive the message from the client
        memset(messageBuffer,0,sizeof(messageBuffer));
        int expected_data_len = sizeof (messageBuffer); /* maximum length of received data */

        // receive the message from the clients socket into 'messageBuffer'
        int read_bytes = recv(sock, messageBuffer, expected_data_len, 0);
        if (read_bytes <= 0) {
            return "";
        } 

        return messageBuffer;
    };

    void write(string input) {
        int sizeOfMessage = input.size();
        int sent_bytes = send(sock, input.c_str(), sizeOfMessage + 1, 0); 
    };
};

#endif