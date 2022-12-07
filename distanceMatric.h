//
// Created by orrbb on 07/12/2022.
//
using namespace std;

#ifndef ADVANCED_PROGRAMMING_1_DISTANCEMATRIC_H
#define ADVANCED_PROGRAMMING_1_DISTANCEMATRIC_H
#include <string>
#include <vector>

class DistanceMetric {
    string dis_fun;
public:
    DistanceMetric(string funcName);
    float calc_distance(vector <float> v1, vector <float> v2);
};


#endif //ADVANCED_PROGRAMMING_1_DISTANCEMATRIC_H
