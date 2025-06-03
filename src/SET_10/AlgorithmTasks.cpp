#include "AlgorithmTasks.h"

double AlgorithmTasks::CalculateMaxParticleKnapsackPrice(std::vector<KnapsackParticleItem>& items, uint32_t maxVolume) {
    uint32_t leftVolume = maxVolume;
    double maxCost = 0;

    std::sort(items.begin(), items.end(), KnapsackParticleItemComparator());

    KnapsackParticleItem curItem{};
    for (size_t i = 0; i < items.size(); ++i) {

        curItem = items[i];
        if (curItem.volume <= leftVolume) {
            maxCost += curItem.cost;
            leftVolume -= curItem.volume;
        } else {
            maxCost += leftVolume * curItem.unitCost;
            break;
        }
    }

    return maxCost;
}

// only god and i know what this code does
std::vector<uint32_t> AlgorithmTasks::GenerateMax2DiffedSliceNumsTransposition(uint32_t n, uint32_t l, uint32_t r) {
    std::vector<uint32_t> maxSliceTransposition(n);

    uint32_t midSliceIdx = (l + (r - l)/2);
    uint32_t maxNum = n;
    uint32_t predMaxNum = maxNum - 1;

    if (n == 1) {
        maxSliceTransposition[midSliceIdx] = maxNum;
        return maxSliceTransposition;
    }

    std::vector<bool> numTaken(n + 1, false);
    maxSliceTransposition[midSliceIdx] = maxNum;
    numTaken[maxNum] = true;

    uint32_t leftPartSize = midSliceIdx;
    int32_t rightPartSize;

    if (midSliceIdx + 1 < n) {
        maxSliceTransposition[midSliceIdx + 1] = predMaxNum;
        numTaken[predMaxNum] = true;
        rightPartSize = n - midSliceIdx - 2;
    } else {
        rightPartSize = 0;
    }


    if (leftPartSize < rightPartSize) {

        int32_t leftSlideIdx = midSliceIdx - 1;
        uint32_t leftFillNum = maxNum - 2;
        while (leftSlideIdx >= 0) {
            maxSliceTransposition[leftSlideIdx] = leftFillNum;
            numTaken[leftFillNum] = true;
            leftSlideIdx--;
            leftFillNum -= 2;
        }

        uint32_t rightSlideIdx = midSliceIdx + 1;
        uint32_t  rightSlideNum = predMaxNum;
        uint32_t curDiff;
        while (rightSlideIdx + 1 < n) {
            curDiff = !numTaken[rightSlideNum - 1] ? 1 :  2;
            rightSlideNum -= curDiff;
            maxSliceTransposition[++rightSlideIdx] = rightSlideNum;
            numTaken[rightSlideNum] = true;
        }

    } else {

        uint32_t rightSideIdx = midSliceIdx + 2;
        uint32_t rightFillNum = predMaxNum - 2;
        while (rightSideIdx < n) {
            maxSliceTransposition[rightSideIdx] = rightFillNum;
            numTaken[rightFillNum] = true;
            rightSideIdx++;
            rightFillNum -= 2;
        }

        int32_t leftSlideIdx = midSliceIdx;
        uint32_t  leftSlideNum = maxNum;
        uint32_t curDiff;
        while (leftSlideIdx - 1 >= 0) {
            curDiff = !numTaken[leftSlideNum - 1] ? 1 :  2;
            leftSlideNum -= curDiff;
            maxSliceTransposition[--leftSlideIdx] = leftSlideNum;
            numTaken[leftSlideNum] = true;
        }
    }


    return maxSliceTransposition;
}

std::vector<int32_t> AlgorithmTasks::GetSegmentsMinimalCoveringPoints(std::vector<SegmentPoints>& segments) {
    std::vector<int32_t> points;

    std::sort(segments.begin(), segments.end(), SegmentPointsComparator());

    points.push_back(segments[0].right);

    for (size_t i = 0; i < segments.size(); ++i) {
        if (segments[i].left > points.back()) {
            points.push_back(segments[i].right);
        }
    }

    return points;
}

