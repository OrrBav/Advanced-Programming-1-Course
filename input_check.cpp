//
// Created by orrbb on 21/11/2022.
//

#include <iostream>
#include <vector>
#include <string>


using namespace std;
/*
 * function should iterate over input string and check if input is valid.
 * if so - save as str
 */
vector <float> check(string input_str, vector <float>& numbers) {
    string new_num;
    char single_cut;
    bool space_flag = false;
    bool dot_flag = false;
    // finds if first and last char in string are digits, and ensures for loop logic
    if ((isdigit(input_str[0]) == false) || isdigit(input_str[input_str.length() - 1]) == false) {
        throw invalid_argument("input should be numbers separated by spaces.");
    }
    for (int i = 0; i < input_str.length(); i++) {
        if (isdigit(input_str[i]) == true) {
            // iterating over number, so space should be set to false
            space_flag = false;
            // converts input_srt[i] from char to string, and enables stof()
            single_cut = input_str[i];
            string string_cut {single_cut};
            new_num += string_cut;

        }
            // char is not a digit: can be space, dot (good) or other ABC (bad)
        else {
            // two consecutive spaces
            if (input_str[i] == ' ') {
                if (space_flag == true) {
                    throw invalid_argument("input should be numbers separated by spaces.");
                }
                    // prepare for a new valid number
                else {
                    space_flag = true;
                    dot_flag = false;
                    numbers.push_back(stof(new_num));
                    new_num = "";
                }
            }
                // char is dot - should be only one per number
            else if(input_str[i] == '.') {
                // there was already a dot in number
                if (dot_flag == true) {
                    throw invalid_argument("input should be numbers separated by spaces.");
                }
                else {
                    dot_flag = true;
                    new_num += ".";
                }
            }
                // invalid char
            else {
                throw invalid_argument("input should be numbers separated by spaces.");
            }
        }
    }
    numbers.push_back(stof(new_num));
    return numbers;
}