#ifndef ALGORITHMTASKS_4_H
#define ALGORITHMTASKS_4_H

#include <cstdint>
#include <string>

struct RBNode {
    int32_t number;
    int32_t key;
    int32_t leftNodeNumber;
    int32_t rightNodeNumber;
    bool redColor;

    RBNode(int32_t num = 0, int32_t key = 0, int32_t leftNum = -1, int32_t rightNum = -1,
           bool color = false) {
        this->number = num;
        this->key = key;
        this->leftNodeNumber = leftNum;
        this->rightNodeNumber = rightNum;
        this->redColor = color;
    }

    RBNode(int32_t num = 0, int32_t key = 0, const std::string &leftNum = "null", const std::string &rightNum = "null",
           const std::string &color = "B") {
        this->number = num;
        this->key = key;
        this->leftNodeNumber = ConvertToNodeNum(leftNum);
        this->rightNodeNumber = ConvertToNodeNum(rightNum);
        this->redColor = (color == "R");
    }

private:
    static int32_t ConvertToNodeNum(const std::string &stringNodeNum) {
        return (stringNodeNum == "null") ? -1 : (std::stoi(stringNodeNum) - 1);
    }
};

class AlgorithmTasks {
private:
    static int32_t IsBalancedBRTree(const std::vector<RBNode> &tree, int32_t nodeNumber, bool &valid);
public:
    static bool ValidateRBTree(const std::vector<RBNode> &treeNodes, int32_t rootNumber);
};


#endif //ALGORITHMTASKS_4_H
