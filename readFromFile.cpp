
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "function.h"
#include "readFromFile.h"

using namespace std;

// go over each line
// in each line read the entire line (all values and the label)
// values are stored in X_train 2d vector as strings.
// labels are stored in labels 1d vector as strings.


// constructor:
readFromFile::readFromFile(string inputFile) {
    fileName = inputFile;
    featuresPerLine = 0; // init with 0 so it can be updated when reading the file
}

vector<float> readFromFile::handleLine(string& line) {
    vector<string> row;
    stringstream str(line); // puts current line in "str" variable
    string word;
    
    while (getline(str, word, ','))
        row.push_back(word);  // adds single word to row (vector)

    // takes last input string in current row and adds it to labels
    string label = row.back();
    y_train.push_back(label);
    // now delete this last string from row
    row.pop_back();

    // convert row (vector<string>) to a regular string
    string stringsRow;
    for (const auto &piece : row) stringsRow = stringsRow + piece + " ";
    // delete last space " "
    stringsRow.pop_back();
    
    // convert strings to vector<floats> and add to X_train
    vector<float> floatsRow;
    check(stringsRow, floatsRow);
    X_train.push_back(floatsRow);
    return floatsRow;
}

// the read function:
int readFromFile::read() {
    string line, word;
    // open file and read from it
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        if (getline(file, line)) {
            vector<float> row = handleLine(line);
            // initialize featuresPerLine according to the first line in the file
            featuresPerLine = row.size();

            // reads from second line till end of file
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
