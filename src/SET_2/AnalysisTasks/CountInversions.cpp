#include <vector>
#include <cstdint>

int32_t MergeAndCountInversions(std::vector<int32_t>& array, int32_t left, int32_t middle, int32_t right) {
    int32_t left_size = middle - left + 1;
    int32_t right_size = right - middle;

    std::vector<int32_t> left_part;
    left_part.reserve(left_size);
    std::vector<int32_t> right_part;
    right_part.reserve(right_size);

    for (int32_t i = 0; i < left_size; ++i) {
        left_part.emplace_back(array[left + i]);
    }
    for (int32_t i = 0; i < right_size; ++i) {
        right_part.emplace_back(array[middle + 1 + i]);
    }

    int32_t inversionsCount = 0;
    int32_t arrowFromRightCount = 0;

    int32_t left_idx = 0;
    int32_t right_idx = 0;
    int32_t main_idx = left;

    while (left_idx < left_size && right_idx < right_size) {
        if (left_part[left_idx] <= right_part[right_idx]) {
            array[main_idx] = left_part[left_idx];
            left_idx++;
            inversionsCount += arrowFromRightCount;
        } else {
            arrowFromRightCount++;
            array[main_idx] = right_part[right_idx];
            right_idx++;
        }
        main_idx++;
    }

    while (left_idx < left_size) {
        inversionsCount += arrowFromRightCount;
        array[main_idx] = left_part[left_idx];
        left_idx++;
        main_idx++;
    }

    while (right_idx < right_size) {
        array[main_idx] = right_part[right_idx];
        right_idx++;
        main_idx++;
    }

    return inversionsCount;
}

int32_t CountInversions(std::vector<int32_t>& array, int32_t left, int32_t right) {
    if (left == right) {
        return 0;
    }
    int32_t middle = left + (right - left)/ 2;

    int32_t leftNumOfInversions = CountInversions(array, left, middle);
    int32_t rightNumOfInversions = CountInversions(array, middle + 1, right);

    int32_t numOfConnectiveInversions = MergeAndCountInversions(array, left, middle,  right);

    return leftNumOfInversions + rightNumOfInversions + numOfConnectiveInversions;
}
