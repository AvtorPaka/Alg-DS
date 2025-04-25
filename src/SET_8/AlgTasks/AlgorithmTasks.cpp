#include "AlgorithmTasks.h"

#include <queue>

int32_t AlgorithmTasks::FindMinimalRepetativeSegment(const std::string& line) {
    int32_t n = line.size();
    std::vector<int32_t> prefixList = CalculatePrefixFunction(line);

    return (n - prefixList[n - 1]);
}

std::vector<int32_t> AlgorithmTasks::CalculatePrefixFunction(const std::string& line) {
    size_t n = line.length();
    std::vector<int32_t> prefixList(n, 0);

    int32_t borderLen = 0;

    for (int32_t i = 1; i < n; ++i) {

        while (borderLen >= 1 && (line[borderLen] != line[i])) {
            borderLen = prefixList[borderLen - 1];
        }

        if (line[borderLen] == line[i]) {
            ++borderLen;
        }

        prefixList[i] = borderLen;
    }

    return prefixList;
}

std::vector<int32_t > AlgorithmTasks::KMPMatching(const std::string& patter, const std::string& text) {
    size_t m = patter.size();
    size_t n = text.size();
    std::vector<int32_t> prefixList = CalculateRefinedPrefixFunction(patter);

    std::vector<int32_t> matchingFirstIndexes;

    int32_t matched = 0;
    int32_t i = 0;
    while (i < n) {
        while (matched > 0 && (patter[matched] != text[i])) {
            matched = prefixList[matched - 1];
        }

        if (patter[matched] == text[i]) {
            matched++;
        }

        if (matched == m) {
            matchingFirstIndexes.push_back(i + 1 - m);
            matched = prefixList[matched - 1];
        }

        i++;
    }

    return matchingFirstIndexes;
}

std::vector<int32_t> AlgorithmTasks::CalculateRefinedPrefixFunction(const std::string& line) {
    std::vector<int32_t> prefix = CalculatePrefixFunction(line);
    size_t n = line.size();
    std::vector<int32_t> refined(n, 0);
    for (size_t i = 0; i < n; ++i) {
        int32_t current = prefix[i];
        if (i < n - 1) {
            while (current > 0 && line[current] == line[i + 1]) {
                current = prefix[current - 1];
            }
        }
        refined[i] = current;
    }
    return refined;
}

std::vector<int32_t> AlgorithmTasks::BoyerMooreHorspoolMatching(const std::string& text, const std::string& pattern) {
    std::vector<int32_t> matchedStartIndexes;
    int32_t n = text.size();
    int32_t m = pattern.size();

    if (m == 0 || n < m) {
        return matchedStartIndexes;
    }

    std::unordered_map<char, int32_t> distanceMap = CalculateDistanceTable(pattern);

    int32_t shift = 0;

    while (shift <= n - m) {
        int32_t j = m - 1;

        while (j >= 0 && text[shift + j] == pattern[j]) {
            j--;
        }

        if (j < 0) {
            matchedStartIndexes.push_back(shift);
            shift++;
        } else {
            char last_char = text[shift + m - 1];
            int32_t shift_val = m;
            if (distanceMap.find(last_char) != distanceMap.end()) {
                shift_val = distanceMap[last_char];
            }
            shift += shift_val;
        }
    }

    return matchedStartIndexes;
}

std::unordered_map<char, int32_t> AlgorithmTasks::CalculateDistanceTable(const std::string& pattern) {
    std::unordered_map<char, int32_t> table;
    int32_t m = pattern.size();
    if (m == 0) return table;

    for (int32_t i = 0; i < m - 1; ++i) {
        table[pattern[i]] = i;
    }

    for (auto& pair : table) {
        pair.second = (m - 1) - pair.second;
    }

    return table;
}

int32_t AlgorithmTasks::LevenshteinDistance(const std::string &stringOne, const std::string &stringTwo) {
    size_t n = stringOne.size();
    size_t m = stringTwo.size();

    if (m == 0) {
        return n;
    } if (n == 0) {
        return m;
    }

    std::vector<int32_t> previousRow(m + 1, 0);
    std::vector<int32_t> currentRow(m + 1, 0);

    for (int32_t i = 0; i < m + 1; ++i) {
        previousRow[i] = i;
    }

    for (int32_t i = 1; i < n + 1; ++i) {
        currentRow[0] = i;

        for (int32_t j = 1; j < m + 1; ++j) {
            if (stringOne[i - 1] == stringTwo[j - 1]) {
                currentRow[j] = previousRow[j - 1];
            } else {
                currentRow[j] = 1 + std::min(currentRow[j - 1], std::min(previousRow[j], previousRow[j - 1]));
            }
        }

        previousRow = currentRow;
    }

    return currentRow[m];
}

