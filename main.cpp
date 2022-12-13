//Orr, Ariel
#include "function.h"
#include "knn.h"
#include "readFromFile.h"


#define ARG_SIZE (4)

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != ARG_SIZE) {
        cout << "Should have received " << ARG_SIZE << " arguments, but received " << argc << " instead" << endl;
        exit(-1);
    }

    string filename = argv[2];
    string distanceFuncName = argv[3];

    int k;
    if (isInteger(argv[1])) {
        k = stoi(argv[1]);
    }
    else {
        cout << "received invalid value for k: " << argv[1] << " (should be an integer)" << endl;
        exit(-1);
    }

    readFromFile reader(filename);
    reader.read();
    
    Knn knn = Knn(k, distanceFuncName, reader.X_train, reader.y_train);
    
    string inputVector;
    struct ParsedLine ret;
    while (true) {
        getline(cin, inputVector);
        ret = parseInput(inputVector, false, ' ');
        if (ret.features.size() != reader.featuresPerLine) {
            cout << "input vector should have " << (reader.featuresPerLine) << " elements, separated by spaces." << endl;
            exit(-1);
        }

        string prediction = knn.predict(ret.features);
        cout << prediction << endl;
    }
    // should delete new dismetric object
}
