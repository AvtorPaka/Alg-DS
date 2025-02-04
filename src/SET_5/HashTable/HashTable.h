#ifndef IMPLEMENTATIONDATA_HASHTABLE_H
#define IMPLEMENTATIONDATA_HASHTABLE_H

#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <stdexcept>

template<class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType curKey, ValueType curVal) {
        key = curKey;
        value = curVal;
        next = nullptr;
    }
};

template<class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
private:
    size_t _capacity;
    size_t _size;
    Func _hash;
    double _loadFactor;
    std::vector<Node<KeyType, ValueType> *> _buckets;

    size_t GetHash(KeyType key) {
        return _hash(key) % _capacity;
    }

    void SetLoadFactor(double loadFactor) {
        if (loadFactor > 0 && loadFactor <= 1) {
            _loadFactor = loadFactor;
        } else {
            _loadFactor = 0.5;
        }
    }

    void ReHash() {
        size_t old_capacity = _capacity;
        this->_capacity = this->_capacity * 2;
        this->_size = 0;

        std::vector<Node<KeyType, ValueType> *> oldBuckets = this->_buckets;
        _buckets = std::vector<Node<KeyType, ValueType> *>(_capacity, nullptr);
        _buckets.shrink_to_fit();

        for (size_t i = 0; i < old_capacity; ++i) {
            Node<KeyType, ValueType> *node = oldBuckets[i];
            while (node != nullptr) {
                Node<KeyType, ValueType>* next = node->next;
                this->insert(node->key, node->value);
                delete node;
                node = next;
            }
        }

    }

public:

    HashTable() {
        _capacity = 100;
        _size = 0;
        _loadFactor = 0.5;
        _buckets = std::vector<Node<KeyType, ValueType> *>(_capacity, nullptr);
        _buckets.shrink_to_fit();
    }

    explicit HashTable(Func hash) : HashTable() {
        _hash = hash;
    }

    HashTable(size_t capacity, double loadFactor, Func hash = std::hash<KeyType>()) {
        _capacity = capacity;
        _size = 0;
        SetLoadFactor(loadFactor);
        _hash = hash;
        _buckets = std::vector<Node<KeyType, ValueType> *>(_capacity, nullptr);
        _buckets.shrink_to_fit();
    }


    void insert(KeyType key, ValueType value) {
        size_t keyHash = GetHash(key);

        Node<KeyType, ValueType> *newNode = new Node<KeyType, ValueType>(key, value);

        if (_buckets[keyHash] == nullptr) {
            _buckets[keyHash] = newNode;
            _size++;

            if ((double) _size / (double) _capacity > _loadFactor) {
                ReHash();
            }
            return;
        }

        Node<KeyType, ValueType> *node = _buckets[keyHash];
        Node<KeyType, ValueType> *prevNode = nullptr;
        while (node != nullptr) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            prevNode = node;
            node = node->next;
        }

        prevNode->next = newNode;
        _size++;

        if ((double) _size / (double) _capacity > _loadFactor) {
            ReHash();
        }
    }

    ValueType *find(KeyType key) {
        size_t keyHash = GetHash(key);

        Node<KeyType, ValueType> *node = _buckets[keyHash];
        while (node != nullptr) {
            if (node->key == key) {
                return &(node->value);
            }
            node = node->next;
        }

        return nullptr;
    }

    void erase(KeyType key) {
        size_t keyHash = GetHash(key);

        Node<KeyType, ValueType> *node = _buckets[keyHash];
        Node<KeyType, ValueType> *prevNode = nullptr;

        while (node != nullptr) {
            if (node->key == key) {
                if (prevNode != nullptr) {
                    prevNode->next = node->next;
                } else {
                    _buckets[keyHash] = nullptr;
                }
                delete node;
                _size--;
                return;
            }

            prevNode = node;
            node = node->next;
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t hashCode) {
        if (hashCode >= _capacity) {
            throw std::out_of_range("Hash out of range");
        }
        if (_buckets[hashCode] == nullptr) {
            throw std::runtime_error("Trying to access missing value in HashTable ;(.");
        }

        return *(_buckets[hashCode]);
    }

    Node<KeyType, ValueType> at(uint64_t hashCode) {
        if (hashCode >= _capacity) {
            throw std::out_of_range("Hash out of range");
        }
        if (_buckets[hashCode] == nullptr) {
            throw std::runtime_error("Trying to access missing value in HashTable ;(.");
        }

        return *(_buckets[hashCode]);
    }

    size_t size() const {
        return this->_size;
    }

    size_t capacity() const {
        return this->_capacity;
    }

    ~HashTable() {
        for (size_t i = 0; i < _capacity; ++i) {
            Node<KeyType, ValueType>* node = _buckets[i];
            if (node != nullptr) {
                Node<KeyType, ValueType>* next = node->next;
                delete node;
                node = next;
            }
        }
    }
};

#endif //IMPLEMENTATIONDATA_HASHTABLE_H
