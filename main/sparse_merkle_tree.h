#ifndef SPARSE_MERKLE_TREE_H
#define SPARSE_MERKLE_TREE_H

#include <iostream>
#include <optional>
#include <openssl/sha.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

#include "node_factory.h"

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

class SMT {
    public:
        string rootHash;
        int treeDepth;
        vector<MerkleNode> nodes;

        // Key is typically the ethereum node's address
        unordered_map<int, string> hashCache;
        // Cache is store "default" node hashes
        // Pre-compute all leaf nodes's hashes
        unordered_map<int, string> defaultCache;

        SMT(int depth);
        string commit(unordered_map<int, MerkleNode> M);
        string applyOp(Operation op, MerkleNode node);
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
        /// @brief 
        /// @param defaultCache 
        /// @param elements 
        void generateDefaultValues(unordered_map<int, string> &defaultCache) {
            int numOfBaseLayerNodes = pow(2, this->treeDepth);
            int beginIndex = numOfBaseLayerNodes - 1;
            for (int i = 0; i < numOfBaseLayerNodes; i++) {
                defaultCache.insert({beginIndex++, hasher(to_string(defaultVal + beginIndex))});
            }
        }
};


int capacity(int depth) {
    return (1 << (depth + 1)) - 1;
}

/// @brief 
/// @param depth 
SMT::SMT(int depth) {
    this->treeDepth = depth;
    unordered_map<int, string> defaultCache;
    generateDefaultValues(defaultCache);

    this->defaultCache = defaultCache;
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
string SMT::applyOp(Operation op, MerkleNode node) {
    
    string rootHash = "";
    switch (op) {
        case INSERT:
            break;
        case REMOVE:
            
            break;
        case UPDATE:
            
            break;
        default:
            cout << "Unknown selection.\n";
            break;
    }
    return rootHash;
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