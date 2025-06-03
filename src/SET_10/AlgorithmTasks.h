#ifndef ALGORITHMTASKS_10_H
#define ALGORITHMTASKS_10_H

#include <algorithm>
#include <vector>
#include <cstdint>
#include <random>

struct KnapsackParticleItem {
    uint32_t volume;
    uint32_t cost;
    double unitCost;
};

struct KnapsackParticleItemComparator {
public:
    bool operator()(const KnapsackParticleItem& left, const KnapsackParticleItem& right) {
        return left.unitCost > right.unitCost;
    }
};

struct SegmentPoints {
    int32_t left;
    int32_t right;
};

struct SegmentPointsComparator {
public:
    bool operator()(const SegmentPoints& a, const SegmentPoints& b) {
        return a.right < b.right;
    };
};

struct WeightSegment {
    double left;
    double right;
    double weight;
};

struct WeightSegmentComparator {
public:
    bool operator()(const WeightSegment& a, const WeightSegment& b) {
        return a.right < b.right;
    }
};

struct CostWeightKnapsackItem {
    uint32_t weight;
    uint32_t cost;
};

struct CostWeightVolumeKnapsackItem {
    uint32_t weight;
    uint32_t volume;
    uint32_t cost;
};


class AlgorithmTasks {
public:
    static std::vector<std::vector<int32_t>> FindGoodGrid(uint32_t n, uint32_t m, int32_t c, uint32_t iterations);

    static uint64_t CountNumberOfAuthenticNumSet(uint64_t n, uint32_t k, uint64_t& mod);

    static uint32_t FindMaxKnapsackCostWithWeightVolume(const std::vector<CostWeightVolumeKnapsackItem>& items, uint32_t maxWeight, uint32_t maxVolume);

    static uint32_t FindMaxKnapsackCostWithWeight(const std::vector<CostWeightKnapsackItem>& items, uint32_t maxWeight);

    static uint32_t FindMinSegmentCutTime(std::vector<uint32_t>& points);

    static double FoundMaxWeightCompatibleSegments(std::vector<WeightSegment>& segments);

    static std::vector<int32_t> GetSegmentsMinimalCoveringPoints(std::vector<SegmentPoints>& segments);

    static std::vector<uint32_t> GenerateMax2DiffedSliceNumsTransposition(uint32_t n, uint32_t l, uint32_t r);

    static double CalculateMaxParticleKnapsackPrice(std::vector<KnapsackParticleItem>& items, uint32_t maxVolume);

private:
    static uint32_t CountSameColorRectangles(const std::vector<std::vector<int32_t>> &grid, uint32_t n, uint32_t m);

    static int32_t FindSameColorRectDeltaDiff(const std::vector<std::vector<int32_t>> &grid, uint32_t n, uint32_t m, uint32_t iChanged,
                                       uint32_t jChanged, int32_t oldV, int32_t newV);

    static std::vector<std::vector<uint64_t>> MultMatrix(const std::vector<std::vector<uint64_t>>& A, const std::vector<std::vector<uint64_t>>& B, uint32_t size, uint64_t& mod);

    static std::vector<std::vector<uint64_t>> PowMatrix(std::vector<std::vector<uint64_t>> A, uint64_t p, uint32_t size, uint64_t& mod);

    static std::vector<uint64_t> VecMultMatrix(const std::vector<std::vector<uint64_t>>& M, const std::vector<uint64_t>& vec, uint32_t size, uint64_t& mod);
};


#endif //ALGORITHMTASKS_10_H
