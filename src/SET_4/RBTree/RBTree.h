#ifndef IMPLEMENTATIONDATA_RBTREE_H
#define IMPLEMENTATIONDATA_RBTREE_H

#include <initializer_list>
#include <cstdint>

enum class Color { RED, BLACK };

struct RBNode {
    int32_t key;
    int32_t height;
    int32_t size;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    Color color;

    explicit RBNode(int32_t key);
};

class RBTree {
public:
    RBNode *root = nullptr;

    RBTree();

    RBTree(std::initializer_list<int32_t> list);

    ~RBTree();

    void insert(int32_t key);

    int32_t *find(int32_t key);

    int32_t size() const;

    int32_t *lowerBound(int32_t key);

    bool empty() const;

    int32_t height() const;

private:
    RBNode* InternalFindNode(RBNode* rootNode, int32_t key);

    RBNode* lowerBoundInternal(RBNode* node, int32_t key);

    RBNode* insertNodeInternal(RBNode* rootNode, RBNode* node);

    void DeleteNodesCascade(RBNode* node);

    int32_t getNodeHeight(RBNode* node);

    int32_t getNodeSize(RBNode* node);

    void balanceHeight(RBNode*& node);

    void balanceSize(RBNode*& node);

    void balanceMetadata(RBNode*& node);

    void rotateRight(RBNode*& node);

    void rotateLeft(RBNode*& node);

    void fixInsert(RBNode*& node);
};

#endif //IMPLEMENTATIONDATA_RBTREE_H
