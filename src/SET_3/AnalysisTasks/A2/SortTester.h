#ifndef IMPLEMENTATIONDATA_SORTTESTER_H
#define IMPLEMENTATIONDATA_SORTTESTER_H
#include <cstdint>
#include <string>

class SortTester {
public:
    static void TestBaseMergeSortArrayWithRange(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                         int32_t minVal, int32_t maxVal, int32_t averagingRate);

    static void TestBaseMergeSortReverseSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                                     int32_t minVal, int32_t maxVal, int32_t averagingRate);

    static void TestBaseMergeSortParticleSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                                     int32_t minVal, int32_t maxVal, int32_t averagingRate);

    static void TestHybridMergeSortParticleSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                                      int32_t minVal, int32_t maxVal, int32_t averagingRate, int32_t threshold);

    static void TestHybridMergeSortReverseSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                                        int32_t minVal, int32_t maxVal, int32_t averagingRate, int32_t threshold);

    static void TestHybridMergeSortArrayWithRange(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize, size_t step,
                                                       int32_t minVal, int32_t maxVal, int32_t averagingRate, int32_t threshold);
};


#endif //IMPLEMENTATIONDATA_SORTTESTER_H
