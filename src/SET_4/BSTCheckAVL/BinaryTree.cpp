#include "BinaryTree.h"

#include <cmath>
#include <algorithm>

BSTNode *BinaryTree::Insert(BSTNode *curNode, const int32_t &newKey)  {
    if (curNode == nullptr) {
        curNode = new BSTNode(newKey);
    } else if (newKey < curNode->key) {
        curNode->left = Insert(curNode->left, newKey);
    } else if (newKey > curNode->key) {
        curNode->right = Insert(curNode->right, newKey);
    }

    return curNode;
}

int32_t BinaryTree::MaxDepthFromNode(BSTNode *curNode, int32_t curDepth) const {
    if (curNode == nullptr) {
        return curDepth - 1;
    }
    int32_t maxLeftDepth = MaxDepthFromNode(curNode->left, curDepth + 1);
    int32_t maxRightDepth = MaxDepthFromNode(curNode->right, curDepth + 1);
    int32_t maxLocalDepth = std::max(maxLeftDepth, maxRightDepth);

    return maxLocalDepth;
}

bool BinaryTree::IsAVL(BSTNode *rootNode) const {
    if (rootNode == nullptr) {
        return true;
    }
    int32_t leftDepth = MaxDepthFromNode(rootNode->left, 1);
    int32_t rightDepth = MaxDepthFromNode(rootNode->right, 1);

    return (abs(rightDepth - leftDepth) <= 1 && IsAVL(rootNode->left) && IsAVL(rootNode->right));
}

void BinaryTree::Insert(const int32_t &newKey)  {
    this->root = Insert(this->root, newKey);
}

BinaryTree::BinaryTree(const int32_t &key)  {
    this->root = new BSTNode(key);
}

BinaryTree::BinaryTree() {
    this->root = nullptr;
}
