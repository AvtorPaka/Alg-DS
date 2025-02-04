#include "BloomFilter.h"

BloomFilter::BloomFilter(size_t hashes, size_t bits) {
    this->_hashes = hashes;
    this->_bits = bits;
    _filter = std::vector<bool>(_bits, false);
    _raw_set = std::unordered_set<std::string>();
}


void BloomFilter::add(const std::string &key) {
    _raw_set.insert(key);

    for (int i = 0; i < this->_hashes; ++i) {
        _filter[_get_hash(i, key)] = true;
    }
}


bool BloomFilter::verify(const std::string &key) {
    this->cnt++;
    bool bloomAns = true;

    for (int i = 0; i < this->_hashes; ++i) {
        if (!_filter[_get_hash(i, key)]) {
            bloomAns = false;
            break;
        }
    }

    if (bloomAns && !_raw_set.contains(key)) {
        this->false_positive_cnt++;
    }

    return bloomAns;
}


double BloomFilter::getFPRate() const {
    return cnt == 0 ? 0 : (double) false_positive_cnt / cnt;
}


size_t BloomFilter::numberOfHashFunctions() const {
    return _hashes;
}


size_t BloomFilter::numberOfBits() const {
    return _bits;
}


inline size_t BloomFilter::_get_hash(int numOfHash, const std::string &key) const {
    return hasher(key + (numOfHash == 0 ? "" : std::to_string(numOfHash))) % _bits;
}
