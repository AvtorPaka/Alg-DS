#include "AlgorithmTasks.h"
#include <iostream>

void AlgorithmTasks::IntervalMerge(std::vector<Interval> &shards, size_t left, size_t mid, size_t right) {
    size_t left_arr_size = mid - left + 1;
    size_t right_arr_size = right - mid;

    std::vector<Interval> left_arr;
    left_arr.reserve(left_arr_size);
    std::vector<Interval> right_arr;
    right_arr.reserve(right_arr_size);

    for (int32_t i = 0; i < left_arr_size; ++i) {
        left_arr.push_back(shards[left + i]);
    }
    for (int32_t j = 0; j < right_arr_size; ++j) {
        right_arr.push_back(shards[mid + 1 + j]);
    }

    size_t i = 0;
    size_t j = 0;
    size_t main_pointer = left;
    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i].left <= right_arr[j].left) {
            shards[main_pointer] = left_arr[i];
            i++;
        } else {
            shards[main_pointer] = right_arr[j];
            j++;
        }
        main_pointer++;
    }

    while (i < left_arr_size) {
        shards[main_pointer] = left_arr[i];
        ++i;
        main_pointer++;
    }

    while (j < right_arr_size) {
        shards[main_pointer] = right_arr[j];
        ++j;
        main_pointer++;
    }
}

void AlgorithmTasks::IntervalMergeSort(std::vector<Interval> &shards, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        IntervalMergeSort(shards, left, mid);
        IntervalMergeSort(shards, mid + 1, right);

        IntervalMerge(shards, left, mid, right);
    }
}

void AlgorithmTasks::ByakuyaBankai(std::vector<Interval> &shards, size_t n) {
    IntervalMergeSort(shards, 0, n - 1);

    Interval maxInterval = Interval(1, 0);
    Interval maxRightSideInterval = shards[0];

    for (int32_t i = 1; i < n; ++i) {
        Interval curInterval = maxRightSideInterval.overlap(shards[i]);

        if (curInterval.length() > maxInterval.length()) {
            maxInterval = curInterval;
        }

        if (shards[i].right > maxRightSideInterval.right) {
            maxRightSideInterval = shards[i];
        }
    }

    std::cout << maxInterval.length() << std::endl;
    if (maxInterval.length() > 0) {
        std::cout << maxInterval.left << ' ' << maxInterval.right << std::endl;
    }
}

// KARATSUBA 64 multiplication
// | down
// v

