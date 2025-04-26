#include "include/task7.h"

#include <iostream>

const int inf = 1e9;

struct Comparator {
    bool operator()(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        // priorities (weights)
        return get<2>(a) > get<2>(b);
    }
};

// считаем, что граф g является связным и неориентированным, и ненулевым
Graph task7::create_MST(const Graph& g) {
    int sizev = g.get_cnt_vertexes();

    // (vertex <----> minimum vertex) and weight
    // unordered_map<int, pair<int, int>> v_mv_w;
    vector<tuple<int, int, int>> v_mv_w;

    // vertex, dependent vertex, priority (weight) (по неубыванию)
    priority_queue<tuple<int, int, int>,
                   vector<tuple<int, int, int>>,
                   Comparator> v_p;
    // запихиваем (shove) все вершины в приоритетную очередь
    // первую вершину (индекс 0) запихиваем в очередь с приоритетом 0
    // все остальные вершины идут с приоритетом inf
    v_p.push(make_tuple(0, inf, inf));
    for (int i = 1; i < sizev; i++) {
        v_p.push(make_tuple(i, inf, inf));
    }
    unordered_set<int> checked;     // проверенные вершины
    // проделываем действия, пока проверены НЕ ВСЕ вершины
    while (checked.size() < sizev) {
        // он должен брать первую непроверенную вершину в приоритетной очереди
        auto vp = v_p.top(); // vertex, dependent vertex, priority
        int current_v = get<0>(vp);
        // если вершина уже была проверена, то удаляем ее и продолжаем на новой итерации
        if (checked.count(current_v) > 0) {
            v_p.pop();
            continue;
        }
        // запихиваем в очередь всех соседей
        for (auto [neighbour, weight]: g[current_v]) {
            // если сосед проверен, то идем на следующую итерацию
            if (checked.count(neighbour) > 0) {
                continue;
            }
            // if (v_mv_w.find(current_v) == v_mv_w.end()) {
            //     v_mv_w[current_v] = make_pair(neighbour, weight);
            // }
            // else {
            //     if (v_mv_w[current_v].second > weight) {
            //         v_mv_w[current_v] = make_pair(neighbour, weight);
            //     }
            // }
            v_p.push(make_tuple(current_v, neighbour, weight));
        }
        // cout << v_mv_w[current_v].second << '\n';
        checked.insert(current_v);
        v_mv_w.push_back(v_p.top());
        v_p.pop();  // удаляем первый элемент из очереди, так как он уже проверен
    }
    Graph MST(sizev);
    for (auto t: v_mv_w) {
        int v1 = get<0>(t);
        int v2 = get<1>(t);
        int w = get<2>(t);
        cout << (char)(v1 + 'A') << ' ' << (char)(v2 + 'A') << ' ' << w << '\n';
        MST.add_edge(v1, v2, w);
    }
    MST.print();
    return MST;

}




