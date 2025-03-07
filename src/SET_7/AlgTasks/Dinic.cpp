#include "Dinic.h"

#include <queue>

void Dinic::AddEdge(int32_t u, int32_t v, int32_t cap) {
    graph[u].push_back({v, (int32_t)graph[v].size(), cap, 0});
    graph[v].push_back({u, (int32_t)graph[u].size() - 1, 0, 0});
}

bool Dinic::Bfs(int32_t s, int32_t t) {
    fill(level.begin(), level.end(), -1);
    std::queue<int32_t> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
        int32_t u = q.front(); q.pop();
        for (DinicEdge& e : graph[u]) {
            if (level[e.to] == -1 && e.flow < e.capacity) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int32_t Dinic::Dfs(int32_t u, int32_t t, int32_t flow) {
    if (u == t) return flow;
    for (; ptr[u] < graph[u].size(); ptr[u]++) {
        DinicEdge& e = graph[u][ptr[u]];
        if (level[e.to] != level[u] + 1 || e.flow >= e.capacity) {
            continue;
        }
        int32_t pushed = Dfs(e.to, t, std::min(flow, e.capacity - e.flow));
        if (pushed > 0) {
            e.flow += pushed;
            graph[e.to][e.rev].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int32_t Dinic::maxFlow(int32_t s, int32_t t) {
    int32_t total = 0;
    while (Bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int32_t pushed = Dfs(s, t, INT_MAX))
            total += pushed;
    }
    return total;
}
