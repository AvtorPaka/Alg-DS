#ifndef ALGORITHMTASKS_1_H
#define ALGORITHMTASKS_1_H

#include <cstdint>
#include <vector>

class AlgorithmTasks {
private:
    static int32_t FindMinRepetativeSegmentCount(const std::vector<int32_t> &array, int32_t n);
public:
    static int32_t WaterWheel(const std::vector<int32_t> &array, int32_t n);
    static void WagonsSorting(const std::vector<int32_t> &wagons, int32_t n);
    static std::string InosukeUnboxing(const std::string &boxed_string);
    static void EndlessCastle();
};


#endif //ALGORITHMTASKS_1_H