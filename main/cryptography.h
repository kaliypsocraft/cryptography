#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <vector>

using namespace std;
// some declarations in
// the header file
class xorCipher {
    public:
        vector<int> encrypt(const string&);
        void decipher(vector<int> cipher);
};
class ROT13 {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
};
class polyAlphabeticCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
    private:
        string formatKey(const string&, const string&);
};
class columnarCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
};
#endif