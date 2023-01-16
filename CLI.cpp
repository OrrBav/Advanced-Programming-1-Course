//
// Created by orrbb on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    CommandData new_commandData;
    this->commandData = new_commandData ;
    //TODO make sure commandData is passed by reference
    commands.push_back(new UploadCommand(dio, commandData));
    commands.push_back(new AlgorithmSettingsCommand(dio, commandData));
    commands.push_back(new ClassifyDataCommand(dio, commandData));
    commands.push_back(new DisplayResultCommand(dio, commandData));
    commands.push_back(new DownloadResultsCommand(dio, commandData));
    commands.push_back(new ExitCommand(dio));
    //TODO: add other commands. should have shared state?
}

// TODO
void CLI::printManu() {
    dio->write("Welcome to the KNN Classifier Server. Please choose an option:");
    for (int i = 0; i < commands.size(); i++) {
        dio->write(commands[i]->description);
    }
}

// TODO
void CLI::start() {
    int input = 0;
    string inputStr;
    int index;
    while (input != 8) {
        printManu();
        inputStr = dio->read();
        if (!isPositiveInteger(inputStr.c_str())) {
            // input check
            continue;
        }
        input = stoi(inputStr);
        if (input < 1 || (input > 5 && input != 8))
            continue;
        index = input - 1;
        if (input == 8) {
            index = 5;      // ensure command[index] works with all manu elements
        }
        commands[index]->execute();
    }
}



// TODO - delete all commands
CLI::~CLI() {
    for (auto & command : commands) {
        delete command;
    }
}


int main () {
    StandardIO dio;
    CLI cli(&dio);
    cli.start();
}