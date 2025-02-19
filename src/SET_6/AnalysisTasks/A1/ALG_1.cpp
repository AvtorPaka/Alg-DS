#include <cstdint>
#include <list>
#include <algorithm>

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

// Интерфейс Link-Cut Tree
class LinkCutTree {
public:
    // Создание вершины и добавление как отдельное дерево
    // O(1)
    void makeTree(int32_t v);

    // Проверка нахождения двух вершин в одной компоненте связности
    // O(log(V))
    bool connected(int32_t u, int32_t v);

    // Добавление ребра между вершинами u и v
    // O(log(V))
    void link(int32_t u, int32_t v);

    // Удаление ребра между вершинами u и v
    // O(log(V))
    void cut(int32_t u, int32_t v);
};

// O(E * log(V))
std::list<Edge> ALG_1(const std::vector<int32_t> &vertices, std::list<Edge> &edgeList) {

    // Сортировка списка ребер по невозрастанию
    // O(E * log(E))
    edgeList.sort([](const Edge &a, const Edge &b) {
        return a.cost > b.cost;
    });

    // Добавление вершин в lct
    // O(V)
    LinkCutTree lct;
    for (int32_t i = 0; i < vertices.size(); ++i) {
        lct.makeTree(vertices[i]);
    }

    // Добавление всех ребер в lct
    // O(E * log(E))
    std::list<Edge>::iterator it;
    for (it = edgeList.begin(); it != edgeList.end(); ++it) {
        lct.link(it->from, it->to);
    }

    std::list<Edge> T(edgeList);
    std::list<Edge>::iterator removeIterator = T.begin();

    // O(E * log(V))
    for (it = edgeList.begin(); it != edgeList.end(); ++it) {
        lct.cut(it->from, it->to);  // O(log(V))
        if (!lct.connected(it->from, it->to)) {     // Проверка на связность, O(log(V))
            lct.link(it->from, it->to);     // O(log(V))
        } else {
            T.erase(removeIterator);    // O(1)
        }
        removeIterator++;
    }

    return T;
}