#include "AlgorithmTasks.h"

#include <vector>

int32_t AlgorithmTasks::IsBalancedBRTree(const std::vector<RBNode> &tree, int32_t nodeNumber, bool &valid) {
    if (nodeNumber == -1) {
        return 1;
    }

    RBNode curNode = tree[nodeNumber];

    int32_t leftUnderTreeBlackCount = IsBalancedBRTree(tree, curNode.leftNodeNumber, valid);
    int32_t rightUnderTreeBlackCount = IsBalancedBRTree(tree, curNode.rightNodeNumber, valid);

    if (leftUnderTreeBlackCount != rightUnderTreeBlackCount) {
        valid = false;
    }

    return leftUnderTreeBlackCount + (curNode.redColor ? 0 : 1);
}

bool AlgorithmTasks::ValidateRBTree(const std::vector<RBNode> &treeNodes, int32_t rootNumber) {
    if (treeNodes[rootNumber].redColor) {
        return false;
    }

    for (int32_t i = 0; i < treeNodes.size(); ++i) {
        RBNode curNode = treeNodes[i];
        if (curNode.leftNodeNumber != -1) {
            if (curNode.redColor && treeNodes[curNode.leftNodeNumber].redColor) {
                return false;
            }
            if (treeNodes[curNode.leftNodeNumber].key >= curNode.key) {
                return false;
            }
        }
        if (curNode.rightNodeNumber != -1) {
            if (curNode.redColor && treeNodes[curNode.rightNodeNumber].redColor) {
                return false;
            }
            if (treeNodes[curNode.rightNodeNumber].key <= curNode.key) {
                return false;
            }
        }
    }

    bool isBalancedRBTree = true;
    IsBalancedBRTree(treeNodes, rootNumber, isBalancedRBTree);

    return isBalancedRBTree;
}
