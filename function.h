#ifndef ADVANCED_PROGRAMMING_1_FUNCTION_H
#define ADVANCED_PROGRAMMING_1_FUNCTION_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "io.h"
using namespace std;

struct ParsedLine {
    vector<float> features;
    string label;
};

int listenToPort(int port);
int acceptClient(int sock);
vector<string> splitString(string str, char delim);
bool checkDistanceInput(string inputDistance);
bool checkPort (string portNum);
bool checkIP(string str_ip);
bool checkInputData(string data);
bool isPositiveInteger(const char *str);
bool isFloat(string& str);
vector <string> checkCommandTwo (string input);
ParsedLine parseInput(string& line, bool hasLabel, char delimiter);

bool uploadFile(SocketIO sio, string filePath);
bool downloadFile(SocketIO sio, string filePath);
bool uploadFileLine(DefaultIO *dio, string filePath);
bool downloadFileLine(const DefaultIO *dio, string filePath);

vector <float> check(string input_str, vector <float>& numbers);
void print_decimal(float q);
void trim(string& s);

vector <float> vectorSubtraction(vector <float> v1, vector <float> v2);
vector <float> vectorRaiseToPower(vector <float> vector, double toThePowerOf = 2);
float vectorSquareRoot(vector <float> vector);
vector <float> vectorAbsolute(vector <float> vector);
float vectorSum(vector <float> vector);
vector <float> vectorAddition(vector <float> v1, vector <float> v2);

// distance functions:
float euclideanDistance(vector <float> v1, vector <float> v2);
float manhattanDistance(vector <float> v1, vector <float> v2);
float chebyshevDistance(vector <float> v1, vector <float> v2);
float canberraDistance(vector <float> v1, vector <float> v2);
float minkowskiDistance(vector <float> v1, vector <float> v2);

#endif //ADVANCED_PROGRAMMING_1_FUNCTION_H
