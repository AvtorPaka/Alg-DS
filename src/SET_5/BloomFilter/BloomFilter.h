#ifndef IMPLEMENTATIONDATA_BLOOMFILTER_H
#define IMPLEMENTATIONDATA_BLOOMFILTER_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_set>

class BloomFilter {
private:
    inline size_t _get_hash(int32_t numOfHash, const std::string &key) const;

    size_t _hashes;
    size_t _bits;

    int32_t cnt = 0, false_positive_cnt = 0;

    std::hash<std::string> hasher{};
    std::vector<bool> _filter;
    std::unordered_set<std::string> _raw_set;

public:
    BloomFilter(size_t hashes, size_t bits);

    void add(const std::string& key);

    bool verify(const std::string& key);

    double getFPRate() const;

    size_t numberOfHashFunctions() const ;

    size_t numberOfBits() const;
};

#endif //IMPLEMENTATIONDATA_BLOOMFILTER_H
