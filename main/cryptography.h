#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <vector>

using namespace std;
// some declarations in
// the header file
class XorCipher {
    public:
        vector<int> encrypt(const string&);
        void decrypt(vector<int> cipher);
};
class ROT13 {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
};
class PolyAlphabeticCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
    private:
        string formatKey(const string&, const string&);
};
class ColumnarCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
        vector<vector<char>> generateColumnar(const string&, int, int);
};
#endif