#include "btree.h"

#include <cstdint>
#include <vector>

int64_t leafSumInternal(Node *node);

void splitChildInternal(Node *node, int32_t idx, int32_t t);

void insertInternal(Node *node, int32_t key, int32_t t);

void deleteNodesCascade(Node *node);

bool containsInternal(Node *node, int32_t key);

Node::Node(int32_t t) {
    this->t = t;
    this->parent = nullptr;
    this->isLeaf = true;
    this->key.reserve(2 * t - 1);
    this->children.reserve(2 * t);
}

BTree::BTree(int32_t t) {
    this->t_ = t;
    this->root = new Node(t);
    this->size_ = 0;
}

BTree::~BTree() {
    deleteNodesCascade(this->root);
}

void BTree::insert(int32_t key) {
    if (!containsInternal(this->root, key)) {
        if (this->root->key.size() == this->t_ * 2 - 1) {
            Node *splitRoot = new Node(this->t_);

            splitRoot->isLeaf = false;
            splitRoot->children.push_back(this->root);
            this->root->parent = splitRoot;
            this->root = splitRoot;

            splitChildInternal(this->root, 0, this->t_);
            insertInternal(this->root, key, this->t_);
        } else {
            insertInternal(this->root, key, this->t_);
        }
        this->size_++;
    }
}

size_t BTree::size() const {
    return this->root == nullptr ? 0 : this->size_;
}

int64_t BTree::sum() const {
    return leafSumInternal(this->root);
}

void insertInternal(Node *node, int32_t key, int32_t t) {
    if (node->isLeaf) {
        int32_t insertIdx = 0;
        for (insertIdx = 0; insertIdx < node->key.size(); ++insertIdx) {
            if (node->key[insertIdx] > key) {
                break;
            }
        }

        node->key.insert(node->key.begin() + insertIdx, key);
    } else {
        int32_t insertIdx = 0;
        for (insertIdx = 0; insertIdx < node->key.size(); ++insertIdx) {
            if (node->key[insertIdx] > key) {
                break;
            }
        }

        int32_t idx = insertIdx;

        if (node->children[idx]->key.size() == 2 * t - 1) {
            splitChildInternal(node, idx, t);
            if (key > node->key[idx]) {
                ++idx;
            }
        }

        insertInternal(node->children[idx], key, t);
    }
}


void splitChildInternal(Node *node, int32_t idx, int32_t t) {
    Node *child = node->children[idx];
    Node *newChild = new Node(t);
    newChild->isLeaf = child->isLeaf;
    newChild->parent = node;

    newChild->key.assign(child->key.begin() + t, child->key.end());
    child->key.resize(t - 1);

    if (!child->isLeaf) {
        for (int32_t i = t; i < child->children.size(); ++i) {
            newChild->children.push_back(child->children[i]);
        }
        child->children.resize(t);

        for (int32_t i = 0; i < newChild->children.size(); ++i) {
            newChild->children[i]->parent = newChild;
        }
    }

    node->children.insert(node->children.begin() + idx + 1, newChild);
    node->key.insert(node->key.begin() + idx, child->key[t - 1]);
}


void deleteNodesCascade(Node *node) {
    if (node != nullptr) {
        if (!node->isLeaf) {
            for (int32_t i = 0; i < node->children.size(); ++i) {
                deleteNodesCascade(node->children[i]);
            }
        }
        delete node;
    }
}

bool containsInternal(Node *node, int32_t key) {
    if (node == nullptr) {
        return false;
    }

    int32_t idx = 0;
    while (idx < node->key.size() && key > node->key[idx]) {
        idx++;
    }

    if (idx < node->key.size() && node->key[idx] == key) {
        return true;
    }

    if (node->isLeaf) {
        return false;
    }

    return containsInternal(node->children[idx], key);
}

int64_t leafSumInternal(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    if (node->isLeaf) {
        int64_t leafSum = 0;
        for (int32_t i = 0; i < node->key.size(); ++i) {
            leafSum += node->key[i];
        }
        return leafSum;
    }

    int64_t sumFromCurrentNode = 0;
    for (int32_t i = 0; i < node->children.size(); ++i) {
        sumFromCurrentNode += leafSumInternal(node->children[i]);
    }

    return sumFromCurrentNode;
}