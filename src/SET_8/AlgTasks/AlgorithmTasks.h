#ifndef ALGORITHMTASKS_8_H
#define ALGORITHMTASKS_8_H

#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <array>

struct ACNode {
    std::array<int32_t, 26> next;
    int32_t link;
    int32_t exit;
    std::vector<int32_t> pattern_indices;
    int32_t depth;

    ACNode() : link(-1), exit(-1), depth(0) {
        next.fill(-1);
    }
};

class AlgorithmTasks {
public:
    static std::vector<int32_t > KMPMatching(const std::string& patter, const std::string& text);

    static std::vector<int32_t> CalculatePrefixFunction(const std::string& line);

    static int32_t FindMinimalRepetativeSegment(const std::string& line);

    static std::vector<int32_t> CalculateRefinedPrefixFunction(const std::string& line);

    static std::vector<int32_t> BoyerMooreHorspoolMatching(const std::string& text, const std::string& pattern);

    static int32_t LevenshteinDistance(const std::string &stringOne, const std::string &stringTwo);

    static int64_t ManakerCountPalindromes(const std::string &text);

    static std::vector<std::vector<int32_t>> AhoCorasick(const std::string& text, const std::vector<std::string>& patterns);

private:
    static void AddPattern(std::vector<ACNode>& nodes, const std::string &pattern, int32_t pattern_index);

    static void BuildAutomaton(std::vector<ACNode>& nodes);

    static std::unordered_map<char, int32_t> CalculateDistanceTable(const std::string& pattern);

};


#endif //ALGORITHMTASKS_8_H
