#include "MiddleQueue.h"

MiddleQueue::MiddleQueue() {
    head = tail = middle = nullptr;
    _size = 0;
}

int MiddleQueue::front() const {
    return head->value;
}

void MiddleQueue::push_back(int value) {
    Node *newTailNode = new Node(value);
    newTailNode->next = nullptr;

    if (empty()) {
        newTailNode->prev = nullptr;
        head = newTailNode;
        tail = newTailNode;
        middle = newTailNode;
    } else {
        tail->next = newTailNode;
        newTailNode->prev = tail;
        tail = newTailNode;

        if (_size % 2 == 0) {
            middle = middle->next;
        }
    }
    _size++;
}

void MiddleQueue::insert_in_middle(int value) {
    Node* pos = middle;

    if (pos == tail) {
        push_back(value);
        return;
    }

    Node *newNode = new Node(value);
    newNode->next = pos->next;
    newNode->prev = pos;
    pos->next->prev = newNode;
    pos->next = newNode;

    if (_size % 2 == 0) {
        middle = middle->next;
    }
    _size++;
}

void MiddleQueue::pop_front() {
    if (_size != 1) {
        if (_size % 2 == 0) {
            middle = middle->next;
        }

        Node *newHeadNode = head->next;
        newHeadNode->prev = nullptr;
        head->next = nullptr;
        head = newHeadNode;
    } else {
        head = tail = middle = nullptr;
    }
    _size--;
}

bool MiddleQueue::empty() const {
    return (head == nullptr);
}
