#include <iostream>
#include "cryptography.h"

using namespace std;

int main() {
    vector<int> cipher = xorCipher("hello!!");
    for (const auto& elem : cipher) {
        cout << char(elem % 127); 
    }
    cout << endl;
    return 0;
}