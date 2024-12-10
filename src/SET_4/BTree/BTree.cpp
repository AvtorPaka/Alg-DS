#include "BTree.h"

#include <cstdint>
#include <vector>

Node::Node(int32_t t) {
    this->t = t;
    this->parent = nullptr;
    this->isLeaf = true;
    this->key.reserve(2 * t - 1);
    this->children.reserve(2 * t);
}

BTree::BTree(int32_t t) {
    this->t_ = t;
    this->root = nullptr;
    this->size_ = 0;
}

BTree::~BTree() {
    deleteNodesCascade(this->root);
}

void BTree::insert(int32_t key) {
    if (this->root == nullptr) {
        this->root = new Node(this->t_);
        this->root->key.push_back(key);
        this->size_++;
        return;
    }

    if (!containsInternal(this->root, key)) {
        if ((int32_t)this->root->key.size() == this->t_ * 2 - 1) {
            Node *splitRoot = new Node(this->t_);

            splitRoot->isLeaf = false;
            splitRoot->children.push_back(this->root);
            this->root->parent = splitRoot;
            this->root = splitRoot;

            splitChildInternal(this->root, 0);
            insertInternal(splitRoot, key);
        } else {
            insertInternal(this->root, key);
        }
        this->size_++;
    }
}

size_t BTree::size() const {
    return countNodesInternal(this->root);
}

int32_t BTree::countNodesInternal(Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    int32_t cntNodesDown = 0;
    for (int32_t i = 0; i < node->children.size(); ++i) {
        cntNodesDown += countNodesInternal(node->children[i]);
    }

    return cntNodesDown + 1;
}

int64_t BTree::sum() const {
    return leafSumInternal(this->root);
}

void BTree::insertInternal(Node *node, int32_t key) {
    if (node->isLeaf) {
        int32_t insertIdx = findKeyIndex(node, key);

        node->key.insert(node->key.begin() + insertIdx, key);
    } else {
        int32_t idx = findKeyIndex(node, key);

        if (node->children[idx]->key.size() == 2 * this->t_ - 1) {
            splitChildInternal(node, idx);
            if (key > node->key[idx]) {
                ++idx;
            }
        }

        insertInternal(node->children[idx], key);
    }
}


void BTree::splitChildInternal(Node *node, int32_t idx) {
    Node *child = node->children[idx];
    Node *newChild = new Node(this->t_);
    newChild->isLeaf = child->isLeaf;
    newChild->parent = node;

    newChild->key.insert(newChild->key.end(), child->key.begin() + this->t_, child->key.end());
    child->key.resize(this->t_ - 1);

    if (!child->isLeaf) {
        newChild->children.insert(newChild->children.end(), child->children.begin() + this->t_, child->children.end());
        child->children.resize(this->t_);
    }

    node->children.insert(node->children.begin() + idx + 1, newChild);
    node->key.insert(node->key.begin() + idx, child->key[this->t_ - 1]);
}

void BTree::deleteNodesCascade(Node *node) {
    if (node != nullptr) {
        if (!node->isLeaf) {
            for (int32_t i = 0; i < node->children.size(); ++i) {
                deleteNodesCascade(node->children[i]);
            }
        }
        delete node;
    }
}

bool BTree::containsInternal(Node *node, int32_t key) {
    Node* checkNode = node;
    while (checkNode != nullptr) {
        int32_t idx = findKeyIndex(checkNode, key);

        if (idx < checkNode->key.size() && checkNode->key[idx] == key) {
            return true;
        }
        if (checkNode->isLeaf) {
            return false;
        }
        checkNode = checkNode->children[idx];
    }
}

int32_t BTree::findKeyIndex(Node* node, int32_t key) {
    int32_t idx = 0;
    int32_t size = (int32_t)node->key.size() - 1;
    while (idx <= size) {
        int32_t mid = (idx + size) / 2;
        if (node->key[mid] == key) {
            return mid;
        }
        if (node->key[mid] < key) {
            idx = mid + 1;
        } else {
            size = mid - 1;
        }
    }
    return idx;
}

int64_t BTree::leafSumInternal(Node *node) const {
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