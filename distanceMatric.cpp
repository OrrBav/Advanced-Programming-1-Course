//
// Created by orrbb on 07/12/2022.
//

#include "distanceMatric.h"
#include "function.h"

DistanceMetric::DistanceMetric(string funcName) {
    dis_fun = funcName;
}

float DistanceMetric::calc_distance(vector <float> v1, vector <float> v2) {
    if (dis_fun == "AUC") {
        float eucDist = vectorSquareRoot(vectorRaiseToPower(vectorSubtraction(v1, v2)));
        return eucDist;
    } else if (dis_fun == "MAN") {
        float manDist = vectorSum(vectorAbsolute(vectorSubtraction(v1, v2)));
        return manDist;
    } else if (dis_fun == "CHB") {
        vector<float> sabtructedVec = vectorSubtraction(v1, v2);
        float max = sabtructedVec.at(0);   //init with first element in vector
        for (int i = 0; i < sabtructedVec.size(); i++) {
            if (sabtructedVec.at(i) > max) {
                max = sabtructedVec.at(i);
            }
        }
        return max;
    } else if (dis_fun == "CAN") {
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
    } else if (dis_fun == "MIN") {
        const double p = 1;
        float sum = vectorSum(vectorRaiseToPower(vectorAbsolute(vectorSubtraction(v1, v2)), p));
        return(pow(sum, 1 / p));
    }
    cout << ""    // represents an error
}