#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <vector>
#include <limits>

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

class SubstitutionCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
    private:
        string formatKey(const string&, int);
};
class RSA {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
    private:
        //long long privateKey = INT_MAX;
        //long long publicKey = INT_MAX;
        
        void generatePublicKey(int);
        void generatePrivateKey(int, long long);
};

class ColumnarCipher {
    public:
        string encrypt(const string&);
        string decrypt(const string&);
    private:
        vector<vector<char>> generateColumnar(const string&, int, int);
        vector<vector<char>> generateDecryption(const string&, int, int);
        void getOrdering(int*);
};
class DiffieHellman {
    public: 
        long long encrypt(const string&);
        string decrypt(const string&);
    private:
        int alice_public_key;
        int alice_private_x;
        int bob_private_y;
        int bob_public_key;
};
#endif