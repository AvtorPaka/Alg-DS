#include "StringSorts.h"

#include <algorithm>

void StringSorts::BasicMergeSort(std::vector<std::string> &array, uint64_t &symbolCompareCount) {
    if (array.size() < 2) {
        return;
    }
    BasicMergeSort(array, 0, array.size() - 1, symbolCompareCount);
}


void
StringSorts::BasicMergeSort(std::vector<std::string> &array, size_t left, size_t right, uint64_t &symbolCompareCount) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        BasicMergeSort(array, left, mid, symbolCompareCount);
        BasicMergeSort(array, mid + 1, right, symbolCompareCount);

        BasicMerge(array, left, mid, right, symbolCompareCount);
    }
}


void StringSorts::BasicMerge(std::vector<std::string> &array, size_t left, size_t mid, size_t right,
                             uint64_t &symbolCompareCount) {
    size_t leftSize = mid - left + 1;
    size_t rightSize = right - mid;

    std::vector<std::string> leftArray(leftSize);
    std::vector<std::string> rightArray(rightSize);
    for (size_t i = 0; i < leftSize; ++i) {
        leftArray[i] = array[left + i];
    }
    for (size_t i = 0; i < rightSize; ++i) {
        rightArray[i] = array[mid + i + 1];
    }

    size_t mainPointer = left;
    size_t i = 0;
    size_t j = 0;
    while (i < leftSize && j < rightSize) {
        if (BasicCompare(leftArray[i], rightArray[j], symbolCompareCount)) {
            array[mainPointer] = leftArray[i++];
        } else {
            array[mainPointer] = rightArray[j++];
        }
        mainPointer++;
    }

    while (i < leftSize) {
        array[mainPointer++] = leftArray[i++];
    }

    while (j < rightSize) {
        array[mainPointer++] = rightArray[j++];
    }
}

void StringSorts::BasicQuickSort(std::vector<std::string> &array, uint64_t &symbolCompareCount) {
    if (array.size() < 2) {
        return;
    }
    BasicQuickSort(array, 0, array.size() - 1, symbolCompareCount);
}

void
StringSorts::BasicQuickSort(std::vector<std::string> &array, size_t left, size_t right, uint64_t &symbolCompareCount) {
    if (left < right) {
        size_t pivotIdx = left + (right - left) / 2;
        size_t partitionIdx = BasicPartition(array, left, pivotIdx, right, symbolCompareCount);

        if (partitionIdx > 0) {
            BasicQuickSort(array, left, partitionIdx - 1, symbolCompareCount);
        }
        BasicQuickSort(array, partitionIdx + 1, right, symbolCompareCount);
    }
}


size_t StringSorts::BasicPartition(std::vector<std::string> &array, size_t left, size_t pivot, size_t right,
                                   uint64_t &symbolCompareCount) {
    std::string pivotVal = array[pivot];

    std::swap(array[pivot], array[right]);
    size_t storeIdx = left;

    for (size_t i = left; i < right; ++i) {
        if (BasicCompare(array[i], pivotVal, symbolCompareCount)) {
            std::swap(array[i], array[storeIdx++]);
        }
    }

    std::swap(array[storeIdx], array[right]);
    return storeIdx;
}

bool StringSorts::BasicCompare(const std::string &left, const std::string &right, uint64_t &symbolCompareCount) {
    size_t minLen = std::min(left.size(), right.size());

    for (size_t i = 0; i < minLen; ++i) {
        symbolCompareCount++;

        if (left[i] < right[i]) {
            return true;
        } else if (left[i] > right[i]) {
            return false;
        }
    }

    return left.size() < right.size();
}


void StringSorts::TernaryQuickSort(std::vector<std::string> &array, uint64_t &symbolCompareCount) {
    if (array.size() < 2) {
        return;
    }
    TernaryQuickSort(array, 0, array.size() - 1, 0, symbolCompareCount);
}

