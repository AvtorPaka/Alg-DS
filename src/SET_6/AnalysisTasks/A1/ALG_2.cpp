#include <vector>
#include <cstdint>

struct Edge {
    int32_t from;
    int32_t to;
    int32_t cost;

    Edge(int32_t from, int32_t to, int32_t cost) {
        this->from = from;
        this->to = to;
        this->cost = cost;
    }
};

// Интерфейс UnionFind на основе "деревьев"
class UnionFind {
public:
    // Создание множества из одного элемента
    // O(1)
    void makeSet(int32_t vertix);
    // Определение представителя множества к которому принадлежит вершина
    // O(a(V))
    int32_t find(int32_t vertix);
    // Объединение множеств, содержащих вершины vert1 и vert2
    // O(a(V))
    void unionVertices(int32_t vert1, int32_t vert2);
};


// O(E * a(V))
std::vector<Edge> ALG_2(const std::vector<int32_t>& verticesArray, const std::vector<Edge>& edgesArray) {
    // Инициализация T и UnionFind
    std::vector<Edge> T;
    UnionFind uf;

    // Инициализация UnionFind
    // O(V)
    for (auto vert: verticesArray) {
        uf.makeSet(vert);
    }

    // O(E * a(V))
    for (auto curEdge : edgesArray) {
        // Проверка на образование цикла в графе T
        // O(a(V))
        if (uf.find(curEdge.from) != uf.find(curEdge.to)) {
            T.push_back(curEdge);
            uf.unionVertices(curEdge.from, curEdge.to); // O(a(V))
        }
    }

    return T;
}