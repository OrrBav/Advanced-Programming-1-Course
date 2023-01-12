#include "function.h"

using namespace std;

// split input string by given delimiter, returns vector<string> of split input
vector<string> splitString(string str, char delim) {
    vector<string> words;
    istringstream iss(str);
    string word;
    // split every 'delim' and insert each str to 'words' vector
    while (getline(iss, word, delim)) {
        words.push_back(word);
    }
    return words;
}

/* checks the given data is valid. data = "vector distanceMetric k"
    parsing the input data into vector, distance metric, k, and validates each one  */
bool checkInputData(string data) {
    vector<string> words = splitString(data, ' ');

    // minimal input data size is 3 (e.g. "3 MAN 7"). less than that is invalid
    if (words.size() < 3) {
        // cout << "words size < 3";
        return false;
    }

    // splitting the data into vector, distance metric, k
    string kInput = words.back();
    words.pop_back();
    string distanceInput = words.back();
    words.pop_back();
    // after popping k and distance, the rest is just the vector
    vector<string> vecFloatInputs = words;

    /* ORR's check input k
    if (kInput.empty()) {
        cout << "invalid k value 1" << endl;
        return false;
    }
    for (char c : kInput) {
        if (!isdigit(c)) {
            cout << "invalid k value 2: " << c << endl;
            return false;
        }
    }
    int k = stoi(kInput);
    if (k < 1) {
        cout << "invalid k value 3" << endl;
        return false;
    } */

    if (!isPositiveInteger(kInput.c_str())) {
        return false;
    }

    // check input distance metric
    if (!checkDistanceInput(distanceInput)) {
        return false;
    }
    
    // check input vector. 'auto' type is vector<string>::iterator
    for (auto iter = vecFloatInputs.begin(); iter != vecFloatInputs.end(); ++iter) {
        if (!isFloat(*iter)) {
            return false;
        }
    }

    return true;
}


bool checkDistanceInput(string inputDistance) {
    if (inputDistance != "AUC" && inputDistance != "MAN" && inputDistance != "CHB" &&
        inputDistance != "CAN" && inputDistance != "MIN" ) {
        return false;
    }
    return true;
}

// checks that input port is valid
bool checkPort (string portNum) {
//    int temp;
        if (isPositiveInteger(portNum.c_str())) {
            int temp = stoi(portNum);
            if ((1024 <= temp) && (temp <= 65535)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
           return false;
        }
}


/**
 * checks if input ip is valid - 4 numbers, each range from 0 to 255, separated by dots.
 * @param str_ip - string of input ip
 * @return true is valid, false otherwise.
 */
bool checkIP(string str_ip) {
    char single_cut;
    string new_num;
    int dot_count = 0;
    vector <int> ipNumbers;
    for (int i = 0; i < str_ip.length(); i++) {
        if (isdigit(str_ip[i])) {
            /* converts input_srt[i] from char to string, and enables stoi check */
            single_cut = str_ip[i];
            string string_cut{ single_cut };
            new_num += string_cut;
        }
            /* char is not a digit: can only be a dot. */
        else {
            if (str_ip[i] == '.') {
                dot_count++;
                /* more than 3 digits are invalid ip address. */
                if (new_num.length() > 3) {
                    return false;
                }
                ipNumbers.push_back(stoi(new_num));
                new_num = "";
            }
                /* invalid char: not a digit or a dot. */
            else {
                return false;
            }
        }
    }
    /* we check new_num length again for the last octate in the ip address. */
    if (dot_count != 3 || new_num.length() > 3) {
        return false;
    }
    ipNumbers.push_back(stoi(new_num));
    for (int i = 0; i < ipNumbers.size(); i++) {
        if (ipNumbers[i] < 0 || ipNumbers[i] > 255) {
            return false;
        }
    }
    return true;
}

/*  checks that the given string holds a valid and positive integer. 
    receives a pointer to the beginning of the string and checks char after char    */
bool isPositiveInteger(const char *str) {
    if (*str == '\0') {
        return false;
    }
    if (*str == '0') {
        return false;
    }
    // check char after char in the given string
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

/* check if given string holds a valid float value */
bool isFloat(string& str) {
    // create a stream from param 'str' because we want to read from it like cin
    // this also makes sure we can read small floats with 'E' like 9.736518826502699E-4
    istringstream stream(str);
    float f;
    stream >> f;
    // we should have reached the end of the string 
    // because we're simply parsing a string that contains only a float number
    bool ReachedEndOfString = stream.eof();
    // reading from the stream into a float number should have succeeded
    bool succeeded = !stream.fail();
    // we're checking for end for string to avoid something like this: "3.14hello" -> "hello", f=3.14
    return ReachedEndOfString && succeeded;
}

/*  this function should parse the line given to it, and exit if there's an error (feature is not a float)
    we use hasLabel=true when we read from an input file with labels
    we use hasLabel=false when we read input from the user (no label) */
ParsedLine parseInput(string& line, bool hasLabel, char delimiter) {
    // this struct holds the line's values: features and label (if exists)
    struct ParsedLine ret;
    stringstream strstream(line);
    vector<string> row;
    string word;
    // read every word between the delimiter (',' for csv and ' ' for user input)
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
 *  @param vectorSquared is the float result
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

/*
 * function should iterate over users input(represented by input_str) and check if input is valid.
 * valid input - only numbers (can have decimal point) separated by dots.
 * return - vector containing float values of user's input numbers, or exception is input is invalid.
 */
vector <float> check(string input_str, vector <float>& numbers) {
    string new_num;
    char single_cut;
    bool space_flag = false;
    bool dot_flag = false;
    // finds if first and last char in string are digits, and ensures for loop logic
    if ((isdigit(input_str[0]) == false) || isdigit(input_str[input_str.length() - 1]) == false) {
        cout << "input should be numbers separated by spaces." << endl;
        exit (-1);
    }
    for (int i = 0; i < input_str.length(); i++) {
        if (isdigit(input_str[i]) == true) {
            // iterating over number, so space should be set to false
            space_flag = false;
            // converts input_srt[i] from char to string, and enables stof()
            single_cut = input_str[i];
            string string_cut {single_cut};
            new_num += string_cut;

        }
            // char is not a digit: can be space, dot (good) or other ABC (bad)
        else {
            // two consecutive spaces
            if (input_str[i] == ' ') {
                if (space_flag == true) {
                    cout << "input should be numbers separated by spaces." << endl;
                    exit (-1);
                }
                    // prepare for a new valid number
                else {
                    space_flag = true;
                    dot_flag = false;
                    numbers.push_back(stof(new_num));
                    new_num = "";
                }
            }
                // char is dot - should be only one per number
            else if(input_str[i] == '.') {
                // there was already a dot in number
                if (dot_flag == true) {
                    cout << "input should be numbers separated by spaces." << endl;
                    exit (-1);
                }
                else {
                    dot_flag = true;
                    new_num += ".";
                }
            }
                // invalid char
            else {
                cout << "input should be numbers separated by spaces." << endl;
                exit (-1);
            }
        }
    }
    numbers.push_back(stof(new_num));
    return numbers;
}

/*
 * function ensures print values are as instructed, by determining how many decimal point should be printed on user's
 * screen.
 * input - float number q, which is the distance calculated on main.
 */
void print_decimal(float q) {
    double p = double(q);
    // if p is an integer num
    if (floor(p) == ceil(p)) {
        cout.precision(1);
        cout << fixed << p << endl;

    }
        // if p has a decimal point
    else {
        cout.precision(4);
        cout << fixed << p << endl;
    }

}