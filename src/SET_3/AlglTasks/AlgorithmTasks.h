#ifndef ALGORITHMTASKS_3_H
#define ALGORITHMTASKS_3_H

#include <vector>

class AlgorithmTasks {
private:
    // Heap sort with sink
    static void GunmanHeapify(std::vector<int32_t> &gunmanArray, int32_t idx, int32_t n);

    static void GunmanBuildMaxHeap(std::vector<int32_t> &gunmanArray);

public:
    // Heap sort with sink
    static void GunmanHeapSort(std::vector<int32_t> &gunmanArray);

    // Counting sort
    static void StarDistanceCountingSort(std::vector<int32_t> &starDistanceArray);

    // Radix sort
    static void RadixSort(std::vector<int32_t> &numArray);
};


#endif //ALGORITHMTASKS_3_H