void StringSorts::TernaryQuickSort(std::vector<std::string> &array, size_t left, size_t right, size_t compareDepth,
                                   uint64_t &symbolCompareCount) {

    if (right == (size_t) -1 || left >= right) {
        return;
    }

    size_t pivotIdx = left + (right - left) / 2;
    char pivotCompareChar = GetStringDepthChar(array[pivotIdx], compareDepth);

    size_t leftTern = left;
    size_t rightTern = right;
    size_t i = left;

    char curCompareChar;
    while (i <= rightTern) {
        curCompareChar = GetStringDepthChar(array[i], compareDepth);

        if (curCompareChar < pivotCompareChar) {
            std::swap(array[i++], array[leftTern++]);
        } else if (curCompareChar > pivotCompareChar) {
            std::swap(array[i], array[rightTern--]);
        } else {
            ++i;
        }

        symbolCompareCount++;
    }

    if (leftTern > 0) {
        TernaryQuickSort(array, left, leftTern - 1, compareDepth, symbolCompareCount);
    }
    if (pivotCompareChar != '\0') {
        TernaryQuickSort(array, leftTern, rightTern, compareDepth + 1, symbolCompareCount);
    }
    TernaryQuickSort(array, rightTern + 1, right, compareDepth, symbolCompareCount);
}


char StringSorts::GetStringDepthChar(const std::string &string, size_t depth) {
    return depth < string.size() ? string[depth] : '\0';
}

void StringSorts::LCPMergeSort(std::vector<std::string> &array, uint64_t &symbolCompareCount) {
    if (array.size() < 2) {
        return;
    }

    std::vector<size_t> lcp(array.size(), 0);
    LCPMergeSort(array, lcp, 0, array.size() - 1, symbolCompareCount);
}

void StringSorts::LCPMergeSort(std::vector<std::string> &array, std::vector<size_t> &lcp, size_t left, size_t right,
                               uint64_t &symbolCompareCount) {

    if (left >= right) {
        return;
    }

    size_t mid = left + (right - left) / 2;

    LCPMergeSort(array, lcp, left, mid, symbolCompareCount);
    LCPMergeSort(array, lcp, mid + 1, right, symbolCompareCount);

    LCPMerge(array, lcp, left, mid, right, symbolCompareCount);
}

void StringSorts::LCPMerge(std::vector<std::string> &array, std::vector<size_t> &lcp, size_t left, size_t mid,
                           size_t right, uint64_t &symbolCompareCount) {
    size_t leftSize = mid - left + 1;
    size_t rightSize = right - mid;

    std::vector<std::string> leftArray(leftSize);
    std::vector<std::string> rightArray(rightSize);

    std::vector<size_t> lcpLeft(leftSize);
    std::vector<size_t> lcpRight(rightSize);

    for (size_t i = 0; i < leftSize; ++i) {
        leftArray[i] = array[left + i];
        lcpLeft[i] = lcp[left + i];
    }
    for (size_t i = 0; i < rightSize; ++i) {
        rightArray[i] = array[mid + i + 1];
        lcpRight[i] = lcp[mid + i + 1];
    }

    size_t mainPointer = left;
    size_t i = 0;
    size_t j = 0;


    while (i < leftSize && j < rightSize) {

        if (lcpLeft[i] > lcpRight[j]) {
            array[mainPointer] = leftArray[i];
            lcp[mainPointer] = lcpLeft[i];
            i++;
        } else if (lcpLeft[i] < lcpRight[j]) {
            array[mainPointer] = rightArray[j];
            lcp[mainPointer] = lcpRight[j];
            j++;

        } else {
            size_t commonLCP = lcpLeft[i];

            auto lcpPair = LCPCompare(leftArray[i], rightArray[j], commonLCP, symbolCompareCount);
            bool leftSOE = std::get<0>(lcpPair);
            size_t newLcp = std::get<1>(lcpPair);

            if (leftSOE) {
                array[mainPointer] = leftArray[i];
                lcp[mainPointer] = commonLCP;
                lcpRight[j] = newLcp;
                i++;

            } else {
                array[mainPointer] = rightArray[j];
                lcp[mainPointer] = commonLCP;
                lcpLeft[i] = newLcp;
                j++;
            }
        }

        mainPointer++;
    }

    while (i < leftSize) {
        array[mainPointer] = leftArray[i];
        lcp[mainPointer++] = lcpLeft[i++];
    }

    while (j < rightSize) {
        array[mainPointer] = rightArray[j];
        lcp[mainPointer++] = lcpRight[j++];
    }
}

std::pair<bool, size_t>
StringSorts::LCPCompare(const std::string &left, const std::string &right, size_t k, uint64_t &symbolCompareCount) {
    size_t lcpSize = k;

    size_t minLen = std::min(left.size(), right.size());

    for (size_t i = k; i < minLen; ++i) {
        symbolCompareCount++;

        if (left[i] < right[i]) {
            return std::make_pair(true, lcpSize);
        }

        if (left[i] > right[i]) {
            return std::make_pair(false, lcpSize);
        }

        lcpSize++;
    }

    return std::make_pair(left.size() <= right.size(), lcpSize);
}

