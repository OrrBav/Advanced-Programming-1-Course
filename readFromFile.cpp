
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "function.h"
#include "readFromFile.h"

using namespace std;

/* go over each line,
in each line read the entire line (all values and the label)
values are stored in X_train 2d vector as strings.
labels are stored in labels 1d vector as strings.*/


// constructor:
readFromFile::readFromFile(string inputFile) {
    fileName = inputFile;
    featuresPerLine = 0; // init with 0 so it can be updated when reading the file
}

vector<float> readFromFile::handleLine(string& line) {
    struct ParsedLine ret = parseInput(line, true, ',');
    y_train.push_back(ret.label);
    X_train.push_back(ret.features);
    return ret.features;
}

int readFromFile::read() {
    string line, word;
    // open file and read from it
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        if (getline(file, line)) {
            vector<float> row = handleLine(line);
            // read the first line in the file and initialize featuresPerLine
            featuresPerLine = row.size();

            // read the rest of the lines, from second line till end of file
            while (getline(file, line)) {
                vector<float> row = handleLine(line);
                if (featuresPerLine != row.size()) {
                    cout << "Encountered two lines with different number of features" << endl;
                    exit(-1); 
                }
            }
        }
    }
    else { 
        cout << "Failed to read file" << endl;
        exit(-1);
    }
    return 0;
}
