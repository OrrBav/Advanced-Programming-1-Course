
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;


// returns the sabstruction result of the 2 input vectors
vector <float> vectorSubstruction(vector <float> v1, vector <float> v2) {

    vector <float> v3;  // the output vetor
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) - v2.at(i)) ;
    }
    return v3;
}

// returns the vector after each elemnt was raised to the power of toThePowerOf
vector <float> vectorRaiseToPower(vector <float> vector, double toThePowerOf = 2) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = pow(vector.at(i),toThePowerOf);
     }
    return vector;
}

// sums all the elements in the vector and perform square root on the sum
float vectorSquareRoot(vector <float> vector) {
     
    float vectorSquarred = sqrt(vectorSum(vector));
    return vectorSquarred;
}

// returns the vector with the absolute value of each elemnt
vector <float> vectorAbsolute(vector <float> vector) {
     
     for (int i = 0; i < vector.size(); i++) {
       vector.at(i) = abs(vector.at(i));
     }
    return vector;
}

// returns the sum of input vector
float vectorSum(vector <float> vector) {
     float sum = 0;
     for (int i = 0; i < vector.size(); i++) {
       sum += vector.at(i);
     }
    return sum;
}


// returns the addition of 2 input vectors 
vector <float> vectorAddition(vector <float> v1, vector <float> v2) {
    vector <float> v3;  // the output vetor
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) + v2.at(i));
    }
    return v3;
}
