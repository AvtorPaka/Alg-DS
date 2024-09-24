## Seminar №3 bonus task

## Демченко Георгий Павлович , БПИ-235

### 1. Analysis | [long_find_max_sum](https://github.com/AvtorPaka/Alg-DS/tree/master/src/BonusTasks/MaxSum/MaxSumImplementation.cpp)

```cpp
int32_t long_find_max_sum(const std::vector<int32_t> &array, int32_t k) {
    size_t n = array.size();                            // c_1
    int32_t max_sum = INT_MIN;                          // c_2

    for (int32_t i = 0; i <= n - k; ++i) {              // (n - k + 1)(k * c_4 + c_3 + c_5)
        int32_t current_sum = 0;                        // c_3
        for (int32_t j = i; j < i + k; ++j) {           // k * c_4
            current_sum += array[j];                    // c_4
        }

        max_sum = std::max(max_sum, current_sum);       // c_5
    }

    return max_sum;
}
```

```math
\bullet \space k \in [0, n]
```

```math
T(n, k) = (n - k + 1) \cdot (k * c_4 + c_3 + c_5) + (c_1 + c_2) \newline = O(nk + k - k^2) = O(k(n + 1 - k))
\newline
```

* **Для явного противопоставления сложности оптимизированной версии**

```math
\bullet \space k = \left[ \frac{n} {2} \right] = \frac{n}{2} \space (\text{для упрощения вычислений}) \newline
```

```math
T(n, \frac{n}{2}) = O\left( \frac{n}{2} \cdot \left(n + 1 - \frac{n}{2} \right)\right) = O\left(\frac{n^2}{4} + \frac{n}{2}\right) = O(n^2)
```

```math
\Rightarrow T(n, k) = O(n^2)
```


### 2. Analysis | [fast_find_max_sum](https://github.com/AvtorPaka/Alg-DS/tree/master/src/BonusTasks/MaxSum/MaxSumImplementation.cpp)

```cpp
int32_t fast_find_max_sum(const std::vector<int32_t> &array, int32_t k) {
    size_t n = array.size();                                // c_1
    int32_t tmp_sum = 0;                                    // c_2
    int32_t max_sum = 0;                                    // c_3

    for (int32_t i = 0; i < n; ++i) {                       // n        
        if (i < k) {                                        
            max_sum += array[i];                            // c_4
            tmp_sum += array[i];                            // c_5
        } else {                                            
            tmp_sum = tmp_sum + array[i] - array[i - k];    // c_6
            max_sum = std::max(max_sum, tmp_sum);           // c_7
        }
    }

    return max_sum;
    }
```

```math
\bullet \space k \in [0, n]
```

```math
T(n, k) =  k \cdot (c_4 + c_5) + (n - k)(c_6 + c_7) + (c_1 + c_2 + c_3) \newline = n \cdot (c_6 + c_7) + k \cdot (c_4 + c_5 - c_6 - c_7) + (c_1 + c_2 + c_3) \newline = \Theta(n + k) = \Theta(n) = O(n)
```