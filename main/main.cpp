#include <iostream>
#include "cryptography.h"

using namespace std;

int main() {
    string message;
    cout << "Enter the intended message: ";
    getline(cin, message);
    vector<int> cipher = xorCipher(message);
    cout << "Enciphered: ";
    for (const auto& elem : cipher) {
        cout << char(elem % 127); 
    }
    cout << endl;
    return 0;
}