
using namespace std;

#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H
#include "function.h"

class readFromFile {
private:
    string fileName;
    vector<float> handleLine(string& line);
public:
    // our 2d vector, containing all inputs
    vector<vector<float>> X_train;
    // the labels of the inputs (X_train)
    vector<string> y_train;
    int featuresPerLine;

    // constructor:
    readFromFile(string inputFile);

    // the read function:
    int read();
};

#endif

