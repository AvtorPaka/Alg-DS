#ifndef IMPLEMENTATIONDATA_STRINGSORTS_H
#define IMPLEMENTATIONDATA_STRINGSORTS_H

#include <vector>
#include <string>
#include <cstdint>
#include <utility>

class StringSorts {
public:
    static void HybridMSDRadixSort(std::vector<std::string>& array, uint64_t& symbolCompareCount, size_t alphabetSize = 123, size_t switchThreshold = 74);
    // symbolCompareCount just for signature compatibility with over sorts, always 0 as expected
    static void MSDRadixSort(std::vector<std::string>& array, uint64_t& symbolCompareCount, size_t alphabetSize = 123);

    static void LCPMergeSort(std::vector<std::string>& array, uint64_t& symbolCompareCount);
    static void TernaryQuickSort(std::vector<std::string>& array, uint64_t& symbolCompareCount);

    static void BasicMergeSort(std::vector<std::string>& array, uint64_t& symbolCompareCount);
    static void BasicQuickSort(std::vector<std::string>& array, uint64_t& symbolCompareCount);

private:
    static void HybridMSDRadixSort(std::vector<std::string>& array, size_t left, size_t right, size_t depth, size_t alphabetSize, size_t switchThreshold, std::vector<std::string>& aux, uint64_t& symbolCompareCount);
    static void MSDRadixSort(std::vector<std::string>& array, size_t left, size_t right, size_t depth, size_t alphabetSize, std::vector<std::string>& aux);
    static int32_t GetStingDepthCharCode(const std::string& string, size_t depth);

    static void LCPMergeSort(std::vector<std::string>& array, std::vector<size_t>& lcp, size_t left, size_t right, uint64_t& symbolCompareCount);
    static void LCPMerge(std::vector<std::string>& array, std::vector<size_t>& lcp, size_t left, size_t  mid, size_t right, uint64_t& symbolCompareCount);
    static std::pair<bool, size_t> LCPCompare(const std::string& left, const std::string& right, size_t k, uint64_t& symbolCompareCount);

    static void TernaryQuickSort(std::vector<std::string>& array, size_t left, size_t  right, size_t compareDepth, uint64_t& symbolCompareCount);
    static char GetStringDepthChar(const std::string& string, size_t depth);

    static void BasicQuickSort(std::vector<std::string>& array, size_t left, size_t right, uint64_t& symbolCompareCount);
    static size_t BasicPartition(std::vector<std::string>& array, size_t left, size_t pivot, size_t right, uint64_t& symbolCompareCount);

    static void BasicMergeSort(std::vector<std::string>& array, size_t left, size_t right, uint64_t& symbolCompareCount);
    static void BasicMerge(std::vector<std::string>& array, size_t left, size_t mid, size_t right, uint64_t& symbolCompareCount);

    static bool BasicCompare(const std::string& left, const std::string& right, uint64_t& symbolCompareCount);
};


#endif //IMPLEMENTATIONDATA_STRINGSORTS_H
