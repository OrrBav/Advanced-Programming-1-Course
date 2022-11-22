#include <math.h>
#include <iostream>
#include <vector>
#include "function.h"
using namespace std;

/*
 *  returns the subtraction result of the 2 input vectors
 */
vector <float> vectorSubtraction(vector <float> v1, vector <float> v2) {

    vector <float> v3;  // the output vetor
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) - v2.at(i)) ;
    }
    return v3;
}

/*
 * returns the vector after each element was raised to the power of toThePowerOf.
 * toThePowerOf default value is 2.
 */
vector <float> vectorRaiseToPower(vector <float> vector, double toThePowerOf) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = pow(vector.at(i),toThePowerOf);
     }
    return vector;
}

/*
 *  sums all the elements in the vector and perform square root on the sum.
 *  return - the squared root of the sum of elements in input vector.
 */
float vectorSquareRoot(vector <float> vector) {
     
    float vectorSquarred = sqrt(vectorSum(vector));
    return vectorSquarred;
}

/*
 * returns the vector with the absolute value of each input vector element.
 */
vector <float> vectorAbsolute(vector <float> vector) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = abs(vector.at(i));
     }
    return vector;
}

/*
 * returns the float sum of input vector.
 * input - input vector.
 */
float vectorSum(vector <float> vector) {
     float sum = 0;
     for (int i = 0; i < vector.size(); i++) {
       sum += vector.at(i);
     }
    return sum;
}

/*
 * creates a new vector, which each element is the result of addition of the corresponding elements in input vectors.
 * input - two vectors containing float elements.
 */
vector <float> vectorAddition(vector <float> v1, vector <float> v2) {
    vector <float> v3;  // the output vetor
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) + v2.at(i));
    }
    return v3;
}
