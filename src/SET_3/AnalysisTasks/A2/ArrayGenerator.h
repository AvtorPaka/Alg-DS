#ifndef IMPLEMENTATIONDATA_ARRAYGENERATOR_H
#define IMPLEMENTATIONDATA_ARRAYGENERATOR_H
#include <vector>
#include <cstdint>

class ArrayGenerator {
public:
    static std::vector<int32_t> GenerateArrayWithRange(size_t size, int32_t min, int32_t max);
    static std::vector<int32_t> GenerateReverseSortedArray(size_t size, int32_t min, int32_t max);
    static std::vector<int32_t> GenerateParticleSortedArray(size_t size, int32_t min, int32_t max, int32_t particleSortedRate);
};


#endif //IMPLEMENTATIONDATA_ARRAYGENERATOR_H
