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
    return g;
}




