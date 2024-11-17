#include "AlgorithmTasks.h"
#include <queue>

// HeapSort with sink
void AlgorithmTasks::GunmanHeapify(std::vector<int32_t> &gunmanArray, int32_t idx, int32_t n) {
    while (idx * 2 <= n) {
        int32_t childIdx = idx * 2;
        if ((childIdx < n) && gunmanArray[childIdx + 1] > gunmanArray[childIdx]) {
            childIdx++;
        }
        if (gunmanArray[idx] >= gunmanArray[childIdx]) {
            break;
        }
        std::swap(gunmanArray[idx], gunmanArray[childIdx]);
        idx = childIdx;
    }
}

void AlgorithmTasks::GunmanBuildMaxHeap(std::vector<int32_t> &gunmanArray) {
    int32_t n = gunmanArray.size() - 1;

    for (int32_t i = n/2; i >= 1; --i){
        GunmanHeapify(gunmanArray, i, n);
    }
}


void AlgorithmTasks::GunmanHeapSort(std::vector<int32_t> &gunmanArray) {
    int32_t n = gunmanArray.size() - 1;
    GunmanBuildMaxHeap(gunmanArray);

    while(n > 1) {
        std::swap(gunmanArray[1], gunmanArray[n]);
        --n;
        GunmanHeapify(gunmanArray, 1, n);
    }
}

// Counting sort
void AlgorithmTasks::StarDistanceCountingSort(std::vector<int32_t> &starDistanceArray) {
    int32_t minDistance = std::pow(10.0, 6.0) + 1;
    int32_t maxDistance = -std::pow(10.0, 6.0) - 1;

    for (int32_t i = 0; i < starDistanceArray.size(); ++i) {
        minDistance = std::min(minDistance, starDistanceArray[i]);
        maxDistance = std::max(maxDistance, starDistanceArray[i]);
    }

    int32_t diffSize = std::abs(maxDistance - minDistance) + 1;
    std::vector<int32_t> countingArray(diffSize);

    for (int32_t i = 0; i < starDistanceArray.size(); ++i) {
        countingArray[starDistanceArray[i] - minDistance]++;
    }

    int32_t countingPtr = 0;
    int32_t distancePtr = 0;
    while (countingPtr < diffSize) {
        for (int32_t i = 0; i < countingArray[countingPtr]; ++i) {
            starDistanceArray[distancePtr] = countingPtr + minDistance;
            distancePtr++;
        }
        countingPtr++;
    }
}

// Radix sort
void AlgorithmTasks::RadixSort(std::vector<int32_t> &numArray) {
    int32_t n = numArray.size();

    int32_t minNum = INT32_MAX;
    for (int32_t i = 0; i < n; ++i) {
        minNum = std::min(minNum, numArray[i]);
    }

    for (int32_t i = 0; i < n; ++i) {
        numArray[i] -= minNum;
    }

    std::vector<std::queue<int32_t>> digitTable(256);

    for (int32_t k = 0; k < 4; ++k) {

        int32_t byteShift = 8 * k;

        for (int32_t i = 0; i < n; ++i) {
            int32_t curByte = (numArray[i] >> byteShift) & 0xFF;
            digitTable[curByte].emplace(numArray[i]);
        }

        if (digitTable[0].size() == n) {
            digitTable[0] = std::queue<int32_t>();
            continue;
        }

        int32_t basePtr = 0;
        for (int32_t i = 0; i < digitTable.size(); ++i) {
            while (!digitTable[i].empty()) {
                numArray[basePtr] = digitTable[i].front();
                digitTable[i].pop();
                basePtr++;
            }
        }
    }

    for (int32_t i = 0; i < n; ++i) {
        numArray[i] += minNum;
    }
}
