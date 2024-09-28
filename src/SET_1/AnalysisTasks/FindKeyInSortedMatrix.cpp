#include <vector>
#include <cstdint>
#include <utility>

std::pair<int32_t , int32_t > FindKeyInSortedMatrix(const std::vector<std::vector<int32_t>>& matrix, int32_t key) {
    int32_t rowIdx = 0;
    int32_t columnIdx = 0;
    size_t n = matrix.size();

    while (rowIdx < n && columnIdx < n) {
        if (matrix[rowIdx][columnIdx] == key) {
            return std::make_pair(rowIdx, columnIdx);
        }
        if (matrix[rowIdx][columnIdx] < key) {
            columnIdx++;
        } else if (matrix[rowIdx][columnIdx] > key) {
            rowIdx++;
        }
    }

    throw std::runtime_error("No such key in matrix");
}