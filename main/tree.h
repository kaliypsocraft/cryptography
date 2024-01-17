#ifndef TREE_H
#define TREE_H

#include <string>

template <typename T>
class Node {
    public:
        T data;
        Node* parent;
        Node* left;
        Node* right;

        Node(T data) {
            this->data = data;
            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
        }
};


#endif