int64_t AlgorithmTasks::ManakerCountPalindromes(const std::string &text) {
    int64_t palindromesCount = 0;
    size_t n = text.size();

    std::vector<int64_t> oddPalindromesCount(n);
    std::vector<int64_t> evenPalindromesCount(n);

    int64_t l = 0;
    int64_t r = -1;
    for (int64_t i = 0; i < n; ++i) {
        int64_t mirror = l + r - i;
        int64_t k = (i > r || mirror < 0 || mirror >= n) ? 1 : std::min(oddPalindromesCount[mirror], r - i + 1);
        while (i + k < n && i - k >= 0 && text[i + k] == text[i - k]) {
            ++k;
        }
        oddPalindromesCount[i] = --k;
        palindromesCount += k + 1;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int64_t k = i > r ? 0 : std::min(evenPalindromesCount[l + r - i + 1], r - i + 1);
        while (i + k < n && i - k - 1 >= 0 && text[i + k] == text[i - k - 1]) {
            ++k;
        }
        evenPalindromesCount[i] = k;
        palindromesCount += k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    return palindromesCount;
}

std::vector<std::vector<int32_t>> AlgorithmTasks::AhoCorasick(const std::string& text, const std::vector<std::string>& patterns) {
    std::vector<ACNode> nodes;
    nodes.emplace_back();
    size_t n = patterns.size();

    for (size_t i = 0; i < n; ++i) {
        if (!patterns[i].empty()) {
            AddPattern(nodes, patterns[i], static_cast<int32_t>(i));
        }
    }


    BuildAutomaton(nodes);

    std::vector<std::vector<int32_t>> occurrences(n);

    int32_t current_node = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i] - 'a';

        while (current_node != 0 && nodes[current_node].next[c] == -1) {
            current_node = nodes[current_node].link;
        }

        if (nodes[current_node].next[c] != -1) {
            current_node = nodes[current_node].next[c];
        }

        int32_t temp_node = current_node;
        while (temp_node != -1) {
            if (!nodes[temp_node].pattern_indices.empty()) {
                int32_t depth = nodes[temp_node].depth;
                int32_t start_pos = static_cast<int32_t>(i) - depth + 1;
                for (int32_t idx : nodes[temp_node].pattern_indices) {
                    if (idx >= 0 && static_cast<size_t>(idx) < n) {
                        occurrences[idx].push_back(start_pos + 1);
                    }
                }
            }
            temp_node = nodes[temp_node].exit;
        }
    }

    return occurrences;
}

void AlgorithmTasks::AddPattern(std::vector<ACNode>& nodes, const std::string &pattern, int32_t pattern_index) {
    int32_t current = 0;
    for (char c : pattern) {
        int32_t idx = c - 'a';
        if (nodes[current].next[idx] == -1) {
            nodes.emplace_back();
            nodes.back().depth = nodes[current].depth + 1;
            nodes[current].next[idx] = static_cast<int32_t>(nodes.size() - 1);
        }
        current = nodes[current].next[idx];
    }
    nodes[current].pattern_indices.push_back(pattern_index);
}

void AlgorithmTasks::BuildAutomaton(std::vector<ACNode>& nodes) {
    std::queue<int32_t> q;

    nodes[0].link = 0;
    nodes[0].exit = -1;
    for (int32_t c = 0; c < 26; ++c) {
        int32_t child = nodes[0].next[c];
        if (child != -1) {
            nodes[child].link = 0;
            nodes[child].exit = -1;
            q.push(child);
        }
    }

    while (!q.empty()) {
        int32_t u = q.front();
        q.pop();

        for (int32_t c = 0; c < 26; ++c) {
            int32_t v = nodes[u].next[c];
            if (v == -1) continue;

            int32_t fallback = nodes[u].link;
            while (fallback != 0 && nodes[fallback].next[c] == -1) {
                fallback = nodes[fallback].link;
            }
            if (nodes[fallback].next[c] != -1) {
                fallback = nodes[fallback].next[c];
            }

            nodes[v].link = fallback;

            if (!nodes[fallback].pattern_indices.empty()) {
                nodes[v].exit = fallback;
            } else {
                nodes[v].exit = nodes[fallback].exit;
            }

            if (nodes[v].exit == v) {
                nodes[v].exit = -1;
            }

            q.push(v);
        }
    }
}
