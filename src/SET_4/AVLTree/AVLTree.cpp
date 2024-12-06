#include "AVLTree.h"

#include <algorithm>
#include <cstdint>

Node::Node(int32_t value) {
    this->value = value;
    this->left= this->right = nullptr;
    this->height = 1;
}

Node::~Node() = default;

AVLTree::AVLTree() {
    this->root_ = nullptr;
    this->size_ = 0;
}

AVLTree::AVLTree(int32_t value) {
    this->root_ = new Node(value);
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
    Node* foundNode = findNode(this->root_, value);

    return foundNode == nullptr ? nullptr : &foundNode->value;
}

int32_t *AVLTree::traversal() {
    int32_t * verticesArray = new int[this->size_];
    int* idx = new int(0);
    traversalInternal(this->root_, verticesArray, idx);
    return verticesArray;
}

int32_t *AVLTree::lowerBound(int32_t value) {
    Node* lowerBoundNode = lowerBoundInternal(this->root_, value);

    return (lowerBoundNode == nullptr ? nullptr : &(lowerBoundNode->value));
}

bool AVLTree::empty() {
    return this->root_ == nullptr;
}

Node *AVLTree::getRoot() {
    return this->root_;
}

int32_t AVLTree::getSize() {
    return this->size_;
}

AVLTree::~AVLTree() = default;

int32_t AVLTree::getNodeHeight(Node *node) {
    return node == nullptr ? 0 : node->height;
}

int32_t AVLTree::balanceFactor(Node *node) {
    return node == nullptr ? 0 : getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node *node) {
    if (node != nullptr) {
        node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
    }
}

Node *AVLTree::rotateRight(Node *node) {
    Node* newRoot = node->left;

    node->left = newRoot->right;
    newRoot->right = node;

    balanceHeight(node);
    balanceHeight(newRoot);

    return newRoot;
}

Node *AVLTree::rotateLeft(Node *node) {
    Node* newRoot = node->right;

    node->right = newRoot->left;
    newRoot->left = node;

    balanceHeight(node);
    balanceHeight(newRoot);

    return newRoot;
}

Node *AVLTree::balanceNode(Node *node) {
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

Node *AVLTree::insertNode(Node *node, int32_t value) {
    if (node == nullptr) {
        this->size_++;
        return new Node(value);
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

Node *AVLTree::findMinNode(Node *node) {
    Node* curNode = node;
    while (curNode->left != nullptr) {
        curNode = curNode->left;
    }
    return curNode;
}

Node *AVLTree::removeMinNode(Node *node) {
    Node* minNode = findMinNode(node);

    if (minNode != nullptr) {
        erase(minNode->value);
    }

    return node;
}

Node *AVLTree::removeNode(Node *node, int32_t value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* tmp = node->left != nullptr ? node->left : node->right;
            if (tmp == nullptr) {
                tmp = node;
                node = nullptr;
            } else {
                *node = *tmp;
            }
            delete tmp;
        } else {
            Node* tmp = findMinNode(node->right);
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

Node *AVLTree::findNode(Node *node, int32_t value) {
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

void AVLTree::traversalInternal(Node *node, int32_t *array, int32_t *index) {
    if (node != nullptr) {
        traversalInternal(node->left, array, index);
        array[*index] = node->value;
        (*index)++;
        traversalInternal(node->right, array, index);
    }
}

Node *AVLTree::lowerBoundInternal(Node *current, int32_t value) const {
    if (current == nullptr) {
        return nullptr;
    }

    if (current->value == value) {
        return current;
    }
    if (current->value < value) {
        return lowerBoundInternal(current->right, value);
    }

    Node* tmpNode = lowerBoundInternal(current->left, value);
    if (tmpNode != nullptr) {
        return tmpNode;
    } else {
        return current;
    }
}