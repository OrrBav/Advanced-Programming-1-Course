//
// Created by orrbb on 11/01/2023.
//

#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMANDORR_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMANDORR_H

#include <string>
using namespace std;

class DefualtIO {
    // add members for streams?
public:
    //constuctor
    DefualtIO() {};
    virtual string read() =0;
    virtual void write(string) =0;

};

class StandartIO : public DefualtIO {
public:
    //constructor
    StandartIO() {}

};

/**
 *
 */
class Command {
protected:
    //TODO: add DefaultIO object dio
    DefualtIO* dio;
public:
    // members
    string description;
    // consructor
    Command(DefualtIO* dio):dio(dio) {}
    //functions:
    virtual void execute() =0;
    // destructor
    virtual ~Command(){};
};

class UploadCommand : public Command {
public:
     UploadCommand(DefualtIO* dio) {
        this->description = "1. upload an unclassified csv data file";
     }
     void execute() {
        //TODO
     }
     ~UploadCommand(){};
};

#endif //ADVANCED_PROGRAMMING_1_EX4_COMMANDORR_H
