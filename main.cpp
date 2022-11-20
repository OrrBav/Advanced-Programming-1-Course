// Created by orrbb on 20/11/2022.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string check(string s1, vector <float> numbers) {
    string test;
    int i = 0;
    for (i; i < s1.length(); i++) {
        if (s1[i] == '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' ) {
            test
        }
    }
}

int main()
{
    string input1;
    vector <string> numbers;
    while (getline(cin, input1, ' ')) {
        if (input1 == "\n")
            numbers.push_back(input1);

    }
    //cout << "Output of begin and end: ";
    //for (auto i = numbers.begin(); i != numbers.end(); ++i)
    //    cout << *i << " ";
}

