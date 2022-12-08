//
// Created by orrbb on 07/12/2022.
//

#include "knn.h"
#include <map>
#include<bits/stdc++.h>

Knn::Knn(int k, string funcName, vector<vector<float>> &x_vector, vector <string> &y_vector, DistanceMetric &disFun)
        : disFun(nullptr) {
    this->k = k;
    this->disFun = new DistanceMetric(funcName);
    x_train = x_vector;
    y_train = y_vector;
}

string Knn::predict (vector <float> x_test ) {
    vector <pair <float, string> > predictVector;
    float distance = 0;
    string label = "";
    for (int i = 0; i < this->x_train.size(); i++) {
        //         distance = this->disFun->calc_distance(reinterpret_cast<const vector<float> &>(x_train[i]), x_test);
        distance = this->disFun->calc_distance(x_train[i], x_test);
        label = y_train[i];
        predictVector.push_back(make_pair(distance, label));
    }
    sort(predictVector.begin(), predictVector.end());
    return Knn::commonLabel(predictVector);
}

string Knn::commonLabel(vector <pair<float, std::string>> predictVector) {
    map<string, float> predictMap;
    string label = "";
    for (int i = 0; i < this->k; i++) {
        label = predictVector[i].second;
        if (predictMap.count(predictVector[i].second) == 1) {       // label already in predictMap
            predictMap[label] += 1;
        } else {        // map does not contain label
            predictMap[label] = 1;
        }
    }
    string commonLabel = "";
    int maxCount = 0;
    // will iterate over map, go get the most common label.
    for (const auto& kv : predictMap) {
        if (kv.second > maxCount) {
            commonLabel = kv.first;
        }
    }
    return commonLabel;
}