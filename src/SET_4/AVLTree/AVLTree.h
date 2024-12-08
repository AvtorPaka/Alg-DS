#ifndef IMPLEMENTATIONDATA_AVLTREE_H
#define IMPLEMENTATIONDATA_AVLTREE_H

#include "cstdint"

struct AVLNode {
    int32_t height;
    AVLNode *left;
    AVLNode *right;
    int32_t value;

    AVLNode(int32_t value);

    ~AVLNode();
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

    AVLNode *getRoot();

    int32_t getSize();

    ~AVLTree();

private:
    AVLNode *root_;
    int32_t size_;

    int32_t getNodeHeight(AVLNode *node);

    int32_t balanceFactor(AVLNode *node);

    void balanceHeight(AVLNode *node);

    AVLNode *rotateRight(AVLNode *node);

    AVLNode *rotateLeft(AVLNode *node);

    AVLNode *balanceNode(AVLNode *node);

    AVLNode *insertNode(AVLNode *node, int32_t value);

    AVLNode *findMinNode(AVLNode *node);

    AVLNode *removeMinNode(AVLNode *node);

    AVLNode *removeNode(AVLNode *node, int32_t value);

    AVLNode *findNode(AVLNode *node, int32_t value);

    void traversalInternal(AVLNode *node, int32_t *array, int32_t *index);

    AVLNode *lowerBoundInternal(AVLNode *current, int32_t value) const;
};


#endif //IMPLEMENTATIONDATA_AVLTREE_H