std::vector<int32_t>
AlgorithmTasks::NaiveMultiplication(const std::vector<int32_t> &numOne, const std::vector<int32_t> &numTwo) {
    size_t n1 = numOne.size();
    size_t n2 = numTwo.size();
    std::vector<int32_t> result(n1 + n2);

    for (int32_t i = 0; i < n1; ++i) {
        for (int32_t j = 0; j < n2; ++j) {
            int32_t curNum = numOne[i] * numTwo[j];
            result[i + j] += curNum;
            if (result[i + j] >= 10) {
                result[i + j + 1] += result[i + j] / 10;
                result[i + j] %= 10;
            }
        }
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

// KARATSUBA 64 multiplication
std::vector<int32_t> AlgorithmTasks::FirstAncientSkill(std::vector<int32_t> &numOne, std::vector<int32_t> &numTwo) {
    if (numOne.size() <= 64 || numTwo.size() <= 64) {
        return NaiveMultiplication(numOne, numTwo);
    }

    int32_t n1 = numOne.size();
    int32_t n2 = numTwo.size();
    if (n1 < n2) {
        AddZeros(numOne, n2 - n1);
    }
    if (n2 < n1) {
        AddZeros(numTwo, n1 - n2);
    }

    int32_t newSize = std::max(n1, n2);
    if (newSize % 2 == 1) {
        AddZeros(numOne, 1);
        AddZeros(numTwo, 1);
        newSize++;
    }

    int32_t halfSize = newSize / 2;

    std::vector<int32_t> a0(numOne.begin(), numOne.begin() + halfSize);
    std::vector<int32_t> a1(numOne.begin() + halfSize, numOne.end());
    std::vector<int32_t> b0(numTwo.begin(), numTwo.begin() + halfSize);
    std::vector<int32_t> b1(numTwo.begin() + halfSize, numTwo.end());

    std::vector<int32_t> a1b1 = FirstAncientSkill(a1, b1);
    std::vector<int32_t> a0b0 = FirstAncientSkill(a0, b0);

    std::vector<int32_t> a1a0Sum = SumNums(a1, a0);
    std::vector<int32_t> b1b0Sum = SumNums(b1, b0);
    std::vector<int32_t> superMulti = FirstAncientSkill(a1a0Sum, b1b0Sum);

    std::vector<int32_t> superSum = SumNums(a1b1, a0b0);
    std::vector<int32_t> preMiddleCoef = SubtractNums(superMulti, a1b1);
    std::vector<int32_t> middleCoef = SubtractNums(preMiddleCoef, a0b0);

    std::reverse(middleCoef.begin(), middleCoef.end());
    AddZeros(middleCoef, halfSize);
    std::reverse(middleCoef.begin(), middleCoef.end());

    std::reverse(a1b1.begin(), a1b1.end());
    AddZeros(a1b1, halfSize * 2);
    std::reverse(a1b1.begin(), a1b1.end());

    std::vector<int32_t> FinalSum1 = SumNums(a1b1, middleCoef);

    return SumNums(FinalSum1, a0b0);
}

void AlgorithmTasks::AddZeros(std::vector<int32_t> &num, size_t amount) {
    for (int32_t i = 0; i < amount; ++i) {
        num.push_back(0);
    }
}

std::vector<int32_t> AlgorithmTasks::SubtractNums(std::vector<int32_t> numOne, std::vector<int32_t> &numTwo) {
    int32_t n1 = numOne.size();
    int32_t n2 = numTwo.size();
    if (n2 < n1) {
        AddZeros(numTwo, n1 - n2);
    }
    std::vector<int32_t> result(n1);

    for (int32_t i = 0; i < n1; ++i) {
        result[i] = numOne[i] - numTwo[i];
        if (result[i] < 0) {
            result[i] += 10;
            numOne[i + 1] -= 1;
        }
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

std::vector<int32_t> AlgorithmTasks::SumNums(std::vector<int32_t> &numOne, std::vector<int32_t> &numTwo) {
    int32_t n1 = numOne.size();
    int32_t n2 = numTwo.size();
    if (n1 < n2) {
        AddZeros(numOne, n2 - n1);
    }
    if (n2 < n1) {
        AddZeros(numTwo, n1 - n2);
    }
    std::vector<int32_t> result(std::max(n1, n2) + 1);

    for (int32_t i = 0; i < std::max(n1, n2); ++i) {
        result[i] += numOne[i] + numTwo[i];
        if (result[i] >= 10) {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

// Strassen 32 algorithm
// | down
// v
std::vector<std::vector<int64_t>> AlgorithmTasks::SecondAncientSkill(std::vector<std::vector<int64_t>> &matrixOne,
                                                                     std::vector<std::vector<int64_t>> &matrixTwo,
                                                                     size_t n) {
    if (n <= 32) {
        return NaiveMatrixMultiplication(matrixOne, matrixTwo, n);
    }

    size_t half = n / 2;

    std::vector<std::vector<std::vector<int64_t>>> ABlock = SplitMatrix(matrixOne, n);
    std::vector<std::vector<int64_t>> a11 = ABlock[0];
    std::vector<std::vector<int64_t>> a12 = ABlock[1];
    std::vector<std::vector<int64_t>> a21 = ABlock[2];
    std::vector<std::vector<int64_t>> a22 = ABlock[3];

    std::vector<std::vector<std::vector<int64_t>>> BBlock = SplitMatrix(matrixTwo, n);
    std::vector<std::vector<int64_t>> b11 = BBlock[0];
    std::vector<std::vector<int64_t>> b12 = BBlock[1];
    std::vector<std::vector<int64_t>> b21 = BBlock[2];
    std::vector<std::vector<int64_t>> b22 = BBlock[3];

    std::vector<std::vector<int64_t>> s1 = SubtractMatrixes(b12, b22, half);
    std::vector<std::vector<int64_t>> s2 = SumMatrixes(a11, a12, half);
    std::vector<std::vector<int64_t>> s3 = SumMatrixes(a21, a22, half);
    std::vector<std::vector<int64_t>> s4 = SubtractMatrixes(b21, b11, half);
    std::vector<std::vector<int64_t>> s5 = SumMatrixes(a11, a22, half);
    std::vector<std::vector<int64_t>> s6 = SumMatrixes(b11, b22, half);
    std::vector<std::vector<int64_t>> s7 = SubtractMatrixes(a12, a22, half);
    std::vector<std::vector<int64_t>> s8 = SumMatrixes(b21, b22, half);
    std::vector<std::vector<int64_t>> s9 = SubtractMatrixes(a11, a21, half);
    std::vector<std::vector<int64_t>> s10 = SumMatrixes(b11, b12, half);

    std::vector<std::vector<int64_t>> p1 = SecondAncientSkill(a11, s1, half);
    std::vector<std::vector<int64_t>> p2 = SecondAncientSkill(s2, b22, half);
    std::vector<std::vector<int64_t>> p3 = SecondAncientSkill(s3, b11, half);
    std::vector<std::vector<int64_t>> p4 = SecondAncientSkill(a22, s4, half);
    std::vector<std::vector<int64_t>> p5 = SecondAncientSkill(s5, s6, half);
    std::vector<std::vector<int64_t>> p6 = SecondAncientSkill(s7, s8, half);
    std::vector<std::vector<int64_t>> p7 = SecondAncientSkill(s9, s10, half);

    std::vector<std::vector<int64_t>> p5p4 = SumMatrixes(p5, p4, half);
    std::vector<std::vector<int64_t>> p5p4p2 = SubtractMatrixes(p5p4, p2, half);
    std::vector<std::vector<int64_t>> c11 = SumMatrixes(p5p4p2, p6, half);

    std::vector<std::vector<int64_t>> c12 = SumMatrixes(p1, p2, half);
    std::vector<std::vector<int64_t>> c21 = SumMatrixes(p3, p4, half);

    std::vector<std::vector<int64_t>> p5p1 = SumMatrixes(p5, p1, half);
    std::vector<std::vector<int64_t>> p5p1p3 = SubtractMatrixes(p5p1, p3, half);
    std::vector<std::vector<int64_t>> c22 = SubtractMatrixes(p5p1p3, p7, half);

    return MergeMatrixes(c11, c12, c21, c22, half);
}

std::vector<std::vector<int64_t>>
AlgorithmTasks::NaiveMatrixMultiplication(const std::vector<std::vector<int64_t>> &matrixOne,
                                          const std::vector<std::vector<int64_t>> &matrixTwo, size_t n) {
    std::vector<std::vector<int64_t>> resultMatrix(n, std::vector<int64_t>(n));

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            int64_t curNum = 0;
            for (int32_t k = 0; k < n; ++k) {
                curNum += (matrixOne[i][k] * matrixTwo[k][j]);
            }
            resultMatrix[i][j] = curNum;
        }
    }

    return resultMatrix;
}

std::vector<std::vector<int64_t>> AlgorithmTasks::SubtractMatrixes(const std::vector<std::vector<int64_t>> &matrixOne,
                                                                   const std::vector<std::vector<int64_t>> &matrixTwo,
                                                                   size_t n) {
    std::vector<std::vector<int64_t>> resultMatrix(n, std::vector<int64_t>(n));

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            resultMatrix[i][j] = matrixOne[i][j] - matrixTwo[i][j];
        }
    }

    return resultMatrix;
}

std::vector<std::vector<int64_t>> AlgorithmTasks::SumMatrixes(const std::vector<std::vector<int64_t>> &matrixOne,
                                                              const std::vector<std::vector<int64_t>> &matrixTwo,
                                                              size_t n) {
    std::vector<std::vector<int64_t>> resultMatrix(n, std::vector<int64_t>(n));

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            resultMatrix[i][j] = matrixOne[i][j] + matrixTwo[i][j];
        }
    }

    return resultMatrix;
}

std::vector<std::vector<int64_t>>
AlgorithmTasks::MergeMatrixes(const std::vector<std::vector<int64_t>> &c11,
                              const std::vector<std::vector<int64_t>> &c12,
                              const std::vector<std::vector<int64_t>> &c21,
                              const std::vector<std::vector<int64_t>> &c22,
                              size_t n) {
    std::vector<std::vector<int64_t>> resultMatrix(n * 2, std::vector<int64_t>(n * 2));

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            resultMatrix[i][j] = c11[i][j];
            resultMatrix[i][j + n] = c12[i][j];
            resultMatrix[i + n][j] = c21[i][j];
            resultMatrix[i + n][j + n] = c22[i][j];
        }
    }

    return resultMatrix;
}