int32_t StringSorts::GetStingDepthCharCode(const std::string& string, size_t depth) {
    return depth < string.size() ? static_cast<unsigned char>(string[depth]) : -1;
}

void StringSorts::MSDRadixSort(std::vector<std::string> &array, uint64_t& symbolCompareCount, size_t alphabetSize) {
    if (array.size() < 2) {
        return;
    }
    symbolCompareCount = 0;
    std::vector<std::string> aux(array.size());
    MSDRadixSort(array, 0, array.size() - 1, 0, alphabetSize, aux);
}


void StringSorts::HybridMSDRadixSort(std::vector<std::string> &array, uint64_t &symbolCompareCount, size_t alphabetSize, size_t switchThreshold) {
    if (array.size() < 2) {
        return;
    }
    std::vector<std::string> aux(array.size());
    HybridMSDRadixSort(array, 0, array.size() - 1, 0, alphabetSize, switchThreshold, aux, symbolCompareCount);
}

void StringSorts::MSDRadixSort(std::vector<std::string> &array, size_t left, size_t right, size_t depth, size_t alphabetSize,
                                     std::vector<std::string> &aux) {
    if (right <= left) {
        return;
    }

    std::vector<size_t> counts(alphabetSize + 1, 0);

    for (size_t i = left; i <= right; ++i) {
        counts[GetStingDepthCharCode(array[i], depth) + 1]++;
    }

    std::vector<size_t> diffCounts = counts;
    counts[0] = 0;
    for (size_t i = 0; i < alphabetSize; ++i) {
        counts[i + 1] = counts[i] + diffCounts[i];
    }

    std::vector<size_t> savedCounts = counts;
    for (size_t i = left; i <= right; ++i) {
        int32_t charCode = GetStingDepthCharCode(array[i], depth);
        size_t bucketIdx = charCode + 1;
        aux[counts[bucketIdx]++] = array[i];
    }

    for (size_t i = 0; i <= right - left; ++i) {
        array[left + i] = aux[i];
    }

    for (size_t i = 0; i < alphabetSize; ++i) {
        size_t curBucketIdx = i + 1;

        size_t auxStart = savedCounts[curBucketIdx];
        size_t nextAuxStart = curBucketIdx < alphabetSize ? savedCounts[curBucketIdx + 1] : (right - left + 1);

        if (nextAuxStart > auxStart) {
            size_t sub_low = left + auxStart;
            size_t sub_high = left + nextAuxStart - 1;
            MSDRadixSort(array, sub_low, sub_high, depth + 1, alphabetSize, aux);
        }
    }
}

void StringSorts::HybridMSDRadixSort(std::vector<std::string> &array, size_t left, size_t right, size_t depth, size_t alphabetSize, size_t switchThreshold,
                                     std::vector<std::string> &aux, uint64_t &symbolCompareCount) {
    if (right <= left) {
        return;
    }

    size_t subArraySize = right - left + 1;
    if (subArraySize < switchThreshold) {
        TernaryQuickSort(array, left, right, depth, symbolCompareCount);
        return;
    }

    std::vector<size_t> counts(alphabetSize + 1, 0);

    for (size_t i = left; i <= right; ++i) {
        counts[GetStingDepthCharCode(array[i], depth) + 1]++;
    }

    std::vector<size_t> diffCounts = counts;
    counts[0] = 0;
    for (size_t i = 0; i < alphabetSize; ++i) {
        counts[i + 1] = counts[i] + diffCounts[i];
    }

    std::vector<size_t> savedCounts = counts;
    for (size_t i = left; i <= right; ++i) {
        int32_t charCode = GetStingDepthCharCode(array[i], depth);
        size_t bucketIdx = charCode + 1;
        aux[counts[bucketIdx]++] = array[i];
    }

    for (size_t i = 0; i <= right - left; ++i) {
        array[left + i] = aux[i];
    }

    for (size_t i = 0; i < alphabetSize; ++i) {
        size_t curBucketIdx = i + 1;

        size_t auxStart = savedCounts[curBucketIdx];
        size_t nextAuxStart = curBucketIdx < alphabetSize ? savedCounts[curBucketIdx + 1] : (right - left + 1);

        if (nextAuxStart > auxStart) {
            size_t sub_low = left + auxStart;
            size_t sub_high = left + nextAuxStart - 1;
            HybridMSDRadixSort(array, sub_low, sub_high, depth + 1, alphabetSize, switchThreshold, aux, symbolCompareCount);
        }
    }
}