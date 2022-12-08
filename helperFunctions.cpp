#include "function.h"
#include <iostream>
#include <sstream>
using namespace std;

bool isInteger(char *str) {
    if (*str == '\0') 
        return false;

    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }

    return true;
}

bool isFloat(string& str) {
    // create a stream from param 'str' because we want to read from it like cin
    istringstream stream(str);
    float f;
    stream >> f;
    // we should have reached the end of the string 
    // because we're simply parsing a string that contains only a float number
    bool ReachedEndOfString = stream.eof();
    // reading from the stream into a float number should have succeeded
    bool succeeded = !stream.fail();
    // we're checking for end for string because of this example: "3.14hello" -> "hello", f=3.14
    return ReachedEndOfString && succeeded;
}

// this function should parse the line given to it, and exit if there's an error (e.g. feature is not a float)
// we use hasLabel=true when we read from an input file with labels
// we use hasLabel=false when we read input from the user (no label)
ParsedLine parseInput(string& line, bool hasLabel, char delimiter) {
    // this struct holds the line's values: features and label (if exists)
    struct ParsedLine ret;
    stringstream strstream(line);
    vector<string> row;
    string word;
    // read every word between the delimiter (e.g. ',' for csv and ' ' for user input)
    while (getline(strstream, word, delimiter)) 
        row.push_back(word);

    // if we have a label - we want to parse it, and make sure row will only contain features
    if (hasLabel) {
        ret.label = row.back();
        row.pop_back();
    }

    // run through every word (feature) in the row vector
    for (string& str : row) {
        // make sure the word is a float, otherwise we exit
        if (!isFloat(str)) {
            cout << "Encountered an invalid (non-float) feature: " << str << endl;
            exit(-1);
        }
        else {
            float feature = stof(str);
            ret.features.push_back(feature);
        }
    }
    return ret;
}

/*
 * calculates the subtraction result of the 2 input vectors.
 * @param v1, v2 input vectors
 * @param v3 the result vector
 * @return float vector that holds the result
 */
vector <float> vectorSubtraction(vector <float> v1, vector <float> v2) {

    vector <float> v3;
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) - v2.at(i)) ;
    }
    return v3;
}

/*
 * raises each element in the input vector to the power of toThePowerOf.
 * @param toThePowerOf is the power we raise, default value is 2.
 * @param vector the input vector
 * @return float vector that holds the result
 */
vector <float> vectorRaiseToPower(vector <float> vector, double toThePowerOf) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = pow(vector.at(i),toThePowerOf);
     }
    return vector;
}

/*
 *  sums all the elements in the input vector and perform square root on the sum.
 *  @param vector input vector
 *  @param vectorSquarred is the float result
 *  @return the squared root of the sum of elements in input vector.
 */
float vectorSquareRoot(vector <float> vector) {
     
    float vectorSquarred = sqrt(vectorSum(vector));
    return vectorSquarred;
}

/*
 * calculates the absolute value of each element in the input vector.
 * @param vector input vector and also the return vector after absolute value.
 * @return float vector that holds the result
 */
vector <float> vectorAbsolute(vector <float> vector) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = abs(vector.at(i));
     }
    return vector;
}

/*
 * calculates the sum of the elements in the input vector.
 * @param vector input  vector
 * @return the float sum of the vector.
 */
float vectorSum(vector <float> vector) {
     float sum = 0;
     for (int i = 0; i < vector.size(); i++) {
       sum += vector.at(i);
     }
    return sum;
}

/*
 * calculates the addition result of the 2 input vectors.
 * @param v1, v2 input float vectors
 * @param v3 the result float vector
 * @return float vector that holds the result
 */
vector <float> vectorAddition(vector <float> v1, vector <float> v2) {
    vector <float> v3;
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) + v2.at(i));
    }
    return v3;
}
