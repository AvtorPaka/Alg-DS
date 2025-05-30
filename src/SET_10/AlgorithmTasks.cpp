#include "AlgorithmTasks.h"

double AlgorithmTasks::CalculateMaxParticleKnapsackPrice(std::vector<KnapsackParticleItem>& items, uint32_t maxVolume) {
    uint32_t leftVolume = maxVolume;
    double maxCost = 0;

    std::sort(items.begin(), items.end(), KnapsackParticleItemComparator());

    KnapsackParticleItem curItem{};
    for (size_t i = 0; i < items.size(); ++i) {

        curItem = items[i];
        if (curItem.volume <= leftVolume) {
            maxCost += curItem.cost;
            leftVolume -= curItem.volume;
        } else {
            maxCost += leftVolume * curItem.unitCost;
            break;
        }
    }

    return maxCost;
}

// only god and i know what this code does
std::vector<uint32_t> AlgorithmTasks::GenerateMax2DiffedSliceNumsTransposition(uint32_t n, uint32_t l, uint32_t r) {
    std::vector<uint32_t> maxSliceTransposition(n);

    uint32_t midSliceIdx = (l + (r - l)/2);
    uint32_t maxNum = n;
    uint32_t predMaxNum = maxNum - 1;

    if (n == 1) {
        maxSliceTransposition[midSliceIdx] = maxNum;
        return maxSliceTransposition;
    }

    std::vector<bool> numTaken(n + 1, false);
    maxSliceTransposition[midSliceIdx] = maxNum;
    numTaken[maxNum] = true;

    uint32_t leftPartSize = midSliceIdx;
    int32_t rightPartSize;

    if (midSliceIdx + 1 < n) {
        maxSliceTransposition[midSliceIdx + 1] = predMaxNum;
        numTaken[predMaxNum] = true;
        rightPartSize = n - midSliceIdx - 2;
    } else {
        rightPartSize = 0;
    }


    if (leftPartSize < rightPartSize) {

        int32_t leftSlideIdx = midSliceIdx - 1;
        uint32_t leftFillNum = maxNum - 2;
        while (leftSlideIdx >= 0) {
            maxSliceTransposition[leftSlideIdx] = leftFillNum;
            numTaken[leftFillNum] = true;
            leftSlideIdx--;
            leftFillNum -= 2;
        }

        uint32_t rightSlideIdx = midSliceIdx + 1;
        uint32_t  rightSlideNum = predMaxNum;
        uint32_t curDiff;
        while (rightSlideIdx + 1 < n) {
            curDiff = !numTaken[rightSlideNum - 1] ? 1 :  2;
            rightSlideNum -= curDiff;
            maxSliceTransposition[++rightSlideIdx] = rightSlideNum;
            numTaken[rightSlideNum] = true;
        }

    } else {

        uint32_t rightSideIdx = midSliceIdx + 2;
        uint32_t rightFillNum = predMaxNum - 2;
        while (rightSideIdx < n) {
            maxSliceTransposition[rightSideIdx] = rightFillNum;
            numTaken[rightFillNum] = true;
            rightSideIdx++;
            rightFillNum -= 2;
        }

        int32_t leftSlideIdx = midSliceIdx;
        uint32_t  leftSlideNum = maxNum;
        uint32_t curDiff;
        while (leftSlideIdx - 1 >= 0) {
            curDiff = !numTaken[leftSlideNum - 1] ? 1 :  2;
            leftSlideNum -= curDiff;
            maxSliceTransposition[--leftSlideIdx] = leftSlideNum;
            numTaken[leftSlideNum] = true;
        }
    }


    return maxSliceTransposition;
}

std::vector<int32_t> AlgorithmTasks::GetSegmentsMinimalCoveringPoints(std::vector<SegmentPoints>& segments) {
    std::vector<int32_t> points;

    std::sort(segments.begin(), segments.end(), SegmentPointsComparator());

    points.push_back(segments[0].right);

    for (size_t i = 0; i < segments.size(); ++i) {
        if (segments[i].left > points.back()) {
            points.push_back(segments[i].right);
        }
    }

    return points;
}

