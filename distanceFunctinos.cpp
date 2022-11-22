#include "function.h"
using namespace std;

/*
 * calculates the Euclidean distance of two input vectors, based on the wikipedia formula.
 * @param v1 and v2 are input float vectors
 * @return float representing the Euclidean distance result
 */
float euclideanDistance(vector <float> v1, vector <float> v2) {
    float eucDist = vectorSquareRoot(vectorRaiseToPower(vectorSubtraction(v1,v2)));
    return eucDist;

}

/*
 * calculates the Manhattan distance of two input vectors, based on the wikipedia formula.
 * @param v1 and v2 are input float vectors.
 * @return float representing Manhattan distance result
 */
float manhattanDistance(vector <float> v1, vector <float> v2) {
    float manDist = vectorSum(vectorAbsolute(vectorSubtraction(v1, v2)));
    return manDist;
    
}

/*
 * calculates the Chebyshev distance of two input vectors, based on the wikipedia formula.
 * @param v1 and v2 are input float vectors.
 * @return float representing Chebyshev distance result
 */
float chebyshevDistance(vector <float> v1, vector <float> v2) {
    vector <float> sabtructedVec  = vectorSubtraction(v1, v2);
    float max = sabtructedVec.at(0);   //init with first element in vector
    for (int i = 0; i < sabtructedVec.size(); i++)    {
        if (sabtructedVec.at(i) > max) {
            max = sabtructedVec.at(i); 
        } 
    }
    return max;
}

/*
 * calculates the Canberra distance of two input vectors, based on the wikipedia formula.
 * @param v1 and v2 are input float vectors.
 * @return float representing Canberra distance result
 */
float canberraDistance(vector <float> v1, vector <float> v2) {
    vector<float> numerator, denominator, resultVector;
    numerator = vectorAbsolute(vectorSubtraction(v1, v2));
    denominator = vectorAddition(vectorAbsolute(v1), vectorAbsolute(v2));
    if (vectorSum(denominator) == 0) {
        // -1 will indicate something went wrong, because distance will always be not negative.
        return (static_cast<float>(-1));
    }
    for (int i = 0; i < v1.size(); i++) {
        resultVector.push_back(numerator.at(i) / denominator.at(i));
    }
    return vectorSum(resultVector);

}

/*
 * calculates the Minkowski distance of two input vectors, based on the wikipedia formula.
 * @param v1 and v2 are input float vectors.
 * @return float representing Minkowski distance result
 */
float minkowskiDistance(vector <float> v1, vector <float> v2) {
    const double p = 1;
    float sum = vectorSum(vectorRaiseToPower(vectorAbsolute(vectorSubtraction(v1, v2)), p));
    return(pow(sum, 1 / p));

}
