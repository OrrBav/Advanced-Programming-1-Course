#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMAND_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMAND_H

#include <string>
#include "io.h"

using namespace std;

class Command {
protected:
    DefaultIO *dio;
public:
    const string description;
    Command(string description, DefaultIO *dio) : description(description), dio(dio) { }
        // here we use different constructor style and dont use 'regular' constructor 
        // because const params dont allow '=' assignment 
        // not like this:
        // this->description = description;
        // this->dio = dio;
    virtual void execute() = 0;
};

class UploadCommand : public Command {
public:
    UploadCommand() : Command("upload an unclassified csv data file", new StandardIO()) { }
    void execute() {
        this->dio->write("UPLOAD");
    }
};

class AlgorithmSettingsCommand : public Command {
public:
    AlgorithmSettingsCommand() : Command("algorithm settings", new StandardIO()) {}
    void execute() {
        this->dio->write("ALGORITHM SETTINGS");
    }
};


// TODO:
// add the 3 other menu options
// ...
#endif