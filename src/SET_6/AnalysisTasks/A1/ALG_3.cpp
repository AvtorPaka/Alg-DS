#include <vector>
#include <cstdint>
#include <unordered_map>

struct Edge {
    int32_t from;
    int32_t to;
    int32_t cost;
    size_t hash;

    Edge(int32_t from, int32_t to, int32_t cost) {
        this->from = from;
        this->to = to;
        this->cost = cost;
    }
};

// Интерфейс Link-Cut Tree
class LinkCutTree2 {
public:
    // Создание вершины и добавление как отдельное дерево
    // O(1)
    void makeTree(int32_t v);
    // Добавление ребра между вершинами u и v
    // O(log(V))
    void link(int32_t u, int32_t v);
    // Удаление ребра между вершинами u и v
    // O(log(V))
    void cut(int32_t u, int32_t v);
    // Поиск максимального ребра на пути между вершинами u и v
    // O(log(V))
    Edge queryMax(int32_t u, int32_t v);
};

// Интерфейс UnionFind на основе "деревьев"
class UnionFind2 {
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

//  O(E + V + E * (a(V) + log(V))) = O(E * (a(V) + log(V))) = O(E * log(V))
std::vector<Edge> ALG_3(const std::vector<int32_t>& verticesArray, const std::vector<Edge>& edgesArray) {
    // Инициализация soft-delete хэш-таблицы
    // O(E)
    std::unordered_map<size_t , bool> isEdgeUsed;
    for (Edge edge: edgesArray) {
        isEdgeUsed[edge.hash] = false;
    }

    // Добавление вершин в LCT
    // O(V)
    LinkCutTree2 lct;
    for (int vert: verticesArray) {
        lct.makeTree(vert);
    }

    // Инициализация UnionFind
    // O(V)
    UnionFind2 uf;
    for (auto vert: verticesArray) {
        uf.makeSet(vert);
    }

    std::vector<Edge> T;

    // O(E * (a(V) + log(V)))
    for (Edge curEdge: edgesArray) {
        // Проверка на образование цикла в графе T
        // O(a(V))
        if (uf.find(curEdge.from) != uf.find(curEdge.to)) {

            uf.unionVertices(curEdge.from, curEdge.to);  // O(a(V))
            lct.link(curEdge.from, curEdge.to);         // O(log(V))
            isEdgeUsed[curEdge.hash] = true;            // O(1)

        } else {

            // Поиск максимального по весу ребра на пути между вершинами u-v
            // O(log(V))
            Edge maxCostEdge = lct.queryMax(curEdge.from, curEdge.to);

            // Если текущее на добавление ребро максимальное по весу
            if (curEdge.cost >= maxCostEdge.cost) {
                continue; // Пропускаем удаление, так как не было физического добавления текущего ребра
            }

            // Удаление максимального по весу ребра
            isEdgeUsed[maxCostEdge.hash] = false;       // O(1)
            lct.cut(maxCostEdge.from, maxCostEdge.to);  // O(log(V))

            // Добавление текущего ребра как не максимального
            uf.unionVertices(curEdge.from, curEdge.to);  // O(a(V))
            lct.link(curEdge.from, curEdge.to);         // O(log(V))
            isEdgeUsed[curEdge.hash] = true;            // O(1)
        }
    }

    // Сбор T по данным из soft-delete хэш-таблицы
    // O(E)
    for (Edge edge: edgesArray) {
        if (isEdgeUsed[edge.hash]) {
            T.push_back(edge);
        }
    }

    return T;
}