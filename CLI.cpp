//
// Created by orrbb on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    readFromFile reader_classified("No path was given");
    readFromFile reader_unclassified("No path was given");
    // has
    CommandData new_commandData = {reader_classified, reader_classified};
    this->commandData = new_commandData ;
    //TODO make sure is it passed by reference
    commands.push_back(new UploadCommand(dio, commandData));
    //TODO: add other commands. should have shared state?

}