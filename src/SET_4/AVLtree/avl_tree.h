#ifndef IMPLEMENTATIONDATA_AVL_TREE_H
#define IMPLEMENTATIONDATA_AVL_TREE_H

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

    explicit AVLTree(int32_t value); //Ok

    int32_t getHeight(); //Ok

    void insert(int32_t value); //Ok

    void erase(int32_t value); // Ok

    int32_t *find(int32_t value); //Ok

    int32_t *traversal(); // Ok

    int32_t *lowerBound(int32_t value); // Ok

    bool empty(); //Ok

    Node *getRoot(); //Ok

    int32_t getSize(); //Ok

    ~AVLTree(); //Ok

private:
    Node *root_;
    int32_t size_;

    int32_t getNodeHeight(Node *node); //Ok

    int32_t balanceFactor(Node *node); //Ok

    void balanceHeight(Node *node); //Ok

    Node *rotateRight(Node *node); //Ok

    Node *rotateLeft(Node *node); //Ok

    Node *balanceNode(Node *node); //Ok

    Node *insertNode(Node *node, int32_t value); //Ok

    Node *findMinNode(Node *node); // Ok

    Node *removeMinNode(Node *node); // Ok?

    Node *removeNode(Node *node, int32_t value); // Ok

    Node *findNode(Node *node, int32_t value); //Ok

    void traversalInternal(Node *node, int32_t *array, int32_t *index); // Ok

    Node *lowerBoundInternal(Node *current, int32_t value) const; // Ok
};


#endif //IMPLEMENTATIONDATA_AVL_TREE_H
