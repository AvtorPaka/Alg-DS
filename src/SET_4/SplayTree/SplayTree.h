#ifndef IMPLEMENTATIONDATA_SPLAYTREE_H
#define IMPLEMENTATIONDATA_SPLAYTREE_H

#include <cstdint>

struct Node {
    Node(int32_t key, Node *parent);

    int32_t key;
    Node *left;
    Node *right;
    Node *parent;
};

class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void insert(int32_t key);

    Node *find(int32_t key) const;

    int32_t splay(Node *node);

    int32_t getHeight() const;

private:
    Node *root;

    void clear(Node *node);

    void rotateLeft(Node *node);

    void rotateRight(Node *node);

    int32_t getHeight(Node *node) const;
};

#endif //IMPLEMENTATIONDATA_SPLAYTREE_H
