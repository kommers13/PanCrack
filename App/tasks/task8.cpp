#include "task8.h"
#include <queue>
#include <limits>
#include <sstream>
#include <algorithm>

namespace task8 {

const int inf = std::numeric_limits<int>::max();


std::pair<int, std::vector<int>> find_shortest_path(const Graph& g, int start, int end) {
    // Проверка на пустой граф
    if (g.vertex_count() == 0) {
        return {inf, {}};
    }

    // Проверка на валидность входных вершин
    if (start < 1 || end < 1 || start > g.vertex_count() || end > g.vertex_count()) {
        return {inf, {}};
    }

    // Специальный случай: путь из вершины в саму себя
    if (start == end) {
        return {0, {start}};
    }

    int start_0 = start - 1;
    int end_0 = end - 1;
    int n = g.vertex_count();
    std::vector<int> dist(n, inf);
    std::vector<int> prev(n, -1);
    dist[start_0] = 0;

    auto cmp = [](const std::pair<int, int>& left, const std::pair<int, int>& right) {
        return left.second > right.second;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
    pq.push({start_0, 0});

    bool reachable = false;
    while (!pq.empty()) {
        auto [u, current_dist] = pq.top();
        pq.pop();

        if (u == end_0) {
            reachable = true;
            break;
        }
        if (current_dist > dist[u]) continue;

        for (const auto& [v, weight] : g[u]) {
            if (weight != inf && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    // Восстановление пути
    std::vector<int> path;
    if (reachable) {
        for (int at = end_0; at != -1; at = prev[at]) {
            path.push_back(at + 1);
        }
        std::reverse(path.begin(), path.end());
        return {dist[end_0], path};
    }

    // Если путь не существует, возвращаем inf и пустой вектор
    return {inf, {}};
}

} // namespace task8
