#include "StringSortTester.h"

void StringSortTester::Run(const StringSortTester::SortTestParameters& parameters) {

    std::ofstream dataFile(parameters.resultDataFile);
    std::string divider = '\n' + std::string(20, '-') + '\n';
    dataFile << parameters.testName << divider;

    dataFile << "Size: " + std::to_string(parameters.minArrSize) + '-' + std::to_string(parameters.maxArrSize) << '\n';
    dataFile << "Step: " + std::to_string(parameters.step) + '\n';
    dataFile << "Averaging rate: " + std::to_string(parameters.averagingRate) << '\n';
    dataFile << "Strings lengths: 10-200" << divider;
    dataFile << "N - array size\nT - averaged elapsed time (in microseconds)\nC - averaged number of symbol compares\n\nN : T : C\n";

    std::cout << "Start running\n" << parameters.testName << "\nbenchmark." << '\n';
    for (size_t curSize = parameters.minArrSize; curSize <= parameters.maxArrSize; curSize += parameters.step) {

        std::cout << "Running for size: " << std::to_string(curSize) << '\n';

        uint64_t timeSum = 0;
        uint64_t symbolComparesSum = 0;
        std::vector<std::string> array;
        uint64_t symbolCompares = 0;

        for (int32_t j = 0; j < parameters.averagingRate; ++j) {
            array = parameters.generateArrayFunc(curSize);

            auto start = std::chrono::high_resolution_clock::now();
            parameters.sortFunc(array, symbolCompares);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;

            uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            timeSum += microsec;
            symbolComparesSum += symbolCompares;
            symbolCompares = 0;
        }

        double avgTime = (double) timeSum / parameters.averagingRate;
        double avgCompares = (double) symbolComparesSum / parameters.averagingRate;
        dataFile << std::to_string(curSize) + " : " + std::to_string(avgTime) + " : " + std::to_string(avgCompares) + '\n';
    }

    std::cout << "Benchmark over.";
    dataFile.close();
}
