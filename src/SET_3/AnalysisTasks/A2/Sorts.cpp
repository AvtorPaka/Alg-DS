#include "Sorts.h"

void Sorts::HybridMergeSort(std::vector<int32_t>& array, int32_t left, int32_t right, int32_t threshold) {
    if ((right - left) + 1 <= threshold) {
        InsertionSort(array, left, right);
    } else {
        int32_t middle = left + (right - left)/2;
        HybridMergeSort(array, left, middle, threshold);
        HybridMergeSort(array, middle + 1, right, threshold);

        Merge(array, left, middle, right);
    }
}

void Sorts::Merge(std::vector<int32_t>& array, int32_t left, int32_t mid, int32_t right) {
    size_t left_arr_size = mid - left + 1;
    size_t right_arr_size = right - mid;

    std::vector<int32_t> left_arr;
    left_arr.reserve(left_arr_size);
    std::vector<int32_t> right_arr;
    right_arr.reserve(right_arr_size);

    for (int32_t i = 0; i < left_arr_size; ++i) {
        left_arr.push_back(array[left + i]);
    }
    for (int32_t j = 0; j < right_arr_size; ++j) {
        right_arr.push_back(array[mid + 1 + j]);
    }

    size_t i = 0;
    size_t j = 0;
    size_t main_pointer = left;
    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i] <= right_arr[j]) {
            array[main_pointer] = left_arr[i];
            i++;
        } else {
            array[main_pointer] = right_arr[j];
            j++;
        }
        main_pointer++;
    }

    while (i < left_arr_size) {
        array[main_pointer] = left_arr[i];
        ++i;
        main_pointer++;
    }

    while (j < right_arr_size) {
        array[main_pointer] = right_arr[j];
        ++j;
        main_pointer++;
    }
}

void Sorts::BaseMergeSort(std::vector<int32_t >& array, int32_t left, int32_t right) {
    if (left < right) {
        int32_t middle = left + (right - left)/2;
        BaseMergeSort(array, left, middle);
        BaseMergeSort(array, middle + 1, right);

        Merge(array, left, middle, right);
    }
}

void Sorts::InsertionSort(std::vector<int32_t>& array, int32_t left, int32_t right) {
    for (int32_t i = left; i <= right; ++i) {
        int32_t key = array[i];
        int32_t j = i - 1;

        while (j >= left && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}