#ifndef IMPLEMENTATIONDATA_STRINGARRAYGENERATOR_H
#define IMPLEMENTATIONDATA_STRINGARRAYGENERATOR_H

#include <string>
#include <vector>

class StringArrayGenerator {
public:

    std::vector<std::string> GenerateArray(size_t size);

    std::vector<std::string> GenerateReverseSortedArray(size_t size);

    std::vector<std::string> GenerateParticleSortedArray(size_t size, uint32_t particleSortFactor = 10);

    std::string GenerateRandomString(size_t minLength, size_t maxLength);

    std::string GenerateRandonStringWithPrefix(size_t minLength, size_t maxLength, const std::string& prefix);

private:
    const std::string allowedCharacters = "!@#%:;^&*()-.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    const size_t minStringLength = 10;
    const size_t maxStringLength = 200;
};


#endif //IMPLEMENTATIONDATA_STRINGARRAYGENERATOR_H
