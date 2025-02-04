#ifndef IMPLEMENTATIONDATA_FINDMAXANAGRAM_H
#define IMPLEMENTATIONDATA_FINDMAXANAGRAM_H

#include <vector>
#include <cstdint>
#include <tuple>
#include <unordered_map>

class FindMaxAnagram {
private:
    static std::unordered_map<int32_t, uint64_t> GenerateHashes(const std::vector<int32_t> &nums, const std::vector<int32_t> &numsTwo);
public:
    static std::tuple<int32_t, int32_t, int32_t> FindAnagram(const std::vector<int32_t> &a, const std::vector<int32_t> &b, int32_t minArrSize);
};


#endif //IMPLEMENTATIONDATA_FINDMAXANAGRAM_H
