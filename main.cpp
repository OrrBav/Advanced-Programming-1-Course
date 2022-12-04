//Orr, Ariel
#include "function.h"

using namespace std;


int main()
{
    string str1, str2;
    vector<float> numbers1, numbers2;
    getline(cin, str1);
    check(str1, numbers1);
    getline(cin, str2);
    check(str2, numbers2);
    if (numbers1.size() != numbers2.size()) {
        cout << "inputs should have the same number of numbers" << endl;
        return -1;
    }

    print_decimal(euclideanDistance(numbers1, numbers2));
    print_decimal(manhattanDistance(numbers1, numbers2));
    print_decimal(chebyshevDistance(numbers1, numbers2));
    if (canberraDistance(numbers1, numbers2) == -1) {
        cout << "Canberra distance error: cannot divide by zero" << endl;
    }
    else {
        print_decimal(canberraDistance(numbers1, numbers2));
    }
    print_decimal(minkowskiDistance(numbers1, numbers2));
    return 0;

}
