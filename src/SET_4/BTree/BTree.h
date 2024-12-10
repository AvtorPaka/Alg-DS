#ifndef IMPLEMENTATIONDATA_BTREE_H
#define IMPLEMENTATIONDATA_BTREE_H

#include <vector>
#include <cstdint>

struct Node {
    Node(int32_t t);

    std::vector<int32_t> key;
    std::vector<Node *> children;
    Node *parent;
    bool isLeaf;
    int32_t t;
};


class BTree {
public:
    explicit BTree(int32_t t);

    ~BTree();

    void insert(int32_t key);

    size_t size() const;

    int64_t sum() const;


private:
    Node *root;
    int32_t t_;
    int32_t size_;

    int64_t leafSumInternal(Node *node) const;

    void splitChildInternal(Node *node, int32_t idx);

    void insertInternal(Node *node, int32_t key);

    void deleteNodesCascade(Node *node);

    bool containsInternal(Node *node, int32_t key);

    int32_t findKeyIndex(Node* node, int32_t key);

    int32_t countNodesInternal(Node* node) const;
};

#endif // IMPLEMENTATIONDATA_BTREE_H