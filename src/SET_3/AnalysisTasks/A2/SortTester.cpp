#include "SortTester.h"
#include "ArrayGenerator.h"
#include <vector>
#include <chrono>
#include <fstream>
#include "Sorts.h"

void SortTester::TestBaseMergeSortArrayWithRange(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize,
                                                 size_t step,
                                                 int32_t minVal, int32_t maxVal, int32_t averagingRate) {

    std::ofstream dataFile(dataFilePath);
    dataFile << "Base Merge Sort\nTests results with random unsorted arrays\n\n";
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateArrayWithRange(curSize, minVal, maxVal);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::BaseMergeSort(array, 0, curSize - 1);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}

void SortTester::TestBaseMergeSortReverseSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize,
                                                 size_t step, int32_t minVal, int32_t maxVal, int32_t averagingRate) {
    std::ofstream dataFile(dataFilePath);
    dataFile << "Base Merge Sort\nTests results with reverse sorted arrays\n\n";
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateReverseSortedArray(curSize, minVal, maxVal);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::BaseMergeSort(array, 0, curSize - 1);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}

void SortTester::TestBaseMergeSortParticleSortedArrays(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize,
                                                  size_t step, int32_t minVal, int32_t maxVal, int32_t averagingRate) {
    std::ofstream dataFile(dataFilePath);
    dataFile << "Base Merge Sort\nTests results with particle sorted arrays\n\n";
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "Number of swapped elements = N/10\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateParticleSortedArray(curSize, minVal, maxVal, curSize/10);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::BaseMergeSort(array, 0, curSize - 1);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}

void SortTester::TestHybridMergeSortParticleSortedArrays(const std::string &dataFilePath, size_t minArrSize,
                                                         size_t maxArrSize, size_t step, int32_t minVal, int32_t maxVal,
                                                         int32_t averagingRate, int32_t threshold) {
    std::ofstream dataFile(dataFilePath);
    dataFile << "Hybrid Merge Sort\nTests results with particle sorted arrays\n\n";
    dataFile << "Insertion sort threshold = " + std::to_string(threshold) + '\n';
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "Number of swapped elements = N/10\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateParticleSortedArray(curSize, minVal, maxVal, curSize/10);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::HybridMergeSort(array, 0, curSize - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}

void SortTester::TestHybridMergeSortReverseSortedArrays(const std::string &dataFilePath, size_t minArrSize,
                                                        size_t maxArrSize, size_t step, int32_t minVal, int32_t maxVal,
                                                        int32_t averagingRate, int32_t threshold) {
    std::ofstream dataFile(dataFilePath);
    dataFile << "Hybrid Merge Sort\nTests results with reverse sorted arrays\n\n";
    dataFile << "Insertion sort threshold = " + std::to_string(threshold) + '\n';
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateReverseSortedArray(curSize, minVal, maxVal);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::HybridMergeSort(array, 0, curSize - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}

void
SortTester::TestHybridMergeSortArrayWithRange(const std::string &dataFilePath, size_t minArrSize, size_t maxArrSize,
                                              size_t step, int32_t minVal, int32_t maxVal, int32_t averagingRate,
                                              int32_t threshold) {
    std::ofstream dataFile(dataFilePath);
    dataFile << "Hybrid Merge Sort\nTests results with random unsorted arrays\n\n";
    dataFile << "Insertion sort threshold = " + std::to_string(threshold) + '\n';
    dataFile << "Range of test arrays size: " + std::to_string(minArrSize) + '-' + std::to_string(maxArrSize) +
                ". With step = " + std::to_string(step) + '\n';
    dataFile << "Range of random values: " + std::to_string(minVal) + '-' + std::to_string(maxVal) + '\n';
    dataFile << "Averaging rate = " + std::to_string(averagingRate) + "\n";
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\n\nN : T\n";

    for (size_t curSize = minArrSize; curSize <= maxArrSize; curSize += step) {
        uint64_t timeSum = 0;
        std::vector<int32_t> array;

        for (int32_t j = 0; j < averagingRate; ++j) {
            array = ArrayGenerator::GenerateArrayWithRange(curSize, minVal, maxVal);

            auto start = std::chrono::high_resolution_clock::now();
            Sorts::HybridMergeSort(array, 0, curSize - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
        }

        double avgTime = (double) timeSum / averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + '\n';
    }

    dataFile.close();
}
