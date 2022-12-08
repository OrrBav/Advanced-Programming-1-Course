//Orr, Ariel
#include "function.h"
#include "knn.h"
#include "readFromFile.h"
#include <string>

using namespace std;

int main(int argc, char** argv[])
{

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
    }
    

    // vector<vector<float>> x_train
    //         {
    //                 {1, 2, 3},
    //                 {4, 5, 6},
    //                 {3, 2, 1}
    //         };
    // vector <string> y_train {
    //         "a", "b", "a"
    // };
    // int k = 2;
    // Knn knn = Knn(k, "lol",x_train, y_train);
    // vector <float> test {
    //     4.5, 5.2, 5.9
    // };
    // string s = knn.predict(test);
    // cout << s << endl;
    // // should add delete for distance metric in knn
    return 0;

}
