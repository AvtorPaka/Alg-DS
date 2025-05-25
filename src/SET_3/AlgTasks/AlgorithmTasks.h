#ifndef ALGORITHMTASKS_3_H
#define ALGORITHMTASKS_3_H

#include <vector>

class AlgorithmTasks {
private:
    // Heap sort with sink
    static void GunmanHeapify(std::vector<int32_t> &gunmanArray, int32_t idx, int32_t n);

    static void GunmanBuildMaxHeap(std::vector<int32_t> &gunmanArray);

    // Stable merge sort
    static void GunmanStableMerge(std::vector<std::pair<int32_t, int32_t>>& gunmanArray, int32_t left, int32_t mid, int32_t right);

    // Monte Carlo binary matrix multiplication check
    static std::string MultBinMatrixWithVector(const std::string& vector, const std::vector<std::string>& matrix, int32_t n);

    static std::string ConvertHexTo4Bit(char c);

    // Annealing Method N quins correct placement
    static int32_t CountCorrectPlacedQuins(const std::vector<int32_t>& chessBoard);


public:
    // Heap sort with sink
    static void HeapSort(std::vector<int32_t> &gunmanArray);

    // Counting sort
    static void CountingSort(std::vector<int32_t> &starDistanceArray);

    // Radix sort
    static void RadixSort(std::vector<int32_t> &numArray);

    // Stable merge sort
    static void StableMergeSort(std::vector<std::pair<int32_t, int32_t>>& gunmanArray, int32_t left, int32_t right);

    // Monte Carlo binary matrix multiplication check
    static bool MonteCarloValidateMatrixMultiplication(const std::vector<std::string> &matrixA, const std::vector<std::string> &matrixB,
                                                const std::vector<std::string> &matrixC, int32_t size);

    static std::string ConvertHexToString(const std::string& hex, int32_t size);

    // Annealing Method N quins correct placement
    // best iterCount = 30k for 200x200 board
    static std::vector<int32_t> QuinPlacement(int32_t boardSize, int32_t iterCount);
};


#endif //ALGORITHMTASKS_3_H
