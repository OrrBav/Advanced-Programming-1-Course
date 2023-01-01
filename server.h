//
// Created by orrbb on 01/01/2023.
//

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
# include "function.h"

using namespace std;

class TCPServer {
    int port;
    readFromFile reader;
public:
    TCPServer(int port, readFromFile& file_reader);
    int runServer();
};

#endif //ADVANCED_PROGRAMMING_1_EX3_SERVER_H
