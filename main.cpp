#include "function.h"
#include "readFromFile.h"

using namespace std;

// class IDistance {
// public:
//     virtual float compute(vector<string>& a, vector<string>& b) = 0;
// }

// class ManhattanDistance {
// public:
//     float compute(vector<string>& a, vector<string>& b) {
//         // mahattan..
//     }
// };

// class KNN {
// private:
//     IDistance *m_distance;
// public:
//     KNN(IDistance *distance) : m_distance(distance) {}
//     string predict(vector<string> features);
// };

// IDistance *distance;
// if (arg_distance == "MAN") distance = new ManhattanDistance();
// else if ( .... == "")
// new KNN(distance);

// struct Distance {
//     int originalIndex;
//     int distance;
// };

// vector<struct Distance> distances;

// int comparator(struct Distance a, struct Distance b) {
//     if (a.distance > b.distance) return 1;
//     if (a.distance < b.distance) return -1;
//     return 0;
// }

// sort(distances, comparator);

// for 
//     for 
//         if (comparator(a, b) > 0) swap(a, b);


int main(int argc, char *argv[])
{
    cout <<
    // string str1, str2;
    // vector<float> numbers1, numbers2;
    // getline(cin, str1);
    // check(str1, numbers1);
    // getline(cin, str2);
    // check(str2, numbers2);
    // if (numbers1.size() != numbers2.size()) {
    //     cout << "inputs should have the same number of numbers" << endl;
    //     return -1;
    // }

    // print_decimal(euclideanDistance(numbers1, numbers2));
    // print_decimal(manhattanDistance(numbers1, numbers2));
    // print_decimal(chebyshevDistance(numbers1, numbers2));
    // if (canberraDistance(numbers1, numbers2) == -1) {
    //     cout << "Canberra distance error: cannot divide by zero" << endl;
    // }
    // else {
    //     print_decimal(canberraDistance(numbers1, numbers2));
    // }
    // print_decimal(minkowskiDistance(numbers1, numbers2));



    readFromFile reader("iris_classified.csv");
    reader.read();
    string inputVector;
    vector<float> numbers;
    getline(cin, inputVector);
    check(inputVector, numbers);
    if (numbers.size() != reader.featuresPerLine) {
        cout << "input vector should have " << (reader.featuresPerLine) << " elements, separated by spaces." << endl;
        exit(-1);
    } 
    else {
        cout << "same size" << endl;
        
        cout << "X_train: \n";
        for (int i = 0; i < reader.X_train.size(); i++) {
            for (int j = 0; j < reader.X_train[i].size(); j++) {
                cout << reader.X_train[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "y_train: \n";
        for (int i = 0; i < reader.y_train.size(); i++) {
            cout << reader.y_train[i] << "\n";
        }
        cout << "valuesPerLine: " << reader.featuresPerLine << endl;
    }

    return 0;

}
