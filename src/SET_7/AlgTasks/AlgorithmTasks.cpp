#include "AlgorithmTasks.h"

#include <queue>
#include <utility>

int64_t AlgorithmTasks::EdmondKarp(int32_t s, int32_t t, const std::vector<std::vector<EdmondEdge>>& adjList) {
    size_t n = adjList.size();
    int64_t maxFlow = 0;
    std::vector<int32_t> parentList(n);

    std::vector<std::vector<int64_t>> resNetwork(n, std::vector<int64_t>(n, 0));
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < adjList[i].size(); ++j) {
            EdmondEdge curEdge = adjList[i][j];
            resNetwork[i][curEdge.to] = curEdge.flowCapacity;
        }
    }

    int64_t pathFlow;
    while ((pathFlow = EdmondKarpBfs(s, t, resNetwork, parentList, adjList)) != 0) {
        int32_t curVert = t;

        while (curVert != s) {
            int32_t prevVert = parentList[curVert];
            resNetwork[prevVert][curVert] -= pathFlow;
            resNetwork[curVert][prevVert] += pathFlow;
            curVert = prevVert;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int64_t AlgorithmTasks::EdmondKarpBfs(int32_t s, int32_t t,
                      std::vector<std::vector<int64_t>>& resNetwork,
                      std::vector<int32_t>& parentList,
                      const std::vector<std::vector<EdmondEdge>>& adjList) {

    const int64_t INF = INT64_MAX;
    size_t n = resNetwork.size();
    std::fill(parentList.begin(), parentList.end(), -1);
    parentList[s] = -2;
    std::queue<std::pair<int32_t, int64_t>> q;
    q.emplace(s, INF);

    while (!q.empty()) {
        int32_t curVert = q.front().first;
        int64_t curFlow = q.front().second;
        q.pop();

        for (int32_t nextVert = 0; nextVert < n; ++nextVert) {
            if (resNetwork[curVert][nextVert] > 0 && parentList[nextVert] == -1) {
                parentList[nextVert] = curVert;
                int64_t newFlow = std::min(curFlow, resNetwork[curVert][nextVert]);
                if (nextVert == t) {
                    return newFlow;
                }
                q.emplace(nextVert, newFlow);
            }
        }
    }

    return 0;
}

int64_t AlgorithmTasks::EdmondKarp2Bfs(int32_t s, int32_t t,
                      std::vector<int32_t>& parentList,
                      const std::vector<std::vector<EdmondEdge2>>& adjList) {
    std::fill(parentList.begin(), parentList.end(), -1);
    parentList[s] = -2;
    std::queue<std::pair<int32_t, int64_t>> q;
    q.emplace(s, INT64_MAX);

    while (!q.empty()) {
        int32_t curVert = q.front().first;
        int64_t curFlow = q.front().second;
        q.pop();

        for (const EdmondEdge2& e : adjList[curVert]) {
            if (parentList[e.to] == -1 && e.capacity > e.flow) {
                parentList[e.to] = curVert;
                int64_t new_flow = std::min(curFlow, e.capacity - e.flow);
                if (e.to == t)
                    return new_flow;
                q.emplace(e.to, new_flow);
            }
        }
    }

    return 0;
}

int64_t AlgorithmTasks::EdmondKarp2(int32_t s, int32_t t, const std::vector<std::vector<EdmondEdge2>>& adjList) {
    size_t n = adjList.size();
    int64_t maxFlow = 0;
    std::vector<int32_t> parentList(n);

    std::vector<std::vector<EdmondEdge2>> resGraph = adjList;

    int64_t pathFlow;
    while ((pathFlow = EdmondKarp2Bfs(s, t, parentList, resGraph)) != 0) {

        int32_t curVert = t;
        while (curVert != s) {
            int32_t prevVert = parentList[curVert];

            for (EdmondEdge2& e : resGraph[prevVert]) {
                if (e.to == curVert) {
                    e.flow += pathFlow;
                    resGraph[curVert][e.rev].flow -= pathFlow;
                    break;
                }
            }

            curVert = prevVert;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int32_t AlgorithmTasks::BipartiteMatching(std::vector<std::vector<int32_t>>& adjList, size_t rightPower, size_t leftPower) {
    int32_t maxMatching = 0;
    std::vector<bool> visited(leftPower, false);
    std::vector<int32_t> rightMatch(rightPower, -1);

    for (int32_t i = 0; i < leftPower; ++i) {
        visited.assign(rightPower, false);
        if (BipartiteMatchingDfs(i, adjList, visited, rightMatch)) {
            maxMatching++;
        }
    }

    return maxMatching;
}


bool AlgorithmTasks::BipartiteMatchingDfs(int32_t vert, std::vector<std::vector<int32_t>>& adjList, std::vector<bool>& visited, std::vector<int32_t>& rightMatch) {

    for (int nextVert : adjList[vert]) {
        if (!visited[nextVert]) {
            visited[nextVert] = true;
            if (rightMatch[nextVert] == -1 || BipartiteMatchingDfs(rightMatch[nextVert], adjList, visited, rightMatch)) {
                rightMatch[nextVert] = vert;
                return true;
            }
        }
    }
    return false;
}