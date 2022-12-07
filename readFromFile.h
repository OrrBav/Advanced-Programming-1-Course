
#include <string>
using namespace std;

#ifndef DATE_H
#define DATE_H

class readFromFile
{
private:
    string fileName;

public:
    readFromFile(string inputFile);
    int read();
};


#endif

