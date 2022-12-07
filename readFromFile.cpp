
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
    valuesPerLine = 0; // init with 0 so it can be updated when reading the file
}

// the read function:
int readFromFile::read() {

    // init all containers
    vector<vector<string>> X_train;  // our 2d vector, containing all inputs
    vector<string> row;
    vector<string> y_train; // the labels of the inputs (X_train)
    string line, word;

    // open file and read from it
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear(); // removes all the elements of the vector, making it size 0 so ew can reuse it when reading next line 

            stringstream str(line); // puts current line in "str" variable

            while (getline(str, word, ','))
                row.push_back(word);  // adds single word to row (vector)

            // save the number of elements in a line
            if (row.size() > valuesPerLine) {
                valuesPerLine = row.size();
            }

            // takes last input string in current row and adds it to labels
            string label = row.back();
            y_train.push_back(label);
            // now delete this last string from row and add row to X_train
            row.pop_back();
            X_train.push_back(row);
        }
    }

    else { // TODO add return or error???
        cout << "Could not open the file\n";
    }

    // start test
    cout << "X_train: \n";
    for (int i = 0; i < X_train.size(); i++) {
        for (int j = 0; j < X_train[i].size(); j++) {
            cout << X_train[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "y_train: \n";
    for (int i = 0; i < y_train.size(); i++) {
        cout << y_train[i] << "\n";
    }
    cout << "valuesPerLine: " << valuesPerLine << endl;
    // end of test

    return 0;
}