std::vector<std::vector<std::vector<int64_t>>>
AlgorithmTasks::SplitMatrix(const std::vector<std::vector<int64_t>> &matrix, size_t n) {
    std::vector<std::vector<std::vector<int64_t>>> result(4, std::vector<std::vector<int64_t>>(n / 2,
                                                                                               std::vector<int64_t>(
                                                                                                       n / 2)));
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            if (i <= n / 2 - 1 && j <= n / 2 - 1) {
                result[0][i][j] = matrix[i][j];
            } else if (i <= n / 2 - 1 && j >= n / 2) {
                result[1][i][j - n / 2] = matrix[i][j];
            } else if (i >= n / 2 && j <= n / 2 - 1) {
                result[2][i - n / 2][j] = matrix[i][j];
            } else if (i >= n / 2 && j >= n / 2) {
                result[3][i - n / 2][j - n / 2] = matrix[i][j];
            }
        }
    }

    return result;
}

// Minimal distance between set of 2-dimensional points
int64_t
AlgorithmTasks::TwoDimensionalHuecoMundoPassage(std::vector<HuecoMundoPoint> &points, int32_t left, int32_t right) {
    if (left >= right) {
        return INT64_MAX;
    }
    if (right - 1 == left) {
        return points[left].SquareDistance(points[right]);
    }

    int32_t mid = left + (right - left) / 2;
    int64_t leftPartMinDistance = TwoDimensionalHuecoMundoPassage(points, left, mid);
    int64_t rightPartMinDistance = TwoDimensionalHuecoMundoPassage(points, mid + 1, right);

    int64_t minDistanceD = std::min(leftPartMinDistance, rightPartMinDistance);
    int64_t midPointX = points[mid].x;

    std::vector<HuecoMundoPoint> connectivePoints;


    for (int32_t i = mid; i >= left; i--) {
        if (static_cast<int64_t>(std::pow(points[i].x - midPointX, 2.0)) <= minDistanceD) {
            connectivePoints.push_back(points[i]);
        } else {
            break;
        }
    }

    for (int32_t i = mid + 1; i <= right; ++i) {
        if (static_cast<int64_t>(std::pow(points[i].x - midPointX, 2.0)) <= minDistanceD) {
            connectivePoints.push_back(points[i]);
        } else {
            break;
        }
    }

    std::sort(connectivePoints.begin(), connectivePoints.end(), PointYComparator{});

    int64_t minConnectiveDistance = INT64_MAX;
    auto connSize = static_cast<int32_t>(connectivePoints.size());

    for (int32_t i = 0; i < connSize; ++i) {
        for (int32_t j = 1; j <= 7; ++j) {
            if (i + j < connSize) {
                minConnectiveDistance = std::min(minConnectiveDistance,
                                                 connectivePoints[i].SquareDistance(connectivePoints[i + j]));
            } else {
                break;
            }
        }
    }


    return std::min(minDistanceD, minConnectiveDistance);
}