double AlgorithmTasks::FoundMaxWeightCompatibleSegments(std::vector<WeightSegment>& segments) {
    size_t n = segments.size();
    std::sort(segments.begin(), segments.end(), WeightSegmentComparator());

    std::vector<size_t> maxCompatibleSegmentIdx(n + 1);

    size_t maxCompIdx = 0;
    for (int32_t i = 0; i < n; ++i) {

        for (int32_t j = i - 1; j >= 0; --j) {
            if (segments[i].left >= segments[j].right) {
                maxCompIdx =  j + 1;
                break;
            }
        }

        maxCompatibleSegmentIdx[i + 1] = maxCompIdx;
        maxCompIdx = 0;
    }

    std::vector<double> maxSubSegmentsWeight(n + 1, 0);

    for (int32_t i = 1; i < n + 1; ++i) {
        maxSubSegmentsWeight[i] = std::max(maxSubSegmentsWeight[i - 1], segments[i - 1].weight + maxSubSegmentsWeight[maxCompatibleSegmentIdx[i]]);
    }

    return maxSubSegmentsWeight.back();
}

uint32_t AlgorithmTasks::FindMaxKnapsackCostWithWeight(const std::vector<CostWeightKnapsackItem>& items, uint32_t maxWeight) {
    size_t n = items.size();
    std::vector<uint32_t> prevMaxCost(maxWeight + 1, 0);
    std::vector<uint32_t> curMaxCost(maxWeight + 1, 0);

    for (size_t i = 0; i < n; ++i) {

        for (size_t w = 0; w < maxWeight + 1; ++w) {
            if (items[i].weight > w) {
                curMaxCost[w] = prevMaxCost[w];
            } else {
                curMaxCost[w] = std::max(prevMaxCost[w], items[i].cost + prevMaxCost[w - items[i].weight]);
            }
        }

        prevMaxCost = curMaxCost;
        curMaxCost = std::vector<uint32_t>(maxWeight + 1, 0);
    }

    return prevMaxCost.back();
}

uint32_t AlgorithmTasks::FindMinSegmentCutTime(std::vector<uint32_t>& points) {
    size_t n = points.size();
    std::vector<std::vector<uint32_t>> minSegmentCutCost(n, std::vector<uint32_t>(n, 0));

    for (uint32_t innerPoints = 2; innerPoints < n; ++innerPoints) {
        for (uint32_t i = 0; i < n - innerPoints; ++i) {
            uint32_t j = i + innerPoints;
            minSegmentCutCost[i][j] = UINT32_MAX;
            uint32_t curSegmentLength = points[j] - points[i];

            for (uint32_t k = i + 1; k < j; ++k) {
                minSegmentCutCost[i][j] = std::min(minSegmentCutCost[i][j], curSegmentLength + minSegmentCutCost[i][k] + minSegmentCutCost[k][j]);
            }
        }
    }

    return minSegmentCutCost[0][n - 1];
}

uint32_t AlgorithmTasks::FindMaxKnapsackCostWithWeightVolume(const std::vector<CostWeightVolumeKnapsackItem>& items, uint32_t maxWeight, uint32_t maxVolume) {
    size_t n = items.size();
    std::vector<std::vector<uint32_t>> prevMaxCost(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));
    std::vector<std::vector<uint32_t>> curMaxCost(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));

    for (size_t i = 0; i < n; ++i) {
        const CostWeightVolumeKnapsackItem& curItem = items[i];

        for (size_t w = 0; w < maxWeight + 1; ++w) {
            for (size_t v = 0; v < maxVolume + 1; ++v) {
                if (curItem.weight > w || curItem.volume > v) {
                    curMaxCost[w][v] = prevMaxCost[w][v];
                } else {
                    curMaxCost[w][v] = std::max(prevMaxCost[w][v], items[i].cost + prevMaxCost[w - curItem.weight][v - curItem.volume]);
                }
            }
        }

        prevMaxCost = curMaxCost;
        curMaxCost = std::vector<std::vector<uint32_t>>(maxWeight + 1, std::vector<uint32_t>(maxVolume + 1, 0));
    }

    return prevMaxCost[maxWeight][maxVolume];
}

