#ifndef IMPLEMENTATIONDATA_BINARYTREE_H
#define IMPLEMENTATIONDATA_BINARYTREE_H

#include <cstdint>

struct BSTNode {
public:
    int32_t key;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int32_t key, BSTNode *right = nullptr, BSTNode *left = nullptr) {
        this->key = key;
        this->right = right;
        this->left = left;
    }

    ~BSTNode() = default;
};

// Binary Tree with check for AVL accuracy
class BinaryTree {
private:
    BSTNode *Insert(BSTNode *curNode, const int32_t &newKey);

    int32_t MaxDepthFromNode(BSTNode *curNode, int32_t curDepth) const;

public:
    BSTNode *root;

    BinaryTree();

    BinaryTree(const int32_t &key);

    void Insert(const int32_t &newKey);

    bool IsAVL(BSTNode *rootNode) const;
};

#endif //IMPLEMENTATIONDATA_BINARYTREE_H
