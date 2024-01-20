#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <string>


using namespace std;

template <typename T>
class MerkleTree {
    public:
        T data;
        string nId;
        string direction;

        vector<T> init_protocol(vector<T> leaves);
        vector<vector<T>> generateMerkleTree(vector<T>);
        T generateMerkleRoot(vector<T>);
};

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)  {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

template <typename T>
vector<T> MerkleTree<T>::init_protocol(vector<T> leaves) {
    vector<T> hashes;
    for (const auto& input : leaves) {
        hashes.push_back(sha256(input));
    }
    for (const auto& hash : hashes) {
        std::cout<< "[ " << hash << " ]" << "\n";
    }
    return hashes;
}
/// @brief false is LEFT true is RIGHT
/// @return 
std::string getDirection() {

}
/// @brief From the leaf nodes we traverse upwards towards the root and then return the root
/// @tparam T 
/// @param hashes 
/// @return 
template <typename T>
vector<vector<T>> MerkleTree<T>::generateMerkleTree(vector<T> hashes) {

}
       
/// @brief From the leaf nodes we traverse upwards towards the root and then return the root
/// @tparam T 
/// @param hashes 
/// @return 
template <typename T>
T MerkleTree<T>::generateMerkleRoot(vector<T> hashes) {

}

#endif