#include "function.h"
using namespace std;

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
 *  @param vectorSquarred is the float result
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
