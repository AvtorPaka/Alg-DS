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
};

#endif // IMPLEMENTATIONDATA_BTREE_H