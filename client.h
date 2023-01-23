

#ifndef ADVANCED_PROGRAMMING_1_EX3_CLIENT_H
#define ADVANCED_PROGRAMMING_1_EX3_CLIENT_H
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
#include "io.h"
using namespace std;

class TCPClient {
    int port;
    char* ip;
    bool handleServerInput(SocketIO sio, string serverInput);
public:
    TCPClient(char* ip, int port);
    void runClient();

};

#endif //ADVANCED_PROGRAMMING_1_EX3_CLIENT_H
