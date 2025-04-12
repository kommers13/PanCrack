#include "include/task7.h"



vector<tuple<int, int, int>> sort_edges(const Graph& g) {
    unordered_set<tuple<int, int, int>, TupleHash> edges = g.get_edges();

    vector<tuple<int, int, int>> sorted_edges(edges.begin(), edges.end());

    auto comparator = [=] (const tuple<int, int, int>& t1,
                           const tuple<int, int, int>& t2) {
        return get<2>(t1) < get<2>(t2);
    };

    sort(sorted_edges.begin(), sorted_edges.end(), comparator);

    return sorted_edges;
}

// считаем, что граф g является связным и неориентированным
Graph task7::create_MST(const Graph& g) {
    vector<tuple<int, int, int>> se = sort_edges(g);

    unordered_set<int> svs; // множество вершин MST

    int nv = g.get_graph().size();

    Graph MST(nv);

    for (auto edge: se) {
        int v1, v2, w;
        v1 = get<0>(edge);
        v2 = get<1>(edge);
        w =  get<2>(edge);
        // если хотя бы одна из вершин не принадлежит MST, то это ребро добавляем в MST
        if (svs.find(v1) == svs.end() || svs.find(v2) == svs.end()) {
            MST.add_edge(v1, v2, w);
            svs.insert(v1);
            svs.insert(v2);
        }
        if (svs.size() == nv) {     // все вершины соединены, поэтому заканчиваем
            break;
        }
    }

    return MST;

}




