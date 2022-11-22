// Created by orrbb on 20/11/2022.
#include <iostream>
#include <vector>
#include <string>
#include "function.h"

using namespace std;


int main()
{
    string str1, str2;
    vector<float> numbers1, numbers2;
    getline(cin, str1);
    try {
        check(str1, numbers1);
    }
    catch (invalid_argument& e) {
        cout << e.what() << endl;
        return -1;
    }
    getline(cin, str2);
    try {
        check(str2, numbers2);
    }
    catch (invalid_argument& e) {
        cout << e.what() << endl;
        return -1;
    }
    if (numbers1.size() != numbers2.size()) {
        cout << "inputs should have the same number of numbers";
        return -1;
    }

    print_decimal(euclideanDistance(numbers1, numbers2));
    print_decimal(manhattanDistance(numbers1, numbers2));
    print_decimal(chebyshevDistance(numbers1, numbers2));
    print_decimal(canberraDistance(numbers1, numbers2));
    print_decimal(minkowskiDistance(numbers1, numbers2));
    return 0;

}
