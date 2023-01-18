//
// Created by orrbb on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    CommandData new_commandData;
    this->commandData = new_commandData;
    //TODO make sure commandData is passed by reference
    commands.push_back(new UploadCommand(dio));
    commands.push_back(new AlgorithmSettingsCommand(dio));
    commands.push_back(new ClassifyDataCommand(dio));
    commands.push_back(new DisplayResultCommand(dio));
    commands.push_back(new DownloadResultsCommand(dio));
    commands.push_back(new ExitCommand(dio));
}


/**
 * prints description of all commands.
 */
void CLI::printMenu() {
    dio->write("Welcome to the KNN Classifier Server. Please choose an option:");
    for (int i = 0; i < commands.size(); i++) {
        dio->write(commands[i]->description);
    }
}

/**
 * main function for CLI. loops on menu, and handles it commands.
 */
void CLI::start() {
    CommandData new_commandData;
    int input = 0;
    string inputStr;
    int index;
    while (input != 8) {
        printMenu();
        inputStr = dio->read();
        if (!isPositiveInteger(inputStr.c_str())) {
            this->dio->write("invalid input");
            continue;
        }
        input = stoi(inputStr);
        if (input < 1 || (input > 5 && input != 8)) {
            this->dio->write("invalid input");
            continue;
        }
        index = input - 1;
        if (input == 8) {
            index = 5;      // ensure command[index] works with all manu elements
        }
        commands[index]->execute(&new_commandData);
    }
}

/**
 * destructor for CLI class.
 */
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