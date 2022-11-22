#include <vector>
#include <iostream>
using namespace std;

#include "function.h"

float euclideanDistance(vector <float> v1, vector <float> v2) {
    float eucDist = vectorSquareRoot(vectorRaiseToPower(vectorSubstruction(v1,v2)));
    return eucDist;

}


float manhattanDistance() {


    
}


float chebyshevDistance() {


    
}


float CanberraDistance(vector <float> v1, vector <float> v2) {
    vector<float> numerator, denominator, resultVector;
    numerator = vectorAbsolute(vectorSubstruction(v1, v2));
    denominator = vectorAddition(vectorAbsolute(v1), vectorAbsolute(v2));
    // make sure to check denominator isn't 0

    for (int i = 0; i < v1.size(); i++) {
        resultVector.push_back(numerator.at(i) / denominator.at(i));
    }
    return vectorSum(resultVector);

}


float minkowskiDistance() {


    
}


