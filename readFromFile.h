

#include <string>
using namespace std;

#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

class readFromFile {

public: // TODO: members should be private??
    // members:
    string fileName;
    int valuesPerLine;

    // constructor:
    readFromFile(string inputFile);

    // the read function:
    int read();
};

#endif

