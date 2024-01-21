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
class MerkleProof {
    public:
        string hash;
        string direction;
};

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
        
        vector<MerkleProof<T>> generateMerkleProof(int src, vector<vector<MerkleNode<T>>>);
        vector<vector<MerkleNode<T>>> initialProtocol(vector<T> leaves);
        vector<vector<MerkleNode<T>>> generateMerkleTree(vector<vector<MerkleNode<T>>> merkleTree, vector<T>);
        bool validate(vector<MerkleProof<T>> nodes);
};

/// @brief 
/// @tparam T 
/// @param data 
/// @param direction 
/// @param hash 
template <typename T>
MerkleNode<T>::MerkleNode(string data, string direction, T hash) {
    this->direction = direction;
    this->data = data;
    this->hash = hash;
}

/// @brief Function as produced by Jonathan Drapeua on StackOverflow
/// @param str 
/// @return 
string sha256(const string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.size(), hash);
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

/// @brief 
/// @tparam T 
/// @param leaves 
/// @return 
template <typename T>
vector<vector<MerkleNode<T>>> MerkleTree<T>::initialProtocol(vector<T> leaves) {
    vector<T> hashes;
    vector<vector<MerkleNode<T>>> MT;

    for (const auto& input : leaves) {
        hashes.push_back(sha256(input));
    }
    
    MT = generateMerkleTree(MT, hashes);

    /*
    for (vector<MerkleNode<T>> layer : MT) {
        cout << "This layer has " << layer.size() << " elems" << "\n";
        for (MerkleNode<T> elem : layer) {
            cout << "[ Direction: " << elem.direction << " Hash: " << elem.hash <<  " ]";
        }
        cout << "\n";
    }
    */
    cout << "The root hash is " << root << "\n";
    return MT;
}

/// @brief 
/// @tparam T 
/// @param  
template <typename T>
void printNode(MerkleNode<T> node) {
    cout << "[ " << node.data  << " ]" << '\n';
    cout << "[ " << node.hash  << " ]" << '\n';
    cout << "[ " << node.direction << " ]" << '\n';
}

/// @brief 
/// @param index 
/// @return 
string getDirection(int index) {
    return index % 2 ? "Right" : "Left";
}

/// @brief 
/// @tparam T 
/// @param src 
/// @param MT 
/// @param proof 
/// @return 
template <typename T>
vector<MerkleProof<T>> MerkleTree<T>::generateMerkleProof(int src, vector<vector<MerkleNode<T>>> MT) {
    vector<MerkleProof<T>> proofList;

    // Layer 0 is the base of the tree
    MerkleNode<T> currNode = MT[0][src];
    MerkleProof<T> proof;
    int hashIndex = src;
    
    for (int i = 1; i < MT.size(); i++) {
        proof.hash = currNode.hash;
        proof.direction = currNode.direction;
        
        hashIndex = (hashIndex / 2) % 2 ? hashIndex - 1 : hashIndex + 1;

        currNode = MT[i][hashIndex];
        proofList.push_back(proof);
    }

    return proofList;
}

/// @brief 
/// @tparam T 
/// @param hashes 
/// @return 
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

/// @brief 
/// @tparam T 
/// @param input 
/// @return 
template <typename T>
bool MerkleTree<T>::validate(vector<MerkleProof<T>> input) {
    string combinedHash = "";
    for (int i = 0; i < input.size(); i += 2) {
        combinedHash = sha256(input[i] + input[i + 1]);
        //cout << "Hashing: " << input[i] << " and " << input[i + 1] << " =  " <<  sha256(input[i] + input[i + 1]) << "\n" ;
        input.push_back(combinedHash);
    }
    //cout << combinedHash << "\n";
    return combinedHash == this->root;
}


#endif