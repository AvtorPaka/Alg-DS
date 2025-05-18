#ifndef ALGORITHMTASKS_9_H
#define ALGORITHMTASKS_9_H

#include <cstdint>
#include <string>
#include <map>

struct HuffmanNode {
    char symbol;
    uint32_t freq;
    HuffmanNode* left;
    HuffmanNode* right;

    bool isLeaf() const {
        return this->symbol != '\0';
    }

    HuffmanNode(char ch, uint32_t freq, HuffmanNode* left, HuffmanNode* right)
    {
        this->symbol = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }

    HuffmanNode(uint32_t freq, HuffmanNode* left, HuffmanNode* right): HuffmanNode('\0', freq, left, right) {}
};

struct HuffmanNodeComparator {
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        if (left->freq != right->freq) {
            return left->freq > right->freq;
        }

        if (left->isLeaf() && right->isLeaf()) {
            return left->symbol > right->symbol;
        } else if (left->isLeaf() && !right->isLeaf()) {
            return false;
        } else if (!left->isLeaf() && right->isLeaf()) {
            return true;
        }

        return left->freq > right->freq;
    }
};

class AlgorithmTasks {
public:
    static std::map<char, std::string> GetHuffmanPrefixCode(const std::string& text);

    static HuffmanNode* BuildHuffmanPrefixTree(const std::string& text);

    static std::vector<uint32_t> LZWEncode(const std::string& text);

    static std::string LZWDecode(const std::vector<uint32_t>& charCodes);

private:
    static void GetHuffmanTreeSymbolCodes(HuffmanNode* node, std::map<char, std::string>& symbolCodes, std::string curCode);
};


#endif //ALGORITHMTASKS_9_H
