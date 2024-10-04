#ifndef ALGORITHMTASKS_2_H
#define ALGORITHMTASKS_2_H

#include <vector>

struct Interval {
public:
    int32_t left;
    int32_t right;

    Interval(int32_t l, int32_t r) {
        left = l;
        right = r;
    }

    size_t length() const {
        return std::abs(right - left + 1);
    }

    Interval overlap(const Interval &other) const {
        int32_t possibleLeft = std::max(left, other.left);
        int32_t possibleRight = std::min(right, other.right);

        if (possibleLeft > possibleRight) {
            return {1, 0}; // Суть в right = left - 1, чтобы получалось lenght = 0
        } else {
            return {possibleLeft, possibleRight};
        }
    }
};


class AlgorithmTasks {
private:
    // Strassen 32 algorithm
    static std::vector<std::vector<std::vector<int64_t>>>
    SplitMatrix(const std::vector<std::vector<int64_t>> &matrix, size_t n);

    static std::vector<std::vector<int64_t>>
    MergeMatrixes(const std::vector<std::vector<int64_t>> &c11, const std::vector<std::vector<int64_t>> &c12,
                  const std::vector<std::vector<int64_t>> &c21, const std::vector<std::vector<int64_t>> &c22,
                  size_t n);

    static std::vector<std::vector<int64_t>> SubtractMatrixes(const std::vector<std::vector<int64_t>> &matrixOne,
                                                              const std::vector<std::vector<int64_t>> &matrixTwo,
                                                              size_t n);

    static std::vector<std::vector<int64_t>> SumMatrixes(const std::vector<std::vector<int64_t>> &matrixOne,
                                                         const std::vector<std::vector<int64_t>> &matrixTwo, size_t n);

    static std::vector<std::vector<int64_t>>
    NaiveMatrixMultiplication(const std::vector<std::vector<int64_t>> &matrixOne,
                              const std::vector<std::vector<int64_t>> &matrixTwo, size_t n);

    // Karatsuba 64 multiplication
    static std::vector<int32_t>
    NaiveMultiplication(const std::vector<int32_t> &numOne, const std::vector<int32_t> &numTwo);

    static void AddZeros(std::vector<int32_t> &num, size_t amount);

    static std::vector<int32_t> SubtractNums(std::vector<int32_t> numOne, std::vector<int32_t> &numTwo);

    static std::vector<int32_t> SumNums(std::vector<int32_t> &numOne, std::vector<int32_t> &numTwo);

    static void IntervalMerge(std::vector<Interval> &shards, size_t left, size_t mid, size_t right);

public:
    static void IntervalMergeSort(std::vector<Interval> &shards, size_t left, size_t right);

    static void ByakuyaBankai(std::vector<Interval> &shards, size_t n);

    // Karatsuba 64 multiplication
    static std::vector<int32_t> FirstAncientSkill(std::vector<int32_t> &numOne, std::vector<int32_t> &numTwo);

    // Strassen 32 algorithm
    static std::vector<std::vector<int64_t>>
    SecondAncientSkill(std::vector<std::vector<int64_t>> &matrixOne, std::vector<std::vector<int64_t>> &matrixTwo,
                       size_t n);
};


#endif //ALGORITHMTASKS_2_H
