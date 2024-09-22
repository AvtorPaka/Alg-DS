#include <cstdint>
#include <cstddef>

#ifndef MIDDLEQUEUE_H
#define MIDDLEQUEUE_H

struct Node {
public:
    Node *prev;
    Node *next;
    int value;

    Node() {
        next = prev = nullptr;
        value = 0;
    }

    Node(const int value) : value(value) { next = prev = nullptr; }
};

// Queue with O(1) insertion in middle implementation
class MiddleQueue {
public:
    size_t _size;
    Node *middle;
    Node *head;
    Node *tail;

    MiddleQueue();
    ~MiddleQueue() = default;
    int front() const;
    void push_back(int value);
    void insert_in_middle(int value);
    void pop_front();
    [[nodiscard]] bool empty() const;
};

#endif //MIDDLEQUEUE_H