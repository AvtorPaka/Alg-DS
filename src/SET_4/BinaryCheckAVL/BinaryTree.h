#ifndef IMPLEMENTATIONDATA_BINARYTREE_H
#define IMPLEMENTATIONDATA_BINARYTREE_H

#include <cstdint>

struct Node {
public:
    int32_t key;
    Node *left;
    Node *right;

    Node(int32_t key, Node *right = nullptr, Node *left = nullptr) {
        this->key = key;
        this->right = right;
        this->left = left;
    }

    ~Node() = default;
};

// Binary Tree with check for AVL accuracy
class BinaryTree {
private:
    Node *Insert(Node *curNode, const int32_t &newKey);

    int32_t MaxDepthFromNode(Node *curNode, int32_t curDepth) const;

public:
    Node *root;

    BinaryTree();

    BinaryTree(const int32_t &key);

    void Insert(const int32_t &newKey);

    bool IsAVL(Node *rootNode) const;
};

#endif //IMPLEMENTATIONDATA_BINARYTREE_H
