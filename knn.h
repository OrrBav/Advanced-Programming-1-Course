

#ifndef ADVANCED_PROGRAMMING_1_KNN_H
#define ADVANCED_PROGRAMMING_1_KNN_H
#include "distanceMatric.h"
#include <vector>
#include <map>
#include<bits/stdc++.h>

class Knn {
    int k;
    DistanceMetric disFun;
    vector<vector<float>> x_train;
    vector <string> y_train;
public:
    Knn(int k, string funcName, vector<vector<float>> &x_vector, vector <string> &y_vector);
    string predict (vector <float> x_test);
    string commonLabel(vector <pair <float, string> > predictVector);
};


#endif //ADVANCED_PROGRAMMING_1_KNN_H
