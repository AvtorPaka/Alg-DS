#include "FindMaxAnagram.h"
#include <random>

std::tuple<int32_t, int32_t, int32_t>
FindMaxAnagram::FindAnagram(const std::vector<int32_t> &arrayA, const std::vector<int32_t> &arrayB, int32_t minArrSize) {
    auto hashes = GenerateHashes(arrayA, arrayB);

    int32_t maxSegmentSize = minArrSize;
    for (int32_t curSegmentSize = maxSegmentSize; curSegmentSize >= 1; --curSegmentSize) {
        std::unordered_map<uint64_t, int32_t> sum_pos;

        uint64_t curSum = 0;
        for (int32_t i = 0; i < arrayA.size(); ++i) {
            curSum += hashes[arrayA[i]];
            if (i >= curSegmentSize) {
                curSum -= hashes[arrayA[i - curSegmentSize]];
            }
            if (i >= curSegmentSize - 1) {
                sum_pos[curSum] = i - curSegmentSize + 1;
            }
        }

        curSum = 0;
        for (int32_t i = 0; i < arrayB.size(); ++i) {
            curSum += hashes[arrayB[i]];
            if (i >= curSegmentSize) {
                curSum -= hashes[arrayB[i - curSegmentSize]];
            }
            if (i >= curSegmentSize - 1 && sum_pos.count(curSum)) {
                return {curSegmentSize, sum_pos[curSum] + 1, i - curSegmentSize + 2};
            }
        }
    }
    return {0, -1, -1};
}


std::unordered_map<int32_t, uint64_t>
FindMaxAnagram::GenerateHashes(const std::vector<int32_t> &nums, const std::vector<int32_t> &numsTwo) {
    std::mt19937_64 rng(std::random_device{}());
    std::unordered_map<int32_t, uint64_t> hash_map;

    for (int32_t i = 0; i < numsTwo.size(); ++i) {
        if (!hash_map.contains(nums[i])) {
            hash_map[nums[i]] = rng();
        }
    }

    for (int32_t i = 0; i < numsTwo.size(); ++i) {
        if (!hash_map.contains(numsTwo[i])) {
            hash_map[numsTwo[i]] = rng();
        }
    }

    return hash_map;
}