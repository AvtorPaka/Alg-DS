#include "RBTree.h"

#include <cstdint>
#include <algorithm>

RBNode::RBNode(int32_t key) {
    this->key = key;
    this->left = this->right = this->parent = nullptr;
    this->color = Color::RED;
    this->height = 1;
    this->size = 1;
}

int32_t RBTree::size() const {
    return this->root == nullptr ? 0 : root->size;
}

bool RBTree::empty() const {
    return this->root == nullptr;
}

int32_t RBTree::height() const {
    return this->root == nullptr ? 0 : root->size;
}

RBTree::RBTree() {
    this->root = nullptr;
}

int32_t *RBTree::find(int32_t key) {
    RBNode *foundNode = InternalFindNode(this->root, key);

    return foundNode == nullptr ? nullptr : &foundNode->key;
}

RBNode *RBTree::InternalFindNode(RBNode *node, int32_t key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key == node->key) {
        return node;
    }
    if (key < node->key) {
        return InternalFindNode(node->left, key);
    }
    if (key > node->key) {
        return InternalFindNode(node->right, key);
    }

    return nullptr;
}

void RBTree::insert(int32_t key) {
    RBNode *newNode = new RBNode(key);
    this->root = insertNodeInternal(this->root, newNode);
    fixInsert(newNode);
}

RBTree::RBTree(std::initializer_list<int32_t> list) {
    for (int32_t key: list) {
        this->insert(key);
    }
}

int32_t *RBTree::lowerBound(int32_t key) {
    RBNode *lowerBoundNode = lowerBoundInternal(this->root, key);

    return lowerBoundNode == nullptr ? nullptr : &lowerBoundNode->key;
}

void RBTree::DeleteNodesCascade(RBNode *node) {
    if (node != nullptr) {
        DeleteNodesCascade(node->left);
        DeleteNodesCascade(node->right);
        delete node;
    }
}

RBTree::~RBTree() {
    DeleteNodesCascade(this->root);
}

RBNode *RBTree::lowerBoundInternal(RBNode *node, int32_t key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->key == key) {
        return node;
    }
    if (node->key < key) {
        return lowerBoundInternal(node->right, key);
    }

    RBNode *tmpNode = lowerBoundInternal(node->left, key);
    if (tmpNode != nullptr) {
        return tmpNode;
    } else {
        return node;
    }
}

int32_t RBTree::getNodeHeight(RBNode *node) {
    return node == nullptr ? 0 : node->height;
}

void RBTree::balanceHeight(RBNode *&node) {
    if (node != nullptr) {
        node->height =
                std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + (node->color == Color::BLACK ? 1 : 0);
    }
}

int32_t RBTree::getNodeSize(RBNode *node) {
    return node == nullptr ? 0 : node->size;
}

void RBTree::balanceSize(RBNode *&node) {
    if (node != nullptr) {
        node->size = getNodeSize(node->left) + getNodeSize(node->right) + 1;
    }
}

void RBTree::balanceMetadata(RBNode *&node) {
    balanceHeight(node);
    balanceSize(node);
}

RBNode* RBTree::insertNodeInternal(RBNode *rootNode, RBNode *node) {
    if (rootNode == nullptr) {
        return node;
    }

    if (node->key < rootNode->key) {
        rootNode->left = insertNodeInternal(rootNode->left, node);
        rootNode->left->parent = rootNode;
    } else if (node->key > rootNode->key) {
        rootNode->right = insertNodeInternal(rootNode->right, node);
        rootNode->right->parent = rootNode;
    }

    balanceMetadata(rootNode);
    return rootNode;
}

void RBTree::rotateRight(RBNode *&node) {
    RBNode *child = node->left;
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

    balanceMetadata(node);
    balanceMetadata(child);
}

void RBTree::rotateLeft(RBNode *&node) {
    RBNode *child = node->right;
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

    balanceMetadata(node);
    balanceMetadata(child);
}

void RBTree::fixInsert(RBNode *&node) {
    while (node->parent && node->parent->color == Color::RED) {
        RBNode *grandparent = node->parent->parent;
        if (node->parent == grandparent->left) {
            RBNode *uncle = grandparent->right;
            if (uncle && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent);
            }
        } else {
            RBNode *uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = Color::BLACK;
}

