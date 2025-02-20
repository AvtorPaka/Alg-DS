#include <vector>
#include <queue>
#include <utility>
#include <cstdint>

struct Edge {
    size_t to;
    double weight;
};

std::vector<double> DijkstraMULT(const std::vector<std::vector<Edge>> &adjList, size_t start) {
    size_t n = adjList.size();
    const double INF = std::numeric_limits<double>::infinity();

    std::vector<bool> visited(n, false);

    std::vector<double> distancesVec(n, INF);
    distancesVec[start] = 1.0;

    // std::pair<вес, вершина>
    std::priority_queue<std::pair<double, size_t>, std::vector<std::pair<double, size_t>>, std::greater<>> pq;
    pq.emplace(1.0, start);

    while (!pq.empty()) {
        double curMinWight = pq.top().first;
        size_t vert = pq.top().second;
        visited[vert] = true;
        pq.pop();

        if (curMinWight > distancesVec[vert]) {
            continue;
        }

        for (auto edge: adjList[vert]) {
            if (!visited[edge.to]) {
                double curWeight = curMinWight * edge.weight;
                if (curWeight < distancesVec[edge.to]) {
                    distancesVec[edge.to] = curWeight;
                    pq.emplace(curWeight, edge.to);
                }
            }
        }
    }

    distancesVec[start] = 0;

    return distancesVec;
}