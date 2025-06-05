#include "BBKnapsack.h"

struct BBKnapsackItemNode {
    uint32_t curValue;
    double curWeight;
    double bound;
    size_t depth;
    std::unordered_set<size_t> excluded;

    BBKnapsackItemNode(uint32_t curValue, double curWeight, double bound, size_t depth) {
        this->curWeight = curWeight;
        this->curValue = curValue;
        this->bound = bound;
        this->depth = depth;
    }

    void CalculateBBNodeBound(const std::vector<BBKnapsackItem> &items, double maxWeight) {
        this->bound = 0;

        if (this->curWeight <= maxWeight) {
            double leftWeight = maxWeight;

            for (size_t i = 0; i < items.size(); ++i) {

                if (!this->excluded.contains(i)) {

                    if (items[i].weight <= leftWeight) {
                        bound += items[i].cost;
                        leftWeight -= items[i].weight;
                    } else {
                        bound += leftWeight * items[i].GetUnitCost();
                        leftWeight = 0;
                    }
                }
            }
        }
    }
};

struct BBKnapsackItemNodeComparator {
public:
    bool operator()(const BBKnapsackItemNode &left, const BBKnapsackItemNode &right) {
        return left.bound < right.bound;
    }
};


uint32_t BBKnapsack::FindMaxKnapsackCostWithWeightBB(std::vector<BBKnapsackItem> &items, double maxWeight) {
    std::sort(items.begin(), items.end(), BBKnapsackItemComparator());

    BBKnapsackItemNode initialNode(0, 0, 0, 0);
    initialNode.CalculateBBNodeBound(items, maxWeight);

    std::priority_queue<BBKnapsackItemNode, std::vector<BBKnapsackItemNode>, BBKnapsackItemNodeComparator> itemNodePq;
    itemNodePq.push(initialNode);


    uint32_t curMaxValue = 0;

    while (!itemNodePq.empty()) {
        BBKnapsackItemNode curNode = itemNodePq.top();
        itemNodePq.pop();

        if (curNode.bound > curMaxValue) {
            size_t newDepth = curNode.depth + 1;

            double includedWeight = curNode.curWeight + items[newDepth - 1].weight;
            uint32_t includedValue = curNode.curValue + items[newDepth - 1].cost;
            double includedBound = (includedWeight > maxWeight ? 0 : curNode.bound);
            BBKnapsackItemNode includedNode(
                    includedValue,
                    includedWeight,
                    includedBound,
                    newDepth);
            includedNode.excluded = curNode.excluded;

            if (includedValue > curMaxValue && includedWeight <= maxWeight) {
                curMaxValue = includedValue;
            }

            itemNodePq.push(includedNode);


            BBKnapsackItemNode excludedNode(
                    curNode.curValue,
                    curNode.curWeight,
                    0,
                    newDepth
            );
            excludedNode.excluded = curNode.excluded;
            excludedNode.excluded.insert(newDepth - 1);
            excludedNode.CalculateBBNodeBound(items, maxWeight);

            itemNodePq.push(excludedNode);
        }
    }

    return curMaxValue;
}
