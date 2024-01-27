#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H

#include <string>
#include <optional>
#include <openssl/sha.h>
#include <iomanip>


using namespace std;

/// @brief A hash function utilising SHA256 
/// @param data 
/// @return 
string hasher(const string data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.size(), hash);
    stringstream hashDigest;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)  {
        hashDigest << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return hashDigest.str();
}


class MerkleNode {
    public:
        string hash;
        string balance;
        // Incremeneted every transaction (NOTIONAL nonce here)
        string nonce;
        optional<MerkleNode*> leftChild;
        optional<MerkleNode*> rightChild;
        int nodeIndex;

        MerkleNode(string, string, string, int);
};

/// @brief 
/// @param  
/// @param  
/// @param  
/// @param  
MerkleNode::MerkleNode(string nonce, string balance, string hash, int index) {
    this->nonce = nonce;
    this->balance = balance;
    this->hash = hasher(nonce + balance + hash);
    this->nodeIndex = index;
}

MerkleNode createNode() {
    
    MerkleNode node();

}


#endif