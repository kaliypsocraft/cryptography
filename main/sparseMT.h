#ifndef sparseMT_H
#define sparseMT_H

#include <optional>
#include <openssl/sha.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

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
        optional<MerkleNode> leftChild;
        optional<MerkleNode> rightChild;
        int nodeIndex;

        MerkleNode(string, string, string, int);
        string hasher(const string str);
};

class SMT {
    public:
        int treeDepth;

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
string MerkleNode::hasher(const string data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.size(), hash);
    stringstream hashDigest;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)  {
        hashDigest << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return hashDigest.str();
}

/// @brief 
/// @param M 
/// @return 
string SMT::commit(unordered_map<int, MerkleNode> M) {

}

/// @brief 
/// @param op 
/// @param memberIndex 
/// @return 
string SMT::applyOp(Operation op, int memberIndex) {

}


/// @brief 
/// @param memberIndex 
/// @return 
Witness SMT::memberWitnessCreate(int memberIndex) {

}

/// @brief 
/// @param  
/// @param memberIndex 
/// @return 
bool SMT::memberVerify(Witness, int memberIndex) {

}

#endif