double AlgorithmTasks::TrainToSoulKingsCastle(const std::vector<int32_t> &speedAtTime,
                                              const std::vector<int32_t> &sumTime,
                                              const std::vector<int32_t> &sumDistance, int32_t gap, size_t n) {
    double ans = 0;

    for (int32_t i = 0; i < n + 1; ++i) {
        double possibleTimeFirst =
                calculateNewTime(speedAtTime, sumTime, sumDistance, sumDistance[i] + gap) - sumTime[i];
        ans = std::max(ans, possibleTimeFirst);

        if (sumDistance[i] - gap >= 0) {
            double possibleTimeSecond =
                    sumTime[i] - calculateNewTime(speedAtTime, sumTime, sumDistance, sumDistance[i] - gap);
            ans = std::max(ans, possibleTimeSecond);
        }
    }

    return ans;
}

double AlgorithmTasks::calculateNewTime(const std::vector<int32_t> &speedAtTime, const std::vector<int32_t> &sumTime,
                                        const std::vector<int32_t> &sumDistance, int32_t needDistance) {
    if (needDistance > sumDistance.back()) {
        return sumTime.back();
    }

    int32_t idx = 0;
    for (idx = 0; idx < speedAtTime.size(); ++idx) {
        if (sumDistance[idx] >= needDistance) {
            break;
        }
    }

    return static_cast<double>(sumTime[idx]) - static_cast<double>(sumDistance[idx] - needDistance) / speedAtTime[idx];
}
