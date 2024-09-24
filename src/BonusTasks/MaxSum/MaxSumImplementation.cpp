#include <vector>
#include <cstdint>
#include <climits>

class MaxSumImplementation {
public:
    static int32_t long_find_max_sum(const std::vector<int32_t> &array, int32_t k) {
        size_t n = array.size();
        int32_t max_sum = INT_MIN;

        for (int32_t i = 0; i <= n - k; ++i) {
            int32_t current_sum = 0;
            for (int32_t j = i; j < i + k; ++j) {
                current_sum += array[j];
            }

            max_sum = std::max(max_sum, current_sum);
        }

        return max_sum;
    }

    static int32_t fast_find_max_sum(const std::vector<int32_t> &array, int32_t k) {
        size_t n = array.size();
        int32_t tmp_sum = 0;
        int32_t max_sum = 0;

        for (int32_t i = 0; i < n; ++i) {
            if (i < k) {
                max_sum += array[i];
                tmp_sum += array[i];
            } else {
                tmp_sum = tmp_sum + array[i] - array[i - k];
                max_sum = std::max(max_sum, tmp_sum);
            }
        }

        return max_sum;
    }
};