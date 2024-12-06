#ifndef IMPLEMENTATIONDATA_AVLTREE_H
#define IMPLEMENTATIONDATA_AVLTREE_H

#include "cstdint"

struct Node {
    int32_t height;
    Node *left;
    Node *right;
    int32_t value;

    Node(int32_t value);

    ~Node();
};

class AVLTree {
public:
    AVLTree();

    explicit AVLTree(int32_t value);

    int32_t getHeight();

    void insert(int32_t value);

    void erase(int32_t value);

    int32_t *find(int32_t value);

    int32_t *traversal();

    int32_t *lowerBound(int32_t value);

    bool empty();

    Node *getRoot();

    int32_t getSize();

    ~AVLTree();

private:
    Node *root_;
    int32_t size_;

    int32_t getNodeHeight(Node *node);

    int32_t balanceFactor(Node *node);

    void balanceHeight(Node *node);

    Node *rotateRight(Node *node);

    Node *rotateLeft(Node *node);

    Node *balanceNode(Node *node);

    Node *insertNode(Node *node, int32_t value);

    Node *findMinNode(Node *node);

    Node *removeMinNode(Node *node);

    Node *removeNode(Node *node, int32_t value);

    Node *findNode(Node *node, int32_t value);

    void traversalInternal(Node *node, int32_t *array, int32_t *index);

    Node *lowerBoundInternal(Node *current, int32_t value) const;
};


#endif //IMPLEMENTATIONDATA_AVLTREE_H