double AlgorithmTasks::FoundMaxWeightCompatibleSegments(std::vector<WeightSegment>& segments) {
    size_t n = segments.size();
    std::sort(segments.begin(), segments.end(), WeightSegmentComparator());

    std::vector<size_t> maxCompatibleSegmentIdx(n + 1);

    size_t maxCompIdx = 0;
    for (int32_t i = 0; i < n; ++i) {

        for (int32_t j = i - 1; j >= 0; --j) {
            if (segments[i].left >= segments[j].right) {
                maxCompIdx =  j + 1;
                break;
            }
        }

        maxCompatibleSegmentIdx[i + 1] = maxCompIdx;
        maxCompIdx = 0;
    }

    std::vector<double> maxSubSegmentsWeight(n + 1, 0);

    for (int32_t i = 1; i < n + 1; ++i) {
        maxSubSegmentsWeight[i] = std::max(maxSubSegmentsWeight[i - 1], segments[i - 1].weight + maxSubSegmentsWeight[maxCompatibleSegmentIdx[i]]);
    }

    return maxSubSegmentsWeight.back();
}

uint32_t AlgorithmTasks::FindMaxKnapsackCostWithWeight(const std::vector<CostWeightKnapsackItem>& items, uint32_t maxWeight) {
    size_t n = items.size();
    std::vector<uint32_t> prevMaxCost(maxWeight + 1, 0);
    std::vector<uint32_t> curMaxCost(maxWeight + 1, 0);

    for (size_t i = 0; i < n; ++i) {

        for (size_t w = 0; w < maxWeight + 1; ++w) {
            if (items[i].weight > w) {
                curMaxCost[w] = prevMaxCost[w];
            } else {
                curMaxCost[w] = std::max(prevMaxCost[w], items[i].cost + prevMaxCost[w - items[i].weight]);
            }
        }

        prevMaxCost = curMaxCost;
        curMaxCost = std::vector<uint32_t>(maxWeight + 1, 0);
    }

    return prevMaxCost.back();
}

uint32_t AlgorithmTasks::FindMinSegmentCutTime(std::vector<uint32_t>& points) {
    size_t n = points.size();
    std::vector<std::vector<uint32_t>> minSegmentCutCost(n, std::vector<uint32_t>(n, 0));

    for (uint32_t innerPoints = 2; innerPoints < n; ++innerPoints) {
        for (uint32_t i = 0; i < n - innerPoints; ++i) {
            uint32_t j = i + innerPoints;
            minSegmentCutCost[i][j] = UINT32_MAX;
            uint32_t curSegmentLength = points[j] - points[i];

            for (uint32_t k = i + 1; k < j; ++k) {
                minSegmentCutCost[i][j] = std::min(minSegmentCutCost[i][j], curSegmentLength + minSegmentCutCost[i][k] + minSegmentCutCost[k][j]);
            }
        }
    }

    return minSegmentCutCost[0][n - 1];
}

uint32_t AlgorithmTasks::FindMaxKnapsackCostWithWeightVolume(const std::vector<CostWeightVolumeKnapsackItem>& items, uint32_t maxWeight, uint32_t maxVolume) {
    size_t n = items.size();
    std::vector<std::vector<uint32_t>> prevMaxCost(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));
    std::vector<std::vector<uint32_t>> curMaxCost(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));

    for (size_t i = 0; i < n; ++i) {
        const CostWeightVolumeKnapsackItem& curItem = items[i];

        for (size_t w = 0; w < maxWeight + 1; ++w) {
            for (size_t v = 0; v < maxVolume + 1; ++v) {
                if (curItem.weight > w || curItem.volume > v) {
                    curMaxCost[w][v] = prevMaxCost[w][v];
                } else {
                    curMaxCost[w][v] = std::max(prevMaxCost[w][v], items[i].cost + prevMaxCost[w - curItem.weight][v - curItem.volume]);
                }
            }
        }

        prevMaxCost = curMaxCost;
        curMaxCost = std::vector<std::vector<uint32_t>>(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));;
    }

    return prevMaxCost[maxWeight][maxVolume];
}