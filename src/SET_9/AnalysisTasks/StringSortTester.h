#ifndef IMPLEMENTATIONDATA_STRINGSORTTESTER_H
#define IMPLEMENTATIONDATA_STRINGSORTTESTER_H

#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>
#include <iostream>


class StringSortTester {
public:
    using SortFunctionType = std::function<void(std::vector<std::string> &, uint64_t &)>;
    using ArrayGeneratorType = std::function<std::vector<std::string>(size_t)>;

    struct SortTestParameters {
        SortFunctionType sortFunc;
        ArrayGeneratorType generateArrayFunc;
        std::string& testName;
        std::string& resultDataFile;
        size_t minArrSize;
        size_t maxArrSize;
        size_t step;
        uint32_t averagingRate;
    };

    static void Run(const SortTestParameters& parameters);
};


#endif //IMPLEMENTATIONDATA_STRINGSORTTESTER_H
