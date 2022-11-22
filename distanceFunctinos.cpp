#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#include "function.h"


float euclideanDistance(vector <float> v1, vector <float> v2) {
    float eucDist = vectorSquareRoot(vectorRaiseToPower(vectorSubstruction(v1,v2)));
    return eucDist;

}


float manhattanDistance(vector <float> v1, vector <float> v2) {
    float manDist = vectorSum(vectorAbsolute(vectorSubstruction(v1, v2)));
    return manDist;
    
}


float chebyshevDistance(vector <float> v1, vector <float> v2) {
    vector <float> sabtructedVec  = vectorSubstruction(v1, v2);

    float max = sabtructedVec.at(0); //init with first element in vector
    for (int i = 0; i < sabtructedVec.size(); i++)    {
        if (sabtructedVec.at(i) > max) {
            max = sabtructedVec.at(i); 
        } 
    }
    return max;
}


float canberraDistance(vector <float> v1, vector <float> v2) {
    vector<float> numerator, denominator, resultVector;
    numerator = vectorAbsolute(vectorSubstruction(v1, v2));
    denominator = vectorAddition(vectorAbsolute(v1), vectorAbsolute(v2));
    // make sure to check denominator isn't 0

    for (int i = 0; i < v1.size(); i++) {
        resultVector.push_back(numerator.at(i) / denominator.at(i));
    }
    return vectorSum(resultVector);

}


float minkowskiDistance(vector <float> v1, vector <float> v2) {
    const double p = 1;
    float sum = vectorSum(vectorRaiseToPower(vectorAbsolute(vectorSubstruction(v1, v2)), p));
    return(pow(sum, 1 / p));

}
