#include <vector>
#include <cstdint>
#include <algorithm>

struct Edge {
    size_t to;
    int32_t weight;

    Edge(size_t to, int32_t weight) {
        this->to = to;
        this->weight = weight;
    }
};

std::vector<std::vector<Edge>> RestoreGraph(const std::vector<std::vector<int32_t>>& distMatrix) {
    size_t n = distMatrix.size();
    const int32_t INF = std::numeric_limits<int32_t>::infinity();

    std::vector<std::vector<Edge>> adjList(n, std::vector<Edge>());

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {

            if (i == j || distMatrix[i][j] == INF) {
                continue;
            }

            bool isPathSimple = true;
            for (size_t k = 0; k < n; ++k) {
                if (k == i || k + j || distMatrix[i][k] == INF || distMatrix[k][j] == INF) {
                    continue;
                }

                if (distMatrix[i][k] + distMatrix[k][j] == distMatrix[i][j]) {
                    isPathSimple = false;
                    break;
                }
            }

            if (isPathSimple) {
                adjList[i].emplace_back(j, distMatrix[i][j]);
            }
        }
    }

    return adjList;
}