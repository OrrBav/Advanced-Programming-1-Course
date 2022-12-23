//
// Created by orrbb on 07/12/2022.
//

#include "knn.h"

/*
 * Constructor for knn class.
 * @param k - integer, number of neighbors we wil use in the KNN algorithm.
 * @param funcName - a string representation of the distance function KNN class will use in its calculations.
 * @param x_vector - a 2D vector with float values. we will "train" on it, and compute distance to the x_test vector.
 * @param y_vector - corresponding labels to x_vector.
 */
Knn::Knn(int k, string funcName, vector<vector<float>> &x_vector, vector <string> &y_vector)
        : disFun(funcName) {
    this->k = k;
    x_train = x_vector;
    y_train = y_vector;
}

/*
 * main function of KNN class. will get the x_test vector, and will compute distance for each row (or sample) in
 * x_train. it will save it in a vector of pairs predictVector, where each distance will have the corresponding label.
 * @param x_test - vector of floats we wish to determine its label. User's input from main.
 * @return - string of the predicted label.
 */
string Knn::predict (vector <float> x_test ) {
    vector <pair <float, string> > predictVector;
    float distance = 0;
    string label = "";
    for (int i = 0; i < this->x_train.size(); i++) {
        distance = this->disFun.calc_distance(x_train[i], x_test);
        label = y_train[i];
        predictVector.push_back(make_pair(distance, label));
    }
    sort(predictVector.begin(), predictVector.end());
    return Knn::commonLabel(predictVector);
}

/*
 * function will get predictVector, initialized in predict function, and will determine the most common label from the
 * K values it holds. For that end, we will create a predictMap, which will hold label and its total appearances in
 * predictVector.
 * @predictVector - pair vector of labels and distance according to Knn's distance function.
 * @return - string of the predicted label.
 */
string Knn::commonLabel(vector <pair<float, string>> predictVector) {
    map<string, float> predictMap;
    string label;
    for (int i = 0; i < this->k; i++) {
        label = predictVector[i].second;
        if (predictMap.count(predictVector[i].second) == 1) {       // label already in predictMap
            predictMap[label] += 1;
        } else {                                                    // map does not contain label
            predictMap[label] = 1;
        }
    }
    string commonLabel;
    int maxCount = 0;
    // will iterate over map, go get the most common label.
    for (const auto& kv : predictMap) {
        if (kv.second > maxCount) {
            maxCount = kv.second;
            commonLabel = kv.first;
        }
    }
    return commonLabel;
}
