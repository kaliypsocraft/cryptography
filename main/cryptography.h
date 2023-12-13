#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <vector>

using namespace std;
// some declarations in
// the header file
vector<int> xorCipher(const string&);
string ROT13(string&);
string autoCipher();
string columnarCipher(const string&);

#endif