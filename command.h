#ifndef ADVANCED_PROGRAMMING_1_EX4_COMMAND_H
#define ADVANCED_PROGRAMMING_1_EX4_COMMAND_H

#include <string>
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


class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO *dio, CommandData &new_commandData) : Command("1. upload an unclassified csv data file", dio) {
        this->commandData = new_commandData;
    }
    void execute() override {
        // TODO: server responsible for uploaded file input check, client for written file.
        this->dio->write("Please upload your local train CSV file.");
        string file_path = this->dio->read();
        this->commandData.reader_classified.setFile(file_path);
        int flag = this->commandData.reader_classified.read();
        if (flag == -1) {
            this->dio->write("invalid input");
            return;
        }
        else {
            this->dio->write("Upload complete.");
        }
        this->dio->write("Please upload your local test CSV file.");
        file_path = this->dio->read();
        this->commandData.reader_unclassified.setFile(file_path);
        // TODO: change read(), so it can also create reader with no y_train values
        flag = this->commandData.reader_unclassified.read();
        if (flag == -1) {
            this->dio->write("invalid input");
            return;
        }
        else {
            this->dio->write("Upload complete.");
        }
        this->commandData.isDataUploaded = true;

    }
    ~UploadCommand() override {};
};

class AlgorithmSettingsCommand : public Command {
public:
    AlgorithmSettingsCommand(DefaultIO *dio, CommandData &new_commandData) : Command("2. algorithm settings", dio) {
        this->commandData = new_commandData;
    }
    void execute() {
        string k = to_string(this->commandData.k);
        this->dio->write("The current KNN parameters are: K = " + k + ", distance metric = " +
        this->commandData.distanceMetric);
        string input = this->dio->read();
        vector<string> dataInput = checkCommandTwo(input);
        if (dataInput.empty()) {
            // user pressed enter, values should remain.
            return;
        }
        if (dataInput.size() == 1) {
            this->dio->write("Should provide 2 arguments.");
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
        if (this->commandData.isDataUploaded &&
        stoi(dataInput[0]) > this->commandData.reader_classified.featuresPerLine) {
            this->dio->write("invalid value for K");
        }
        this->commandData.k = stoi(dataInput[0]);
        this->commandData.distanceMetric = dataInput[1];
    }
    ~AlgorithmSettingsCommand() override {};
};

class ClassifyDataCommand : public Command {
public:
    ClassifyDataCommand(DefaultIO *dio, CommandData &new_commandData) : Command("3. classify data", dio) {
        this->commandData = new_commandData;
    }
    void execute() {
        // data was not uploaded
        if (!this->commandData.isDataUploaded) {
            this->dio->write("please upload data");
            return;
        }
        // TODO: should run knn on classified, and than classify the unclassified
        Knn knn = Knn(this->commandData.k, this->commandData.distanceMetric, this->commandData.reader_classified.X_train,
                      this->commandData.reader_classified.y_train);
        // TODO: loop on unclassified csv rows(=vector), and save prediction in reader_unclassified.y_train
        // string prediction = knn.predict();
    }
    ~ClassifyDataCommand() override {};
};

class DisplayResultCommand : public Command {
public:
    DisplayResultCommand(DefaultIO *dio, CommandData &new_commandData) : Command("4. display results", dio) {
        this->commandData = new_commandData;
    }
    void execute() {
        if (!this->commandData.isDataUploaded) {
            this->dio->write("please upload data");
        }
        else if (!this->commandData.isClassified) {
            this->dio->write("please classify the data");
        }
        // data is uploaded and classified
        else {
            for (int i=0; i < this->commandData.reader_unclassified.y_train.size(); i++) {
                this->dio->write(to_string(i) + "\t" + this->commandData.reader_unclassified.y_train[i]);
            }
            this->dio->write("Done.");
        }
    }
    ~DisplayResultCommand() override {};
};

class DownloadResultsCommand : public Command {
public:
    DownloadResultsCommand(DefaultIO *dio, CommandData &new_commandData) : Command("5. download results", dio) {
        this->commandData = new_commandData;
    }
    void execute() {
        if (!this->commandData.isDataUploaded) {
            this->dio->write("please upload data");
        }
        else if (!this->commandData.isClassified) {
            this->dio->write("please classify the data");
        }
        // data is uploaded and classified
        else {
            this->dio->write("Please enter path to file:");
            string path = this->dio->read();
            // TODO: write (in same format as command4) y labels to file in @path
        }
    }
    ~DownloadResultsCommand() override {};
};

class ExitCommand : public Command {
public:
    ExitCommand(DefaultIO *dio) : Command("8. exit", dio) {}
    void execute() {}
    ~ExitCommand() override {}
};

#endif