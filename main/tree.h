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
class MerkleNode {
    public:
        T hash;
        string data;
        string direction;

        MerkleNode(string, string, T);
};

template <typename T>
class MerkleTree {
    public:
        string root;

        vector<MerkleNode<T>> init_protocol(vector<T> leaves);
        vector<vector<MerkleNode<T>>> generateMerkleTree(vector<vector<MerkleNode<T>>>, vector<T>);
        T generateMerkleRoot(vector<T>);
        bool validate(vector<T> nodes);
};


template <typename T>
MerkleNode<T>::MerkleNode(string data, string direction, T hash) {
    this->direction = direction;
    this->data = data;
    this->hash = hash;
}
/// @brief Function as produced by Jonathan Drapeua on StackOverflow
/// @param str 
/// @return 
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
/// @brief Optional function to ensure evenness at each layer
/// @tparam T 
/// @param hashes 
template <typename T>
void ensureEven(vector<T> &hashes) {
    int length = hashes.size();
    if (length % 2 != 0 && length > 1) {
        hashes.push_back(sha256(hashes[length - 1]));
    }  
}

template <typename T>
vector<MerkleNode<T>> MerkleTree<T>::init_protocol(vector<T> leaves) {
    vector<T> hashes;
    vector<vector<T>> MT;
    for (const auto& input : leaves) {
        hashes.push_back(sha256(input));
    }
    MT = generateMerkleTree(MT, hashes);
    for (vector<T> layer : MT) {
        cout << "This layer has " << layer.size() << " elems" << "\n";
        for (T elem : layer) {
            cout << elem << " | ";
        }
        cout << "\n";
    }

    cout << "The root hash is " << root << "\n";
    return hashes;
}
string getDirection(int index) {
    return index % 2 == 0 ? "LEFT" : "RIGHT";
}

template <typename T>
vector<MerkleNode<T>> generateNodes(vector<T> hashes) {
    int length = hashes.size();
    vector<MerkleNode<T>> merkleRow;
    for (int i = 0; i < length; i++) {
        MerkleNode<T> node("N/A", getDirection(i), hashes[i]);
        merkleRow.push_back(node);
    }
    return merkleRow;
}

/// @brief From the leaf nodes we traverse upwards towards the root and then return the root
/// @tparam T 
/// @param hashes 
/// @return 
template <typename T>
vector<vector<MerkleNode<T>>> MerkleTree<T>::generateMerkleTree(vector<vector<MerkleNode<T>>> MT, vector<T> hashes) {
    vector<T> combinedHashes;
    ensureEven(hashes);
    MT.push_back(generateNodes(hashes));
    for (int i = 0; i < hashes.size(); i += 2) {
        string concated = hashes[i] + hashes[i + 1];
        combinedHashes.push_back(sha256(concated));
    }
    if (hashes.size() > 1) {
        return generateMerkleTree(MT, combinedHashes);
    }
    this->root = hashes[0];
    return MT;
}

template <typename T>
bool MerkleTree<T>::validate(vector<T> input) {
    string combinedHash = "";
    for (int i = 0; i < input.size(); i += 2) {
        combinedHash = sha256(input[i] + input[i + 1]);
        //cout << "Hashing: " << input[i] << " and " << input[i + 1] << " =  " <<  sha256(input[i] + input[i + 1]) << "\n" ;
        input.push_back(combinedHash);
    }
    //cout << combinedHash << "\n";
    return combinedHash == this->root;
}

/// @brief From the leaf nodes we traverse upwards towards the root and then return the root
/// @tparam T 
/// @param hashes 
/// @return 
template <typename T>
T MerkleTree<T>::generateMerkleRoot(vector<T> hashes) {

}

#endif