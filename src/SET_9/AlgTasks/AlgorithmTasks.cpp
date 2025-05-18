#include "AlgorithmTasks.h"

#include <queue>
#include <vector>

std::map<char, std::string> AlgorithmTasks::GetHuffmanPrefixCode(const std::string& text) {
    std::map<char, std::string> textSymbolCodes;

    HuffmanNode* huffmanTreeRoot = BuildHuffmanPrefixTree(text);
    GetHuffmanTreeSymbolCodes(huffmanTreeRoot, textSymbolCodes, "");

    return textSymbolCodes;
}

void AlgorithmTasks::GetHuffmanTreeSymbolCodes(HuffmanNode* node, std::map<char, std::string>& symbolCodes, std::string curCode) {
    if (!node) {
        return;
    }

    if (node->isLeaf()) {
        symbolCodes[node->symbol] = curCode.empty() ? "0" : std::move(curCode);
        return;
    }

    GetHuffmanTreeSymbolCodes(node->left, symbolCodes, curCode + "0");
    GetHuffmanTreeSymbolCodes(node->right, symbolCodes, curCode + "1");
}

HuffmanNode*  AlgorithmTasks::BuildHuffmanPrefixTree(const std::string& text) {
    std::vector<uint32_t> charFreq(26);

    for (int32_t i = 0; i < text.size(); ++i) {
        charFreq[text[i] - 97]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNodeComparator> pq;
    for (int32_t i = 0; i < charFreq.size(); ++i) {
        if (charFreq[i] > 0) {
            pq.push(new HuffmanNode((char)(i + 97), charFreq[i], nullptr, nullptr));
        }
    }

    while(pq.size() > 1) {
        HuffmanNode* minFreqNode = pq.top();
        pq.pop();
        HuffmanNode* preMinFreqNode = pq.top();
        pq.pop();
        pq.push(new HuffmanNode(minFreqNode->freq + preMinFreqNode->freq, minFreqNode, preMinFreqNode));
    }

    return pq.top();
}


std::vector<uint32_t> AlgorithmTasks::LZWEncode(const std::string& text) {
    std::vector<uint32_t> lzwCodes;
    std::unordered_map<std::string, uint32_t> charCodes;

    for (int32_t i = 0; i < 128; ++i) {
        charCodes[{(char)i}] = i;
    }

    size_t n = text.size();
    std::string curSubstring;
    uint32_t nextCode = 128;
    int32_t i = 0;
    while (i < n) {
        curSubstring = {text[i]};

        while (i < n - 1 && charCodes.contains(curSubstring + text[i + 1])) {
            curSubstring += text[++i];
        }

        lzwCodes.push_back(charCodes[curSubstring]);

        if (i + 1 < n) {
            curSubstring += text[i + 1];
        }
        charCodes[curSubstring] = nextCode++;

        i++;
    }

    return lzwCodes;
}


std::string AlgorithmTasks::LZWDecode(const std::vector<uint32_t>& charCodes) {
    std::string encodedString;
    std::unordered_map<uint32_t, std::string> charCodesMap;
    for (int32_t i = 0; i < 128; ++i) {
        charCodesMap[i] = {(char)i};
    }

    size_t n = charCodes.size();
    uint32_t nextCode = 128;

    uint32_t prevCode = charCodes[0];
    std::string prevSubString = charCodesMap[prevCode];
    encodedString += prevSubString;

    uint32_t curCode;
    std::string curCodeSubstr;
    for (int32_t i = 1; i < n; ++i) {
        curCode = charCodes[i];

        if (charCodesMap.contains(curCode)) {
            curCodeSubstr = charCodesMap[curCode];
        } else {
            curCodeSubstr = prevSubString + prevSubString[0];
        }

        encodedString += curCodeSubstr;
        charCodesMap[nextCode++] = prevSubString + curCodeSubstr[0];
        prevSubString = curCodeSubstr;
    }

    return encodedString;
}