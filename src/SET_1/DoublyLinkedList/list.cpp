#include <stdexcept>
#include <cstdint>
#include <unordered_set>
#include "list.h"

List::List() {
    head = tail = nullptr;
    _size = 0;
}

List::List(const List &other) {
    Node *new_tail_node = new Node(other.tail->prev, other.tail->next, other.tail->value);
    tail = new_tail_node;
    Node *new_head_node = new Node(other.head->prev, other.head->next, other.head->value);
    head = new_head_node;
    _size = other._size;
}

List::List(std::vector<int> array) {
    _size = 0;
    if (array.empty()) {
        head = tail = nullptr;
    } else {
        Node *head_node = new Node(array[0]);
        _size++;
        head = head_node;
        tail = head_node;

        for (int32_t i = 1; i < array.size(); ++i) {
            push_back(array[i]);
        }
    }
}

List::~List() {
}

int List::front() {
    return head->value;
}


int List::back() {
    return tail->value;
}

void List::push_back(int value) {
    Node *newTailNode = new Node(value);
    newTailNode->next = nullptr;

    if (empty()) {
        newTailNode->prev = nullptr;
        head = newTailNode;
        tail = newTailNode;
    } else {
        tail->next = newTailNode;
        newTailNode->prev = tail;
        tail = newTailNode;
    }
    _size++;
}

void List::push_front(int value) {
    Node *newHeadNode = new Node(value);
    newHeadNode->prev = nullptr;

    if (empty()) {
        newHeadNode->next = nullptr;
        head = newHeadNode;
        tail = newHeadNode;
    } else {
        head->prev = newHeadNode;
        newHeadNode->next = head;
        head = newHeadNode;
    }
    _size++;
}

void List::insert(Node *pos, int value) {
    if (pos == nullptr || head == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }

    if (pos == tail) {
        push_back(value);
        return;
    }

    bool inList = false;
    Node *tmp = head;
    while (tmp != nullptr) {
        if (tmp == pos) {
            inList = true;
            break;
        }
        tmp = tmp->next;
    }

    if (!inList) {
        throw std::runtime_error("Incorrect position!");
    } else {
        Node *newNode = new Node(value);
        newNode->next = pos->next;
        newNode->prev = pos;
        pos->next->prev = newNode;
        pos->next = newNode;
        _size++;
    }
}

void List::pop_front() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }

    if (_size != 1) {
        Node *newHeadNode = head->next;
        newHeadNode->prev = nullptr;
        head->next = nullptr;
        head = newHeadNode;
    } else {
        head = tail = nullptr;
    }
    _size--;
}

void List::pop_back() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }

    if (_size != 1) {
        Node *newTailNode = tail->prev;
        newTailNode->next = nullptr;
        tail->prev = nullptr;
        tail = newTailNode;
    } else {
        head = tail = nullptr;
    }
    _size--;
}

void List::erase(Node *pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }

    if (pos == head) {
        pop_front();
        return;
    }

    if (pos == tail) {
        pop_back();
        return;
    }

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    pos->prev = nullptr;
    pos->next = nullptr;
    _size--;
}

void List::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

void List::reverse() {
    if (!empty() && _size != 1) {
        Node *temp = nullptr;
        Node *current = head;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr)
            head = temp->prev;

        Node *tmpHead = head;
        while (tmpHead != nullptr) {
            if (tmpHead->next == nullptr) {
                tail = tmpHead;
            }
            tmpHead = tmpHead->next;
        }
    }
}

void List::remove_duplicates() {
    if (!empty() && _size != 1) {
        std::unordered_set<int32_t> unique;

        Node *tmpHead = head;
        while (tmpHead != nullptr) {
            Node *nextNode = tmpHead->next;
            if (unique.contains(tmpHead->value)) {
                erase(tmpHead);
            } else {
                unique.insert(tmpHead->value);
            }
            tmpHead = nextNode;
        }
    }
}

void List::replace(int old_value, int new_value) {
    Node *tmpHead = head;
    while (tmpHead != nullptr) {
        if (tmpHead->value == old_value) {
            tmpHead->value = new_value;
        }
        tmpHead = tmpHead->next;
    }
}

void List::merge(const List &other) {
    if (!other.empty()) {
        Node *tmpHead = other.head;
        while (tmpHead != nullptr) {
            push_back(tmpHead->value);
            tmpHead = tmpHead->next;
        }
    }
}

void List::copy(const List &other) {
    clear();
    Node *tmpHead = other.head;
    while (tmpHead != nullptr) {
        push_back(tmpHead->value);
        tmpHead = tmpHead->next;
    }
}

bool List::check_cycle() const {
    Node *t = head;
    Node *h = head;

    while (h != nullptr && h->next != nullptr) {
        t = t->next;
        h = h->next->next;
        if (t == h) {
            return true;
        }
    }

    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const {
    return (head == nullptr);
}

