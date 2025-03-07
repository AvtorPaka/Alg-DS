#ifndef IMPLEMENTATIONDATA_DINIC_H
#define IMPLEMENTATIONDATA_DINIC_H

#include <cstdint>
#include <vector>

struct DinicEdge {
    int32_t to;
    int32_t rev;
    int32_t capacity;
    int32_t flow;
};

class Dinic {
public:
    std::vector<std::vector<DinicEdge>> graph;
    std::vector<int32_t> level, ptr;
    int32_t n;

    Dinic(int32_t n) : n(n), graph(n), level(n), ptr(n) {}

    void AddEdge(int32_t u, int32_t v, int32_t cap);

    bool Bfs(int32_t s, int32_t t);

    int32_t Dfs(int32_t u, int32_t t, int32_t flow);

    int32_t maxFlow(int32_t s, int32_t t);
};


#endif //IMPLEMENTATIONDATA_DINIC_H
