#include "ArrayGenerator.h"
#include <random>
#include <algorithm>

std::vector<int32_t> ArrayGenerator::GenerateArrayWithRange(size_t size, int32_t min, int32_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    std::vector<int32_t> array(size);
    for (size_t i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }

    return array;
}

std::vector<int32_t> ArrayGenerator::GenerateReverseSortedArray(size_t size, int32_t min, int32_t max) {
    std::vector<int32_t> array = GenerateArrayWithRange(size, min, max);

    std::sort(array.begin(), array.end(), std::greater<>());

    return array;
}

std::vector<int32_t> ArrayGenerator::GenerateParticleSortedArray(size_t size, int32_t min, int32_t max, int32_t particleSortedRate) {
    std::vector<int32_t> array = GenerateArrayWithRange(size, min, max);
    std::sort(array.begin(), array.end());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);

    for (int32_t i = 0; i < particleSortedRate; ++i) {
        std::swap(array[dis(gen)], array[dis(gen)]);
    }

    return array;
}