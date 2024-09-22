#include "AlgorithmTasks.h"
#include <stack>
#include "iostream"
#include "../MiddleQueue/MiddleQueue.h"


int32_t AlgorithmTasks::WaterWheel(const std::vector<int32_t> &array, int32_t n) {
    int32_t max_hem_dist = 0;
    int32_t ans = 0;

    int32_t rep_seg_count = FindMinRepetativeSegmentCount(array, n);

    for (int32_t i = 0; i < n; ++i) {
        int32_t cur_hem_dist = 0;

        for (int32_t j = 0; j < n; ++j) {
            int32_t diff_idx = (j + i) % n;
            if (array[diff_idx] != array[j]) {
                cur_hem_dist++;
            }
        }

        if (cur_hem_dist > max_hem_dist) {
            ans = 1;
            max_hem_dist = cur_hem_dist;
        } else if (cur_hem_dist == max_hem_dist) {
            ans++;
        }
    }

    return ans / rep_seg_count;
}

int32_t AlgorithmTasks::FindMinRepetativeSegmentCount(const std::vector<int32_t> &array, int32_t n) {
    int32_t min_len_ans = n;

    for (int32_t min_len = 1; min_len <= n / 2; min_len++) {
        if (n % min_len != 0) {
            continue;
        }

        bool success_2 = true;
        for (int32_t i = 0; i < min_len; i++) {
            bool success = true;

            for (int32_t j = i; j < n; j += min_len) {
                if (array[i] != array[j]) {
                    success = false;
                    break;
                } else {
                    continue;
                }
            }

            if (!success) {
                success_2 = false;
                break;
            }
        }

        if (success_2) {
            min_len_ans = min_len;
            break;
        }
    }

    int32_t ans = (min_len_ans == n ? 1 : (n / min_len_ans));
    return ans;
}

void AlgorithmTasks::WagonsSorting(const std::vector<int32_t> &wagons, int32_t n) {
    std::string store_log;
    bool real = true;
    int32_t claimed_idx = 0;

    std::vector<bool> claimed(n + 2);
    int32_t last_stored = 0;
    std::stack<int32_t> deadendstack;

    while (last_stored != n) {
        if (claimed[last_stored + 1]) {
            real = false;
            break;
        }

        int32_t taken_count = 0;
        while (wagons[claimed_idx] != last_stored + 1) {
            deadendstack.push(wagons[claimed_idx]);
            claimed[wagons[claimed_idx]] = true;
            claimed_idx++;
            taken_count++;
        }
        deadendstack.push(wagons[claimed_idx]);
        claimed[wagons[claimed_idx]] = true;
        claimed_idx++;
        taken_count++;

        store_log += (store_log.empty() ? "1 " : "\n1 ") + std::to_string(taken_count);


        int32_t store_cnt = 0;
        while (deadendstack.top() == last_stored + 1) {
            last_stored = deadendstack.top();
            deadendstack.pop();
            store_cnt++;
            if (deadendstack.empty()) {
                break;
            }
        }
        store_log += "\n2 " + std::to_string(store_cnt);
    }

    if (real) {
        std::cout << store_log;
    } else {
        std::cout << 0;
    }
}

std::string AlgorithmTasks::InosukeUnboxing(const std::string &boxed_string) {
    std::stack<std::pair<std::string, int32_t>> box_order;
    std::string tmp_string;
    int32_t num_of_cur_boxes = 0;

    for (int32_t i = 0; i < boxed_string.size(); ++i) {
        char curChar = boxed_string[i];
        if (curChar == '[') {
            box_order.emplace(tmp_string, num_of_cur_boxes);
            num_of_cur_boxes = 0;
            tmp_string.clear();
        } else if (curChar == ']') {
            std::pair<std::string, int32_t> boxed_data = box_order.top();
            box_order.pop();
            std::string main_string = std::get<0>(boxed_data);
            for (int32_t j = 0; j < std::get<1>(boxed_data); ++j) {
                main_string += tmp_string;
            }
            tmp_string = main_string;
        } else if (isdigit(curChar)) {
            num_of_cur_boxes = curChar - '0';
        } else {
            tmp_string += curChar;
        }
    }

    return tmp_string;
}

void AlgorithmTasks::EndlessCastle() {
    std::string n_s;
    std::getline(std::cin, n_s);
    int32_t n = std::stoi(n_s);

    MiddleQueue list = MiddleQueue();
    std::string comand;
    for (int32_t i = 0; i < n; ++i) {
        std::getline(std::cin, comand);
        char comandType = comand[0];

        if (comandType == '+') {
            int32_t num = std::stoi(comand.substr(2, std::string::npos));

            list.push_back(num);
        } else if (comandType == '*') {
            int32_t num = std::stoi(comand.substr(2, std::string::npos));

            if (list.empty()) {
                list.push_back(num);
            } else {
                list.insert_in_middle(num);
            }
        } else {
            std::cout << list.front() << std::endl;
            list.pop_front();
        }
    }
}
