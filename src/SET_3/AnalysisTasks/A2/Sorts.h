#ifndef IMPLEMENTATIONDATA_SORTS_H
#define IMPLEMENTATIONDATA_SORTS_H

#include <vector>
#include <cstdint>

class Sorts {
private:
    static void Merge(std::vector<int32_t>& array, int32_t left, int32_t mid, int32_t right);
    static void InsertionSort(std::vector<int32_t>& array, int32_t left, int32_t right);
public:
    static void HybridMergeSort(std::vector<int32_t>& array, int32_t left, int32_t right, int32_t threshold);
    static void BaseMergeSort(std::vector<int32_t >& array, int32_t left, int32_t right);
};


#endif //IMPLEMENTATIONDATA_SORTS_H
