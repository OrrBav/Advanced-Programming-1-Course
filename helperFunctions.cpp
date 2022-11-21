
#include <iostream>
#include <vector>
using namespace std;


vector <float> vectorSubstruction(vector <float> v1, vector <float> v2) {

    vector <float> v3;  // the output vetor
    for (int i = 0; i < v1.size(); i++) {
        v3.push_back(v1.at(i) - v2.at(i)) ;
    }
    return v3;
}


int main()
{
    vector <float> v1 = {-2,5,6,3};
    vector <float> v2 = {1,3,8,2};

    vector <float> substructedVector = vectorSubstruction(v1, v2);

    for (float i : substructedVector)
        std::cout << i << ' ';

}


