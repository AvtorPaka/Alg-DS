#ifndef ALGORITHMTASKS_7_H
#define ALGORITHMTASKS_7_H

#include <vector>
#include <cstdint>

struct EdmondEdge2 {
    int32_t to;
    int32_t rev;
    int64_t capacity;
    int64_t flow;
};

struct EdmondEdge {
    int32_t to;
    int32_t flowCapacity;

    EdmondEdge(int32_t to, int32_t flowCapacity) {
        this->to = to;
        this->flowCapacity = flowCapacity;
    }
};

class AlgorithmTasks {
private:

    // Edmond Karp MaxFlow
    static int64_t EdmondKarpBfs(int32_t s, int32_t t, std::vector<std::vector<int64_t>>& resNetwork, std::vector<int32_t>& parentList, const std::vector<std::vector<EdmondEdge>>& adjList);
    static int64_t EdmondKarp2Bfs(int32_t s, int32_t t, std::vector<int32_t>& parentList, const std::vector<std::vector<EdmondEdge2>>& adjList);

    // BipartiteMatching
    static bool BipartiteMatchingDfs(int32_t vert, std::vector<std::vector<int32_t>>& adjList, std::vector<bool>& visited, std::vector<int32_t>& rightMatch);

public:

    // Edmond Karp MaxFlow
    static int64_t EdmondKarp(int32_t s, int32_t t, const std::vector<std::vector<EdmondEdge>>& adjList);
    static int64_t EdmondKarp2(int32_t s, int32_t t, const std::vector<std::vector<EdmondEdge2>>& adjList);

    // BipartiteMatching
    static int32_t BipartiteMatching(std::vector<std::vector<int32_t>>& adjList, size_t rightPower, size_t leftPower);
};


#endif //ALGORITHMTASKS_7_H
