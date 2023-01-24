#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMAND_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMAND_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
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
    int sock;
    int port;
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
        this->dio->write("CLIENT_CMD_UPLOAD");
        this->dio->write("Please upload your local train CSV file.");
        // write the train file content into a new local file on server side
        // gets input from client side
        // concat socket name to file name so it has a unique name
        const string trainFilePath = to_string(commandData->sock) + "_train.csv";
        if (!downloadFileLine(dio, trainFilePath)) {
            // client has given an invalid file.
            return;
        }
        commandData->reader_classified.setFile(trainFilePath);
        int flag = commandData->reader_classified.read(true);
        if (flag == -1) {
            // read function appends values to members, so they should be erased.
            this->dio->write("invalid input");
            commandData->reader_classified.clearVector();
            return;
        }
        this->dio->write("Upload complete.\nPlease upload your local test CSV file.");
        // write the test file content into a new local file on server side
        // concat socket name to file name so it has a unique name
        const string testFilePath = to_string(commandData->sock) + "_test.csv";
        if (!downloadFileLine(dio, testFilePath)) {
            // client has given an invalid file
            // first reader, that was initialized, should be cleared
            commandData->reader_classified.clearVector();
            return;
        }
        commandData->reader_unclassified.setFile(testFilePath);
        flag = commandData->reader_unclassified.read(false);
        if (flag == -1 ||
        commandData->reader_classified.featuresPerLine != commandData->reader_unclassified.featuresPerLine) {
            this->dio->write("invalid input");
            // read function appends values to members, so they should be erased.
            commandData->reader_classified.clearVector();
            commandData->reader_unclassified.clearVector();
            return;
        }
        commandData->isDataUploaded = true;
        this->dio->write("Upload complete.");
        remove(trainFilePath.c_str());
        remove(testFilePath.c_str());
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
        // for client loop logic
        this->dio->write("write");
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
        // input check for values
        if (dataInput[0] == "Error" || dataInput[1] == "Error") {
            if (dataInput[0] == "Error" && dataInput[1] == "Error") {
                this->dio->write("invalid value for K, invalid value for metric");
            } else if (dataInput[0] == "Error") {
                this->dio->write("invalid value for K");
            } else if (dataInput[1] == "Error") {
                this->dio->write("invalid value for metric");
            }
            return;
        }
        // if reader was constructed, should check k < number of vectors (can also be number of rows in y_train)
        if (commandData->isDataUploaded &&
        stoi(dataInput[0]) > commandData->reader_classified.X_train.size()) {
            this->dio->write("invalid value for K - features");
            return;
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
        // checks if input k is greater than number of lines in given file, and if so - sets k to be the
        // max valid value = number of rows in the classified vector.
        if (commandData->k > commandData->reader_classified.X_train.size()) {
            commandData->k =  commandData->reader_classified.X_train.size();
        }
        string prediction;
        Knn knn = Knn(commandData->k,commandData->distanceMetric, commandData->reader_classified.X_train,
                      commandData->reader_classified.y_train);
        for (int i = 0; i < commandData->reader_unclassified.X_train.size(); i++) {
            prediction = knn.predict(commandData->reader_unclassified.X_train[i]);
            commandData->reader_unclassified.y_train[i] = prediction;
        }
        this->dio->write("classifying data complete");
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
            return;
        }
        else if (!commandData->isClassified) {
            this->dio->write("please classify the data");
            return;
        }
        // data is uploaded and classified
        else {
            this->dio->write("CLIENT_CMD_RESULTS");
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
            // concat socket name to file name so it has a unique name
            const string downloadFilePath = to_string(commandData->sock) + "_download.txt";
            fstream file(downloadFilePath, ios_base::out | ios_base::trunc);
            if (!file.is_open()) {
                this->dio->write("invalid input");
                return;
            }

            for (int i=0; i < commandData->reader_unclassified.y_train.size(); i++) {
                file << to_string(i + 1) << "\t" << commandData->reader_unclassified.y_train[i] << endl;
            }
            file.close();
            this->dio->write("CLIENT_CMD_DOWNLOAD");
            this->dio->write("Please enter path to the new file:");

            // generate random port and send to client in range (10,000-60,000)
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(0, 50000);
            // send the new port to client so they can both know the new one
            auto random_integer = uni(rng);
            int port = 10000 + random_integer;
            
            int sock = listenToPort(port);
            this->dio->write(to_string(port));
            int client_sock = acceptClient(sock);

            // send file to client and close sockets
            thread t([downloadFilePath, sock, client_sock]() {
                SocketIO io(client_sock);
                uploadFileLine(&io, downloadFilePath);
                close(client_sock);
                close(sock);
                remove(downloadFilePath.c_str());
            });
            t.detach();
        }
    }
    ~DownloadResultsCommand() override {};
};

class ExitCommand : public Command {
public:
    ExitCommand(DefaultIO *dio) : Command("8. exit", dio) {}
    void execute(CommandData *commandData) {
        dio->write("CLIENT_CMD_EXIT");
    }
    ~ExitCommand() override {}
};

#endif