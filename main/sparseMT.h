#ifndef sparseMT_H
#define sparseMT_H

#include <optional>
#include <openssl/sha.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int defaultVal = 0;

enum NodeDirection {
    LEFT,
    RIGHT,
};

enum Operation {
    INSERT,
    REMOVE,
    UPDATE,
};
class Witness {
    public:
        vector<MerkleNode> proof;
};

class MerkleNode {
    public:
        string hash;
        string data;
        optional<MerkleNode*> leftChild;
        optional<MerkleNode*> rightChild;
        int nodeIndex;

        MerkleNode(string, string, string, int);
        string hasher(const string str);
};

class SMT {
    public:
        string rootHash;
        int treeDepth;
        vector<MerkleNode> nodes;
        vector<string> hashCache;
        // Cache is store "default" node hashes
        // Pre-compute all leaf nodes's hashes
        vector<string> defaultCache;

        SMT(int depth);
        string commit(unordered_map<int, MerkleNode> M);
        string applyOp(Operation op, int memberIndex);
        Witness memberWitnessCreate(int memberIndex);
        bool memberVerify(Witness, int memberIndex);
    private:
        /// @brief Inserts 
        /// @param memberIndex 
        /// @return 
        string insertOp(MerkleNode leaf) {
            return "";
        }
        string removeOp(int index) {
            return "";
        }
        string updateOp(MerkleNode updatedLeaf, int index) {
            return "";
        }
};

int capacity(int depth) {
    return (1 << (depth + 1)) - 1;
}

/// @brief 
/// @param  
/// @param  
/// @param  
/// @param  
MerkleNode::MerkleNode(string, string, string, int) {

}
/// @brief 
/// @param depth 
SMT::SMT(int depth) {
    this->treeDepth = depth;
}
/// @brief A hash function utilising SHA256 
/// @param data 
/// @return 
string MerkleNode::hasher(const string data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.size(), hash);
    stringstream hashDigest;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)  {
        hashDigest << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return hashDigest.str();
}

/// @brief From a map we create a tree from the bottom-up
/// @param M 
/// @return the root hash
string SMT::commit(unordered_map<int, MerkleNode> M) {
    return "";
}

/// @brief Applies the operation 'op' on member 'memberIndex'
/// @param op 
/// @param memberIndex 
/// @return 
string SMT::applyOp(Operation op, int memberIndex) {
    return "";
}


/// @brief 
/// @param memberIndex 
/// @return 
Witness SMT::memberWitnessCreate(int memberIndex) {

    return Witness();
}

/// @brief 
/// @param  
/// @param memberIndex 
/// @return 
bool SMT::memberVerify(Witness, int memberIndex) {

    return true;
}

#endif