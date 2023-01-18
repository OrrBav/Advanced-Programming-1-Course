#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMAND_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMAND_H

#include <string>
#include <iostream>
#include <fstream>
#include "io.h"
#include "readFromFile.h"
#include "function.h"
#include "knn.h"
using namespace std;

/**
 * this struct will be the "shared state" between commands belonging to the same CLI.
 * some values are initialized to default values as instructed.
 * readFromFile is initialized using default constructor.
 */
struct CommandData {
    readFromFile reader_classified;
    readFromFile reader_unclassified;
    int k = 5;
    string distanceMetric = "AUC";
    bool isDataUploaded = false;
    bool isClassified = false;
};

class Command {
protected:
    DefaultIO *dio;

public:
    string description;
    Command(string description, DefaultIO *dio) : dio(dio) {
        this->description = description;
    }
    // c++ initializes members of object with ": dio(dio)" syntax.
    // abstract functions
    virtual void execute(CommandData *new_commandData) = 0;
    // destructor
    virtual ~Command(){};
};


class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO *dio) : Command("1. upload an unclassified csv data file", dio) {}
    void execute(CommandData *commandData) override {
        // TODO: server responsible for uploaded file input check, client for written file.
        this->dio->write("Please upload your local train CSV file.");
        string file_path = this->dio->read();
        commandData->reader_classified.setFile(file_path);
        int flag = commandData->reader_classified.read();
        if (flag == -1) {
            // read function appends values to members, so they should be erased.
            this->dio->write("invalid input");
            commandData->reader_classified.clearVector();
            return;
        }
        else {
            this->dio->write("Upload complete.");
        }
        this->dio->write("Please upload your local test CSV file.");
        file_path = this->dio->read();
        commandData->reader_unclassified.setFile(file_path);
        // TODO: change read(), so it can also create reader with no y_train values
        flag = commandData->reader_unclassified.read(false);
        if (flag == -1) {
            this->dio->write("invalid input");
            // read function appends values to members, so they should be erased.
            commandData->reader_classified.clearVector();
            commandData->reader_unclassified.clearVector();
            return;
        }
        else {
            this->dio->write("Upload complete.");
        }
        commandData->isDataUploaded = true;

    }
    ~UploadCommand() override {};
};

class AlgorithmSettingsCommand : public Command {
public:
    AlgorithmSettingsCommand(DefaultIO *dio) : Command("2. algorithm settings", dio) {}
    void execute(CommandData *commandData) {
        string k = to_string(commandData->k);
        this->dio->write("The current KNN parameters are: K = " + k + ", distance metric = " +
        commandData->distanceMetric);
        string input = this->dio->read();
        vector<string> dataInput = checkCommandTwo(input);
        if (dataInput.empty()) {
            // user pressed enter, values should remain.
            return;
        }
        if (dataInput.size() == 1) {
            this->dio->write("invalid input");
            return;
        }
        // TODO: what error to print if num of args != 2?
        // input check for values
        if (dataInput[0] == "Error" || dataInput[1] == "Error") {
            if (dataInput[0] == "Error") {
                this->dio->write("invalid value for K");
            }
            if (dataInput[1] == "Error") {
                this->dio->write("invalid value for metric");
            }
            return;
        }
        // if reader was constructed, should check k < number of features
        if (commandData->isDataUploaded &&
        stoi(dataInput[0]) >commandData->reader_classified.featuresPerLine) {
            this->dio->write("invalid value for K");
        }
        commandData->k = stoi(dataInput[0]);
        commandData->distanceMetric = dataInput[1];
    }
    ~AlgorithmSettingsCommand() override {};
};

class ClassifyDataCommand : public Command {
public:
    ClassifyDataCommand(DefaultIO *dio) : Command("3. classify data", dio) {}
    void execute(CommandData *commandData) {
        // data was not uploaded
        if (!commandData->isDataUploaded) {
            this->dio->write("please upload data");
            return;
        }
        // TODO: should run knn on classified, and than classify the unclassified
        string prediction;
        Knn knn = Knn(commandData->k,commandData->distanceMetric, commandData->reader_classified.X_train,
                      commandData->reader_classified.y_train);
        for (int i = 0; i < commandData->reader_unclassified.X_train.size(); i++) {
            prediction = knn.predict(commandData->reader_unclassified.X_train[i]);
            commandData->reader_unclassified.y_train[i] = prediction;
        }
        commandData->isClassified = true;
    }
    ~ClassifyDataCommand() override {};
};

class DisplayResultCommand : public Command {
public:
    DisplayResultCommand(DefaultIO *dio) : Command("4. display results", dio) {}
    void execute(CommandData *commandData) {
        if (!commandData->isDataUploaded) {
            this->dio->write("please upload data");
        }
        else if (!commandData->isClassified) {
            this->dio->write("please classify the data");
        }
        // data is uploaded and classified
        else {
            for (int i=0; i < commandData->reader_unclassified.y_train.size(); i++) {
                this->dio->write(to_string(i + 1) + "\t" + commandData->reader_unclassified.y_train[i]);
            }
            this->dio->write("Done.");
        }
    }
    ~DisplayResultCommand() override {};
};

class DownloadResultsCommand : public Command {
public:
    DownloadResultsCommand(DefaultIO *dio) : Command("5. download results", dio) {}
    void execute(CommandData *commandData) {
        if (!commandData->isDataUploaded) {
            this->dio->write("please upload data");
        }
        else if (!commandData->isClassified) {
            this->dio->write("please classify the data");
        }
        // data is uploaded and classified
        else {
            // TODO: client side should check for path validity. server should write to file.
            this->dio->write("Please enter path to the new file:");
            string path = this->dio->read();
            ofstream file;
            file.open(path);
            if (file.is_open()) {
                for (int i = 0; i < commandData->reader_unclassified.y_train.size(); i++) {
                    string write = to_string(i + 1) + "," + commandData->reader_unclassified.y_train[i] + "\n";
                    file << write;
                }
                file.close();
            }
            else {
                this->dio->write("invalid input");
            }
        }
    }
    ~DownloadResultsCommand() override {};
};

class ExitCommand : public Command {
public:
    ExitCommand(DefaultIO *dio) : Command("8. exit", dio) {}
    void execute(CommandData *commandData) {}
    ~ExitCommand() override {}
};

#endif