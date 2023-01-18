//
// Created by orrbb on 15/01/2023.
//

#ifndef ADVANCED_PROGRAMMING_1_EX4_CLI_H
#define ADVANCED_PROGRAMMING_1_EX4_CLI_H

#include <vector>
#include "io.h"
#include "command.h"
#include "function.h"

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
    CommandData commandData;
    // TODO: add shared state?
public:
CLI(DefaultIO* dio);
void start();
void printMenu();
virtual ~CLI();
};


#endif //ADVANCED_PROGRAMMING_1_EX4_CLI_H