std::vector<std::vector<uint64_t>> AlgorithmTasks::MultMatrix(const std::vector<std::vector<uint64_t>>& A, const std::vector<std::vector<uint64_t>>& B, uint32_t size, uint64_t& mod) {
    std::vector<std::vector<uint64_t>> C(size, std::vector<uint64_t>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int l = 0; l < size; ++l) {
                C[i][j] = (C[i][j] + A[i][l] * B[l][j]) % mod;
            }
        }
    }
    return C;
}

std::vector<std::vector<uint64_t>> AlgorithmTasks::PowMatrix(std::vector<std::vector<uint64_t>> A, uint64_t p, uint32_t size, uint64_t& mod) {
    std::vector<std::vector<uint64_t>> res(size, std::vector<uint64_t>(size, 0));
    for (int i = 0; i < size; ++i) {
        res[i][i] = 1;
    }

    A[0][0] %= mod;

    while (p > 0) {
        if (p % 2 == 1) {
            res = MultMatrix(res, A, size, mod);
        }
        A = MultMatrix(A, A, size, mod);
        p /= 2;
    }
    return res;
}

std::vector<uint64_t> AlgorithmTasks::VecMultMatrix(const std::vector<std::vector<uint64_t>>& M, const std::vector<uint64_t>& vec, uint32_t size, uint64_t& mod) {
    std::vector<uint64_t> res_vec(size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res_vec[i] = (res_vec[i] + M[i][j] * vec[j]) % mod;
        }
    }
    return res_vec;
}

uint64_t AlgorithmTasks::CountNumberOfAuthenticNumSet(uint64_t n, uint32_t k, uint64_t& mod) {
    if ( n == 0 || k == 0 ) {
        return 0;
    }
    if (k == 1) {
        if ( n == 1 ) {
            return 1;
        }
        return 0;
    }

    if (n == 1) {
        return k % mod;
    }

    uint32_t stateSize = 2 * k;

    std::vector<uint64_t> baseS(stateSize);
    for (uint32_t j = 0; j < k; ++j) {
        baseS[2 * j] = j;
        baseS[2 * j + 1] = (uint64_t)k - 1 - j;
    }

    if (n == 2) {
        uint64_t sum = 0;
        for (uint64_t val : baseS) {
            sum = (sum + val) % mod;
        }
        return sum;
    }

    std::vector<std::vector<uint64_t>> T(stateSize, std::vector<uint64_t>(stateSize, 0));
    for (uint32_t j_new = 0; j_new < k; ++j_new) {
        for (uint32_t s_old = 0; s_old < j_new; ++s_old) {
            T[2 * j_new][2 * s_old + 1] = 1;
        }

        for (uint32_t s_old = j_new + 1; s_old < k; ++s_old) {
            T[2 * j_new + 1][2 * s_old] = 1;
        }
    }

    uint64_t power = n - 2;
    std::vector<std::vector<uint64_t>> T_pow_final = PowMatrix(T, power, stateSize, mod);
    std::vector<uint64_t> S_n = VecMultMatrix(T_pow_final, baseS, stateSize, mod);

    uint64_t ans = 0;
    for (int32_t i = 0; i < S_n.size(); ++i) {
        ans = (ans + S_n[i]) % mod;
    }

    return ans;
}

