#include "AVLTree.h"

#include <algorithm>
#include <cstdint>

AVLNode::AVLNode(int32_t value) {
    this->value = value;
    this->left= this->right = nullptr;
    this->height = 1;
}

AVLNode::~AVLNode() = default;

AVLTree::AVLTree() {
    this->root_ = nullptr;
    this->size_ = 0;
}

AVLTree::AVLTree(int32_t value) {
    this->root_ = new AVLNode(value);
    this->size_ = 1;
}

int32_t AVLTree::getHeight() {
    return getNodeHeight(this->root_);
}

void AVLTree::insert(int32_t value) {
    this->root_ = insertNode(this->root_, value);
}

void AVLTree::erase(int32_t value) {
    this->root_ = removeNode(this->root_, value);
}

int32_t *AVLTree::find(int32_t value) {
    AVLNode* foundNode = findNode(this->root_, value);

    return foundNode == nullptr ? nullptr : &foundNode->value;
}

int32_t *AVLTree::traversal() {
    int32_t * verticesArray = new int[this->size_];
    int* idx = new int(0);
    traversalInternal(this->root_, verticesArray, idx);
    return verticesArray;
}

int32_t *AVLTree::lowerBound(int32_t value) {
    AVLNode* lowerBoundNode = lowerBoundInternal(this->root_, value);

    return (lowerBoundNode == nullptr ? nullptr : &(lowerBoundNode->value));
}

bool AVLTree::empty() {
    return this->root_ == nullptr;
}

AVLNode *AVLTree::getRoot() {
    return this->root_;
}

int32_t AVLTree::getSize() {
    return this->size_;
}

AVLTree::~AVLTree() = default;

int32_t AVLTree::getNodeHeight(AVLNode *node) {
    return node == nullptr ? 0 : node->height;
}

int32_t AVLTree::balanceFactor(AVLNode *node) {
    return node == nullptr ? 0 : getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(AVLNode *node) {
    if (node != nullptr) {
        node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
    }
}

AVLNode *AVLTree::rotateRight(AVLNode *node) {
    AVLNode* newRoot = node->left;

    node->left = newRoot->right;
    newRoot->right = node;

    balanceHeight(node);
    balanceHeight(newRoot);

    return newRoot;
}

AVLNode *AVLTree::rotateLeft(AVLNode *node) {
    AVLNode* newRoot = node->right;

    node->right = newRoot->left;
    newRoot->left = node;

    balanceHeight(node);
    balanceHeight(newRoot);

    return newRoot;
}

AVLNode *AVLTree::balanceNode(AVLNode *node) {
    balanceHeight(node);

    int32_t nodeBalanceFactor = balanceFactor(node);

    if (nodeBalanceFactor > 1) {
        if (balanceFactor(node->left) >= 0) {
            node = rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    } else if (nodeBalanceFactor < -1) {
        if (balanceFactor(node->right) <= 0) {
            node = rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }

    return node;
}

AVLNode *AVLTree::insertNode(AVLNode *node, int32_t value) {
    if (node == nullptr) {
        this->size_++;
        return new AVLNode(value);
    }

    if (node->value == value) {
        return node;
    } else if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }

    node = balanceNode(node);

    return node;
}

AVLNode *AVLTree::findMinNode(AVLNode *node) {
    AVLNode* curNode = node;
    while (curNode->left != nullptr) {
        curNode = curNode->left;
    }
    return curNode;
}

AVLNode *AVLTree::removeMinNode(AVLNode *node) {
    AVLNode* minNode = findMinNode(node);

    if (minNode != nullptr) {
        erase(minNode->value);
    }

    return node;
}

AVLNode *AVLTree::removeNode(AVLNode *node, int32_t value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* tmp = node->left != nullptr ? node->left : node->right;
            if (tmp == nullptr) {
                tmp = node;
                node = nullptr;
            } else {
                *node = *tmp;
            }
            delete tmp;
        } else {
            AVLNode* tmp = findMinNode(node->right);
            node->value = tmp->value;
            node->right = removeNode(node->right, tmp->value);
        }
    }


    if (node == nullptr) {
        this->size_--;
        return node;
    }

    node = balanceNode(node);

    return node;
}

AVLNode *AVLTree::findNode(AVLNode *node, int32_t value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value == value) {
        return node;
    }
    if (value < node->value) {
        return findNode(node->left, value);
    }
    if (value > node->value) {
        return findNode(node->right, value);
    }

    return nullptr;
}

void AVLTree::traversalInternal(AVLNode *node, int32_t *array, int32_t *index) {
    if (node != nullptr) {
        traversalInternal(node->left, array, index);
        array[*index] = node->value;
        (*index)++;
        traversalInternal(node->right, array, index);
    }
}

AVLNode *AVLTree::lowerBoundInternal(AVLNode *current, int32_t value) const {
    if (current == nullptr) {
        return nullptr;
    }

    if (current->value == value) {
        return current;
    }
    if (current->value < value) {
        return lowerBoundInternal(current->right, value);
    }

    AVLNode* tmpNode = lowerBoundInternal(current->left, value);
    if (tmpNode != nullptr) {
        return tmpNode;
    } else {
        return current;
    }
}