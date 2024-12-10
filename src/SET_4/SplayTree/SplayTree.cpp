#include "SplayTree.h"

#include <cstdint>
#include <algorithm>

Node::Node(int32_t key, Node *parent) {
    this->key = key;
    this->parent = parent;
    this->left = this->right = nullptr;
}

SplayTree::SplayTree() {
    this->root = nullptr;
}

void SplayTree::insert(int32_t key) {
    Node *current = this->root;
    Node *prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            return;
        }

        if (key < current->key) {
            prev = current;
            current = current->left;
        } else if (key > current->key) {
            prev = current;
            current = current->right;
        }
    }

    Node *newNode = new Node(key, prev);
    if (prev == nullptr) {
        this->root = newNode;
    } else if (key < prev->key) {
        prev->left = newNode;
    } else if (key > prev->key) {
        prev->right = newNode;
    }

}

Node *SplayTree::find(int32_t key) const {
    Node *node = this->root;

    while (node != nullptr) {
        if (node->key == key) {
            return node;
        }
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        }
    }

    return nullptr;
}

int32_t SplayTree::splay(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    int32_t rotations = 0;
    while (node->parent != nullptr) {
        Node *parentNode = node->parent;
        Node *grandparentNode = parentNode->parent;

        if (grandparentNode == nullptr) {
            if (parentNode->left == node) {
                rotateRight(parentNode);
            } else {
                rotateLeft(parentNode);
            }
        } else {
            if (parentNode->right == node) {
                if (grandparentNode->left == parentNode) {
                    rotateLeft(parentNode);
                    rotateRight(grandparentNode);
                } else {
                    rotateLeft(grandparentNode);
                    rotateLeft(parentNode);
                    rotations++;
                }
            } else {
                if (grandparentNode->right == parentNode) {
                    rotateRight(parentNode);
                    rotateLeft(grandparentNode);
                } else {
                    rotateRight(grandparentNode);
                    rotateRight(parentNode);
                    rotations++;
                }
            }
        }
        rotations++;
    }
    return rotations;
}

int32_t SplayTree::getHeight() const {
    return this->root == nullptr ? 0 : getHeight(this->root);
}

void SplayTree::clear(Node *node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void SplayTree::rotateLeft(Node *node) {
    Node *child = node->right;
    node->right = child->left;

    if (node->right != nullptr) {
        node->right->parent = node;
    }

    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

void SplayTree::rotateRight(Node *node) {
    Node *child = node->left;
    node->left = child->right;

    if (node->left != nullptr) {
        node->left->parent = node;
    }

    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->right = node;
    node->parent = child;
}

SplayTree::~SplayTree() {
    clear(this->root);
}

int32_t SplayTree::getHeight(Node *node) const {
    if (node == nullptr) {
        return -1;
    }
    int32_t maxLeftDepth = getHeight(node->left);
    int32_t maxRightDepth = getHeight(node->right);

    return 1 + std::max(maxLeftDepth, maxRightDepth);
}
