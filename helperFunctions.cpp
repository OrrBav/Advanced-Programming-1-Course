#include "function.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


int acceptClient(int sock) {
    struct sockaddr_in client_sin; /* address struct for the sender info */
    unsigned int addr_len = sizeof (client_sin);
    /* accept creates a new client socket for the connecting client */
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("Error accepting client");
        exit(-1);
    }
    return client_sock;
}


int listenToPort(int port) {
    const int server_port = port;
    // socket creation, sock_stream is a const for TCP
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(-1);
    }

    /* creating the struct for the address */
    struct sockaddr_in server_sin;     /* struct for the address */
    memset(&server_sin, 0, sizeof (server_sin));  /* It copies a single character for a specified number
    * of times to an object (sin) */
    server_sin.sin_family = AF_INET;   /* address protocol type */
    server_sin.sin_addr.s_addr = INADDR_ANY; /* const for any address */
    server_sin.sin_port = htons(server_port); /* defines the port */
    /* binding the socket to the port and ip_address, while checking it can be done */
    if (bind(sock, (struct sockaddr *) &server_sin, sizeof (server_sin)) < 0) {
        perror("Error binding socket");
        exit(-1);
    }
    /* listens up to 5 clients at a time */
    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket");
        exit(-1);
    }
    return sock;
}

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

bool isNotSpace(unsigned char ch) {
    // checks for each char if is not a space
    return !isspace(ch);
}

void trim(string& s) {
    // removes spaces (e.g: " ", \r, \n) from given string ()
    // removes before start of str "   asd"
    s.erase(s.begin(), find_if(s.begin(), s.end(), isNotSpace));
    // removes after end of str "asd   \r"
    s.erase(find_if(s.rbegin(), s.rend(), isNotSpace).base(), s.end());
}

/*  this function should parse the line given to it, and exit if there's an error (feature is not a float)
    we use hasLabel=true when we read from an input file with labels
    we use hasLabel=false when we read input from the user (no label) */
ParsedLine parseInput(string& line, bool hasLabel, char delimiter) {
    // this struct holds the line's values: features and label (if exists)
    struct ParsedLine ret;
    trim(line);

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
        //cout << ret.label << endl;
    }

    // run through every word (feature) in the row vector
    for (string& str : row) {      
        // make sure the word is a float, otherwise we exit
        if (!isFloat(str)) {
            cout << "Encountered an invalid (non-float) feature: " << str << endl;
            exit(0);
        }
        else {
            float feature = stof(str);
            ret.features.push_back(feature);
        }
    }
    
    return ret;
}

// returns true on success
bool downloadFileLine(const DefaultIO *dio, string filePath) {
    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    string line;
    do {
        line = dio->read();
        if (line == "Done.") {
            break;
        }
        else if (line == "SERVER_UPLOAD_ABORT") {
            // client signals server that he received an invalid file, and therefore should stop command.
            return false;
        }
        file << line << endl;
    } while (true);
    file.close();
    return true;
}

// returns true on success
bool uploadFileLine(DefaultIO *dio, string filePath) {
    fstream file(filePath, ios::in);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        dio->write(line);
    }
    dio->write("Done.");
    file.close();
    return true;
}

// NOTE: not in use, but do not delete for now!
// returns true on success
// bool downloadFile(SocketIO sio, string filePath) {
//     ofstream file(filePath, ios::trunc);
//     if (!file.is_open()) {
//         return false;
//     }

//     do {
//         string data = sio.read();
//         size_t idx = data.find("Done.");
//         if (idx != string::npos) {
//             // so we found "Done.", and save string up to its index
//             file << data.substr(0, idx - 1);
//             break;
//         }
//         file << data << endl;
//     } while (true);

//     return true;
// }
// NOTE: not in use, but do not delete for now!
// returns true on success
// bool uploadFile(SocketIO sio, string filePath) {
//     const size_t BUFFER_SIZE = 4096;
//     char buffer[BUFFER_SIZE];
//     FILE *file = fopen(filePath.c_str(), "r");
//     size_t bytes_read;
//     do {
//         bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE - 1, file);
//         if (bytes_read <= 0) {
//             return false;
//         }
//         buffer[BUFFER_SIZE - 1] = '\0';
//         string str = buffer;
//         cout << str << endl;
//         sio.write(buffer);
//     // as long as we are still reading the full buffer size, it means we still need to read more
//     } while (bytes_read == BUFFER_SIZE - 1);
//     sio.write("Done.");
//     return true;
// }

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

/**
 * function that input checks command number two.
 * @param input - user's input. should be an k (positive integer) and a valid distance metric.
 * @return - if input is valid, it returns input data separated into 2
 * vector cells. else, it returns an "error" string in the cell which error has occurred.
 */
vector <string> checkCommandTwo (string input) {
    vector<string> words = splitString(input, ' ');
    vector <string> returnData;
    // if input is empty string, user pressed enter, and command2 values should remain unchanged
    if (words.empty()) {
        return returnData;
    }
    // input size should be 2: integer k and distance metric
    if (words.size() != 2) {
        returnData.emplace_back("Error - should be provided with 2 args");
        return returnData;
    }
    // splitting the data into k, distance metric
    string distanceInput = words.back();
    words.pop_back();
    string kInput = words.back();
    words.pop_back();
    returnData.emplace_back(kInput);
    returnData.emplace_back(distanceInput);

    if (!isPositiveInteger(kInput.c_str())) {
        returnData[0] = "Error";
    }
    // kInput is a number, but too big to be an int type.
    try {
        int kCheck = stoi(kInput);
    } catch (const exception& e) {
        returnData[0] = "Error";
    }

    // check input distance metric
    if (!checkDistanceInput(distanceInput)) {
        returnData[1] = "Error";
    }
    return returnData;
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