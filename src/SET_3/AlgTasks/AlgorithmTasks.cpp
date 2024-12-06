#include "AlgorithmTasks.h"
#include <queue>
#include <iomanip>
#include <random>

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

// Stable merge sort
void AlgorithmTasks::GunmanStableMerge(std::vector<std::pair<int32_t, int32_t>>& gunmanArray, int32_t left, int32_t mid, int32_t right) {
    size_t left_arr_size = mid - left + 1;
    size_t right_arr_size = right - mid;

    std::vector<std::pair<int32_t, int32_t>> left_arr;
    left_arr.reserve(left_arr_size);
    std::vector<std::pair<int32_t, int32_t>> right_arr;
    right_arr.reserve(right_arr_size);

    for (int32_t i = 0; i < left_arr_size; ++i) {
        left_arr.push_back(gunmanArray[left + i]);
    }
    for (int32_t j = 0; j < right_arr_size; ++j) {
        right_arr.push_back(gunmanArray[mid + 1 + j]);
    }

    size_t i = 0;
    size_t j = 0;
    size_t main_pointer = left;
    while (i < left_arr_size && j < right_arr_size) {
        if (((double)left_arr[i].first / left_arr[i].second) <= ((double)right_arr[j].first / right_arr[j].second)) {
            gunmanArray[main_pointer] = left_arr[i];
            i++;
        } else {
            gunmanArray[main_pointer] = right_arr[j];
            j++;
        }
        main_pointer++;
    }

    while (i < left_arr_size) {
        gunmanArray[main_pointer] = left_arr[i];
        ++i;
        main_pointer++;
    }

    while (j < right_arr_size) {
        gunmanArray[main_pointer] = right_arr[j];
        ++j;
        main_pointer++;
    }
}

void AlgorithmTasks::GunmanStableMergeSort(std::vector<std::pair<int32_t, int32_t>>& gunmanArray, int32_t left, int32_t right) {
    if (left < right) {
        int32_t middle = left + (right - left) / 2;

        GunmanStableMergeSort(gunmanArray, left, middle);
        GunmanStableMergeSort(gunmanArray, middle + 1, right);

        GunmanStableMerge(gunmanArray, left, middle, right);
    }
}


// Monte Carlo binary matrix multiplication check
std::string AlgorithmTasks::ConvertHexToString(const std::string& hex, int32_t size) {
    std::string bin;
    for (int32_t i = 0; i < hex.length(); ++i) {
        bin += ConvertHexTo4Bit(hex[i]);
    }
    bin = bin.substr(0, size);
    return bin;
}

std::string AlgorithmTasks::MultBinMatrixWithVector(const std::string& vector, const std::vector<std::string>& matrix, int32_t n) {
    std::string resultVector;

    for (int32_t i = 0; i < n; ++i) {
        int32_t sum = 0;
        for (int32_t j = 0; j < n; ++j) {
            sum += (int)(vector[j] - '0') & (int)(matrix[i][j] - '0');
        }
        resultVector += std::to_string(sum % 2);
    }

    return resultVector;
};

bool AlgorithmTasks::MonteCarloValidateMatrixMultiplication(const std::vector<std::string> &matrixA, const std::vector<std::string> &matrixB,
                                            const std::vector<std::string> &matrixC,  int32_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::string randomBinaryVector;
    for (int i = 0; i < size; ++i) {
        randomBinaryVector += std::to_string(dis(gen));
    }

    std::string br = MultBinMatrixWithVector(randomBinaryVector, matrixB, size);
    std::string left = MultBinMatrixWithVector(br, matrixA, size);
    std::string right = MultBinMatrixWithVector(randomBinaryVector, matrixC, size);

    for (int32_t i = 0; i < size; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
};

std::string AlgorithmTasks::ConvertHexTo4Bit(char c)
{
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "0000";
    }
}

// Annealing Method N quins correct placement
std::vector<int32_t> AlgorithmTasks::QuinPlacement(int32_t boardSize, int32_t iterCount) {
    std::vector<int32_t> chesBoard(boardSize);
    for (int32_t i = 0; i < boardSize; ++i) {
        chesBoard[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(chesBoard.begin(), chesBoard.end(), gen);

    std::uniform_int_distribution<> dis(0, boardSize * 2);
    std::uniform_real_distribution<> realDist(0.0, 1.0);

    int32_t energy = CountCorrectPlacedQuins(chesBoard);
    double temp = 1;

    std::vector<int32_t> tempChessBoard;
    for (int32_t i = 0; i < iterCount; ++i) {
        if (energy == boardSize) {
            break;
        }

        temp *= 0.99;

        tempChessBoard = chesBoard;
        std::swap(tempChessBoard[dis(gen) % boardSize], tempChessBoard[dis(gen) % boardSize]);
        int32_t newEnergy = CountCorrectPlacedQuins(tempChessBoard);

        int32_t deltaEnergy = newEnergy - energy;

        if (newEnergy > energy || realDist(gen) < std::exp((double)deltaEnergy/temp)) {
            chesBoard = tempChessBoard;
            energy = newEnergy;
        }
    }

    return chesBoard;
}


int32_t AlgorithmTasks::CountCorrectPlacedQuins(const std::vector<int32_t>& chessBoard) {
    int32_t n = chessBoard.size();
    std::vector<int8_t> isCounted(n);

    int32_t correctPlaced = n;

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i + 1; j < n; ++j) {
            if (chessBoard[i] == chessBoard[j] || std::abs(chessBoard[i] - chessBoard[j]) == std::abs(i - j)) {
                if (isCounted[i] == 0) {
                    isCounted[i]++;
                    correctPlaced--;
                }
                if (isCounted[j] == 0) {
                    isCounted[j]++;
                    correctPlaced--;
                }
            }
        }
    }

    return correctPlaced;
}