#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <initializer_list>
#include <cstdint>

enum class Color { RED, BLACK };

struct Node {
    int32_t key;
    int32_t height;
    int32_t size;
    Node *left;
    Node *right;
    Node *parent;
    Color color;

    explicit Node(int32_t key);
};

class RBTree {
public:
    Node *root = nullptr;

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
    Node* InternalFindNode(Node* rootNode, int32_t key); //Ok

    Node* lowerBoundInternal(Node* node, int32_t key); //Ok

    Node* insertNodeInternal(Node* rootNode, Node* node);

    void DeleteNodesCascade(Node* node); //Ok

    int32_t getNodeHeight(Node* node); //Ok

    int32_t getNodeSize(Node* node); // Ok

    void balanceHeight(Node*& node); // Ok

    void balanceSize(Node*& node); //Ok

    void balanceMetadata(Node*& node); //Ok

    void rotateRight(Node*& node);

    void rotateLeft(Node*& node);

    void fixInsert(Node*& node);
};

#endif
