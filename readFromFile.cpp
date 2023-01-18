
#include "readFromFile.h"

using namespace std;

/* go over each line,
in each line read the entire line (all values and the label)
values are stored in X_train 2d vector as strings.
labels are stored in labels 1d vector as strings.*/

/**
 * constructor for class.
 * @param inputFile - path for csv file.
 */
readFromFile::readFromFile(string inputFile) {
    fileName = inputFile;
    featuresPerLine = 0; // init with 0 so it can be updated when reading the file
}

/**
 * default constructor for class.
 */
readFromFile::readFromFile() {
    fileName = "Error! No Path was Given.";
    featuresPerLine = 0;
}

/**
 * setter for file name.
 * @param fileName - path to file.
 */
void readFromFile::setFile(string fileName) {
    this->fileName = fileName;
}

vector<float> readFromFile::handleLine(string& line, bool hasLabel) {
    struct ParsedLine ret = parseInput(line, hasLabel, ',');
    y_train.push_back(ret.label);
    X_train.push_back(ret.features);
    return ret.features;
}
// TODO: add default flag for read, handleLine
int readFromFile::read(bool hasLabel) {
    string line, word;
    // open file and read from it
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        if (getline(file, line)) {
            vector<float> row = handleLine(line, hasLabel);
            // read the first line in the file and initialize featuresPerLine
            featuresPerLine = row.size();

            // read the rest of the lines, from second line till end of file
            while (getline(file, line)) {
                vector<float> row = handleLine(line);
                // TODO: if haslabel is false, row doesnt hold the last number in row, that leat to if statment
                // to be true.
                if (featuresPerLine != row.size()) {
                    // cout << "Encountered two lines with different number of features" << endl;
                    // exit(-1);
                    // clear reader members
                    this->X_train.clear();
                    this->y_train.clear();
                    return -1;
                }
            }
        }
    }
    else { 
        // cout << "Failed to read file" << endl;
        // exit(-1);
        // clear reader members
        this->X_train.clear();
        this->y_train.clear();
        return -1;
    }
    return 0;
}

void readFromFile::clearVector () {
    this->X_train.clear();
    this->y_train.clear();
}
