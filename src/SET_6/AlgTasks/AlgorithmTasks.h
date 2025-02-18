#ifndef ALGORITHMTASKS_6_H
#define ALGORITHMTASKS_6_H

#include <vector>
#include <cstdint>
#include <stack>

enum DSUOperationType {
    Add,
    Ask
};

struct DSUOperation {
    DSUOperationType type;
    int32_t from;
    int32_t to;

    DSUOperation(DSUOperationType t, int32_t f, int32_t to) {
        this->type = t;
        this->from = f;
        this->to = to;
    }
};

struct BellmanFordEdge {
    int32_t from;
    int32_t to;
    int64_t cost;

    BellmanFordEdge(int32_t from, int32_t to, int64_t cost) {
        this->from = from;
        this->to = to;
        this->cost = cost;
    }
};

struct KruskalEdge {
    int32_t from;
    int32_t to;
    int32_t cost;

    KruskalEdge(int32_t f, int32_t t, int32_t c) {
        this->from = f;
        this->to = t;
        this->cost = c;
    }

    bool operator<(const KruskalEdge &other) const {
        return this->cost < other.cost;
    }

    bool operator==(const KruskalEdge &other) const {
        return this->to == other.to && this->from == other.from && this->cost == other.cost;
    }
};

class AlgorithmTasks {
public:

    // Kosaraju scc counting
    static void KosarajuDFS(int32_t vertex, const std::vector<std::vector<int32_t>> &adjList, std::vector<bool> &visited,
                     std::stack<int32_t> &readyStack);

    static std::vector<int32_t> KosarajuProcessing(int32_t &id, std::stack<int32_t> &readyStack, int32_t n,
                                            const std::vector<std::vector<int32_t>> &trList);

    // Kruskal MST
    static std::pair<int32_t, std::vector<KruskalEdge>> UnionFindKruskal(const std::vector<KruskalEdge> &sortedEdges, int32_t n);

    // DSU Vertices in one SCC check
    static std::stack<bool> ProcessDSUOperations(std::stack<DSUOperation>& operations, int32_t n);


    static void FloydWarshallAPSP(std::vector<std::vector<int64_t>>& distanceMatrix, int32_t n);


    static std::vector<int64_t> BellmanFordSSSP(const std::vector<BellmanFordEdge> &edges, int32_t n);

private:
    // Kruskal MST
    static int32_t findParent(int32_t v, std::vector<int32_t> &parent);

    static  bool unionVertices(int32_t u, int32_t v, std::vector<int32_t> &parent);

    // Kosaraju scc counting
    static void CountingDFS(int32_t vertex, int32_t sccId, std::vector<bool> &visited, std::vector<int32_t> &vertexId,
                     const std::vector<std::vector<int32_t>> &trList);

    // DSU Vertices in one SCC check
    static bool isVerticesInOneSCC(int32_t u, int32_t v, std::vector<int32_t> &parent);

    static int32_t findDSUParent(int32_t v, std::vector<int32_t> &parent);

    static  void unionDSUVertices(int32_t u, int32_t v, std::vector<int32_t> &parent);
};


#endif //ALGORITHMTASKS_6_H
