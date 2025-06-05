#ifndef IMPLEMENTATIONDATA_BBKNAPSACK_H
#define IMPLEMENTATIONDATA_BBKNAPSACK_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_set>

struct BBKnapsackItem {
    double weight;
    uint32_t cost;

    double GetUnitCost() const {
        return (double) cost / weight;
    }
};

struct BBKnapsackItemComparator {
public:
    bool operator()(const BBKnapsackItem &left, const BBKnapsackItem &right) {
        return left.GetUnitCost() > right.GetUnitCost();
    }
};

class BBKnapsack {
public:
    static uint32_t FindMaxKnapsackCostWithWeightBB(std::vector<BBKnapsackItem> &items, double maxWeight);
};


#endif //IMPLEMENTATIONDATA_BBKNAPSACK_H