std::vector<std::vector<int32_t>> AlgorithmTasks::FindGoodGrid(uint32_t n, uint32_t m, int32_t c, uint32_t iterations) {
    std::vector<std::vector<int32_t>> grid(n, std::vector<int32_t>(m, 0));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> color_dis(1, c);
    std::uniform_int_distribution<uint32_t> row_dis(0, n - 1);
    std::uniform_int_distribution<uint32_t> col_dis(0, m - 1);

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < m; ++j) {
            grid[i][j] = color_dis(gen);
        }
    }
    uint32_t curSameColorRect = CountSameColorRectangles(grid, n, m);

    for (int32_t iter = 0; iter < iterations && curSameColorRect > 0; ++iter) {
        int32_t bestI = -1;
        int32_t bestJ = -1;
        int32_t bestNC = -1;
        int32_t bestDiffDelt = 0;
        bool hasImprovement = false;

        for (int32_t i_check = 0; i_check < n && !hasImprovement; ++i_check) {
            for (int32_t j_check = 0; j_check < m && !hasImprovement; ++j_check) {
                int32_t initColor = grid[i_check][j_check];

                for (int32_t newColor = 1; newColor <= c; ++newColor) {
                    if (newColor == initColor) {
                        continue;
                    }
                    int32_t delta = FindSameColorRectDeltaDiff(grid, n, m, i_check, j_check, initColor, newColor);

                    if (delta < bestDiffDelt) {
                        bestI = i_check;
                        bestJ = j_check;
                        bestNC = newColor;
                        bestDiffDelt = delta;
                    }

                    if (delta < 0) {
                        hasImprovement = true;
                        break;
                    }
                }
            }
        }

        if (bestI == -1) {
            uint32_t randomI = row_dis(gen);
            uint32_t randomJ = col_dis(gen);
            int32_t randOldColor = grid[randomI][randomJ];
            int32_t randNewColor = color_dis(gen);

            while (randNewColor == randOldColor) {
                randNewColor = color_dis(gen);
            }

            int32_t delta_for_random_move = FindSameColorRectDeltaDiff(grid, n, m, randomI, randomJ, randOldColor, randNewColor);
            grid[randomI][randomJ] = randNewColor;
            curSameColorRect += delta_for_random_move;

            if (iter > 0 && iter % 50 == 0) {
                curSameColorRect = CountSameColorRectangles(grid, n, m);
            }
        } else {
            grid[bestI][bestJ] = bestNC;
            curSameColorRect += bestDiffDelt;
        }

        if (curSameColorRect < 0) {
            curSameColorRect = CountSameColorRectangles(grid, n, m);
        }
    }

    if (curSameColorRect != 0) {
        for (int32_t k = 0; k < 10; ++k) {
            for (int32_t i = 0; i < n; ++i) {
                for (int32_t j = 0; j < m; ++j) {
                    grid[i][j] = color_dis(gen);
                }
            }
            curSameColorRect = CountSameColorRectangles(grid, n, m);
            if (curSameColorRect == 0) {
                break;
            }
        }
    }

    return grid;
}

uint32_t AlgorithmTasks::CountSameColorRectangles(const std::vector<std::vector<int32_t>> &grid, uint32_t n, uint32_t m) {
    uint32_t cnt = 0;

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t i_s = i + 1; i_s < n; ++i_s) {
            for (int32_t j = 0; j < m; ++j) {
                for (int32_t j_s = j + 1; j_s < m; ++j_s) {
                    if (grid[i][j] == grid[i_s][j] && grid[i][j] == grid[i][j_s] && grid[i][j] == grid[i_s][j_s]) {
                        cnt++;
                    }
                }
            }
        }
    }

    return cnt;
}

int32_t AlgorithmTasks::FindSameColorRectDeltaDiff(const std::vector<std::vector<int32_t>> &grid, uint32_t n, uint32_t m, uint32_t iChanged,
                           uint32_t jChanged, int32_t oldV, int32_t newV) {
    if (oldV == newV) {
        return 0;
    }

    int32_t delt = 0;
    for (int32_t i = 0; i < n; ++i) {
        if (i == iChanged) {
            continue;
        }
        for (int32_t j = 0; j < m; ++j) {
            if (j == jChanged) {
                continue;
            }

            int32_t color_adjacent_row = grid[iChanged][j];
            int32_t color_adjacent_col = grid[i][jChanged];
            int32_t color_diagonal_opposite = grid[i][j];

            if (color_adjacent_row == oldV && color_adjacent_col == oldV && color_diagonal_opposite == oldV) {
                delt--;
            }
            if (color_adjacent_row == newV && color_adjacent_col == newV && color_diagonal_opposite == newV) {
                delt++;
            }
        }
    }

    return delt;
}
