#include "StringArrayGenerator.h"

#include <random>

std::string StringArrayGenerator::GenerateRandomString(size_t minLength, size_t maxLength) {
    if (minLength > maxLength) {
        throw std::runtime_error("Generated string min length must be less than max length.");
    }

    std::string resultString;

    size_t n = allowedCharacters.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> length_dis(minLength, maxLength);
    std::uniform_int_distribution<size_t> char_dis(0, n - 1);

    size_t resultStringLength = length_dis(gen);
    for (int32_t i = 0; i < resultStringLength; ++i) {
        resultString += allowedCharacters[char_dis(gen)];
    }

    return resultString;
}

std::string StringArrayGenerator::GenerateRandonStringWithPrefix(size_t minLength, size_t maxLength, const std::string& prefix) {
    size_t randomPartMaxLen = (maxLength - prefix.length()) % StringArrayGenerator::maxStringLength;
    if (randomPartMaxLen < minLength) {
        minLength = 0;
    }

    std::string randomPostfix = GenerateRandomString(minLength, randomPartMaxLen);
    return prefix + randomPostfix;
}

std::vector<std::string> StringArrayGenerator::GenerateArray(size_t size) {
    std::vector<std::string> randomStringArray(size);

    for (int32_t i = 0; i < size; ++i) {
        randomStringArray[i] =  GenerateRandomString(minStringLength, maxStringLength);
    }

    return randomStringArray;
}

std::vector<std::string> StringArrayGenerator::GenerateReverseSortedArray(size_t size) {
    std::vector<std::string> randomStringArray = GenerateArray(size);

    std::sort(randomStringArray.begin(), randomStringArray.end(), std::greater<>());

    return randomStringArray;
}

std::vector<std::string> StringArrayGenerator::GenerateParticleSortedArray(size_t size, uint32_t particleSortFactor) {
    std::vector<std::string> randomStringArray = GenerateArray(size);

    std::sort(randomStringArray.begin(), randomStringArray.end());

    size_t numberOfSwappedElements = size / (particleSortFactor == 0 ? (size + 1) : particleSortFactor);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> swap_dis(0, size - 1);

    for (int32_t i = 0; i < numberOfSwappedElements; ++i) {
        std::swap(randomStringArray[swap_dis(gen)], randomStringArray[swap_dis(gen)]);
    }

    return randomStringArray;
}
