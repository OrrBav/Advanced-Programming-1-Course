#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMAND_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMAND_H

#include <string>
#include "io.h"
#include "readFromFile.h"
using namespace std;

/**
 * this struct will be the "shared state" between commands belonging to the same CLI.
 * some values are initialized to default values as instructed.
 * readFromFile is initialized using default constructor.
 */
struct CommandData {
    readFromFile reader_classified;
    readFromFile readFromFile_unclassified;
    int k = 5;
    string distanceMetric = "AUC";
    bool isUploaded = false;
    bool isClassified = false;
};

class Command {
protected:
    DefaultIO *dio;

public:
    string description;
    CommandData commandData;
    Command(string description, DefaultIO *dio) : dio(dio) {
        this->description = description;
    }
        // c++ initializes members of object with ": dio(dio)" syntax.
    // abstract functions
    virtual void execute() = 0;
    // destructor
    virtual ~Command(){};
};

// TODO: add shared state: struct that shares information between commands

class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO *dio, CommandData &new_commandData) : Command("1. upload an unclassified csv data file\n", dio) {
        this->commandData = new_commandData;
    }
    void execute() override {
        // TODO
        this->dio->write("UPLOAD");
    }
    ~UploadCommand() override {};
};

class AlgorithmSettingsCommand : public Command {
public:
    AlgorithmSettingsCommand(DefaultIO *dio) : Command("algorithm settings", dio) {}
    void execute() {
        //TODO
        this->dio->write("ALGORITHM SETTINGS");
    }
    ~AlgorithmSettingsCommand() {};
};


// TODO:
// add the 3 other menu options
// ...
#endif