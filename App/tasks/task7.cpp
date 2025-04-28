#include "include/task7.h"

#include <iostream>

struct Comparator {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        // priorities (weights)
        // first - vertex
        // second - priority
        return a.second > b.second;
    }
};

// считаем, что граф g является связным и неориентированным
Graph task7::create_MST(const Graph& g) {
    int sizev = g.get_cnt_vertexes();
    if (sizev == 0) {
        return g;
    }
    // мы должны брать ребра только с вершин, которые уже присоединены к дереву
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   Comparator> v_p;     // vertex, priority
    // предки вершин (индекс - предок, значение - потомок)
    vector<int> parent(sizev);
    // минимальные веса для вершин (индекс - вершина, значение - вес (приоритет))
    vector<int> min_weight(sizev, task7::inf);
    // проверенные вершины
    vector<bool> checked(sizev, 0);

    parent[0] = -1; // у начальной вершины нет предков
    min_weight[0] = 0;
    v_p.push(make_pair(0, 0));

    while (!v_p.empty()) {
        int current_v = v_p.top().first;
        v_p.pop();
        checked[current_v] = true;
        // проходимся по всем соседям
        for (auto [neighbour, weight]: g[current_v]) {
            if (!checked[neighbour] && weight < min_weight[neighbour]) {
                parent[neighbour] = current_v;
                min_weight[neighbour] = weight;
                v_p.push(make_pair(neighbour, weight));
            }
        }
    }
    Graph MST(sizev);
    for (int i = 1; i < sizev; i++) {
        MST.add_edge(i, parent[i], min_weight[i]);
    }
    // MST.print();
    return MST;

}




