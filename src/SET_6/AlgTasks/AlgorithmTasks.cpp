#include "AlgorithmTasks.h"

std::vector<int32_t> AlgorithmTasks::KosarajuProcessing(int32_t &id, std::stack<int32_t> &readyStack, int32_t n,
                                        const std::vector<std::vector<int32_t>> &trList) {
    std::vector<bool> visited(n, false);
    std::vector<int32_t> vertexId(n, 0);

    while (!readyStack.empty()) {
        int32_t curVertex = readyStack.top();
        readyStack.pop();
        if (!visited[curVertex]) {
            CountingDFS(curVertex, id++, visited, vertexId, trList);
        }
    }

    return vertexId;
}

void AlgorithmTasks::KosarajuDFS(int32_t vertex, const std::vector<std::vector<int32_t>> &adjList, std::vector<bool> &visited,
                 std::stack<int32_t> &readyStack) {
    visited[vertex] = true;
    for (int32_t neighbour: adjList[vertex]) {
        if (!visited[neighbour]) {
            KosarajuDFS(neighbour, adjList, visited, readyStack);
        }
    }
    readyStack.push(vertex);
}

void AlgorithmTasks::CountingDFS(int32_t vertex, int32_t sccId, std::vector<bool> &visited, std::vector<int32_t> &vertexId,
                 const std::vector<std::vector<int32_t>> &trList) {
    vertexId[vertex] = sccId;
    visited[vertex] = true;
    for (int32_t neighbour: trList[vertex]) {
        if (!visited[neighbour]) {
            CountingDFS(neighbour, sccId, visited, vertexId, trList);
        }
    }
}


std::pair<int32_t, std::vector<KruskalEdge>> AlgorithmTasks::UnionFindKruskal(const std::vector<KruskalEdge> &sortedEdges, int32_t n) {
    std::vector<int32_t> parent(n);
    for (int32_t i = 0; i < n; ++i) {
        parent[i] = i;
    }

    std::vector<KruskalEdge> mst;

    int32_t totalCost = 0;
    for (const KruskalEdge &edge: sortedEdges) {
        if (unionVertices(edge.from, edge.to, parent)) {
            mst.push_back(edge);
            totalCost += edge.cost;
        }
    }

    return std::make_pair(totalCost, mst);
}

bool AlgorithmTasks::unionVertices(int32_t u, int32_t v, std::vector<int32_t> &parent) {
    int32_t parentU = findParent(u, parent);
    int32_t parentV = findParent(v, parent);
    if (parentU == parentV) {
        return false;
    }
    parent[parentV] = u;
    return true;
}

int32_t AlgorithmTasks::findParent(int32_t v, std::vector<int32_t> &parent) {
    return parent[v] == v ? v : parent[v] = findParent(parent[v], parent);
}


std::stack<bool> AlgorithmTasks::ProcessDSUOperations(std::stack<DSUOperation>& operations, int32_t n) {
    std::vector<int32_t> parent(n);
    for (int32_t i = 0; i < n; ++i) {
        parent[i] = i;
    }

    std::stack<bool> resultStack;

    while (!operations.empty()) {
        DSUOperation curOperation = operations.top();
        operations.pop();

        if (curOperation.type == DSUOperationType::Ask) {
            resultStack.push(isVerticesInOneSCC(curOperation.from, curOperation.to, parent));
        } else {
            unionDSUVertices(curOperation.from, curOperation.to, parent);
        }

    }
    return resultStack;
}

bool AlgorithmTasks::isVerticesInOneSCC(int32_t u, int32_t v, std::vector<int32_t> &parent) {
    int32_t parentU = findDSUParent(u, parent);
    int32_t parentV = findDSUParent(v, parent);

    return parentU == parentV;
}

void AlgorithmTasks::unionDSUVertices(int32_t u, int32_t v, std::vector<int32_t> &parent) {
    int32_t parentU = findDSUParent(u, parent);
    int32_t parentV = findDSUParent(v, parent);
    if (parentU == parentV) {
        return;
    }
    parent[parentV] = u;
}

int32_t AlgorithmTasks::findDSUParent(int32_t v, std::vector<int32_t> &parent) {
    return parent[v] == v ? v : parent[v] = findDSUParent(parent[v], parent);
}


void AlgorithmTasks::FloydWarshallAPSP(std::vector<std::vector<int64_t>>& distanceMatrix, int32_t n) {
    const int64_t INF = INT64_MAX;

    for (int32_t k = 0; k < n; ++k) {
        for (int32_t i = 0; i < n; ++i) {
            for (int32_t j = 0; j < n; ++j) {
                if (distanceMatrix[i][k] < INF && distanceMatrix[k][j] < INF) {
                    distanceMatrix[i][j] = std::min(distanceMatrix[i][j], distanceMatrix[i][k] + distanceMatrix[k][j]);
                }
            }
        }
    }
}

std::vector<int64_t> AlgorithmTasks::BellmanFordSSSP(const std::vector<BellmanFordEdge> &edges, int32_t n) {
    const int64_t inf = 1e12 + 7;
    std::vector<int64_t> distances(n, inf);
    distances[0] = 0;

    for (int32_t i = 0; i < n; ++i) {
        for (auto curEdge: edges) {
            if (distances[curEdge.from] < inf && distances[curEdge.from] + curEdge.cost < distances[curEdge.to]) {
                distances[curEdge.to] = distances[curEdge.from] + curEdge.cost;
            }
        }
    }

    for (int32_t i = 0; i < n; ++i) {
        for (auto curEdge: edges) {
            if (distances[curEdge.from] < inf && distances[curEdge.from] + curEdge.cost < distances[curEdge.to]) {
                distances[curEdge.to] = -inf;
            }
        }
    }


    return distances;
}