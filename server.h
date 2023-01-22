
#ifndef ADVANCED_PROGRAMMING_1_EX3_SERVER_H
#define ADVANCED_PROGRAMMING_1_EX3_SERVER_H

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
#include "function.h"
#include <thread>
#include "io.h"
#include "command.h"
#include "CLI.h"
using namespace std;

class TCPServer {
    int port;
public:
    TCPServer(int port);
    int runServer();
};

#endif //ADVANCED_PROGRAMMING_1_EX3_SERVER_H
