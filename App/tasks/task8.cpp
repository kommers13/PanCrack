// task8.cpp
#include "task8.h"
#include <queue>
#include <limits>
#include <sstream>


namespace task8 {

const int inf = std::numeric_limits<int>::max();  // Define the inf constant
std::pair<int, std::vector<int>> dijkstra(const Graph& g, int start, int end) {
    const int INF = inf;  // Use the same inf constant
    int n = g.vertex_count();
    std::vector<int> dist(n, INF);
    std::vector<int> prev(n, -1);

    dist[start] = 0;

    auto cmp = [](const std::pair<int, int>& left, const std::pair<int, int>& right) {
        return left.second > right.second;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
    pq.push({start, 0});

    while (!pq.empty()) {
        auto [u, current_dist] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;
        if (u == end) break;

        for (const auto& [v, weight] : g.get_graph().at(u)) {
            if (weight == inf) continue; // Пропускаем рёбра с весом inf (из вашего графа)

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    std::vector<int> path;
    if (dist[end] == INF) {
        return {INF, path};
    }

    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return {dist[end], path};
}

std::string print_shortest_path(const Graph& g, int start, int end) {
    auto [distance, path] = dijkstra(g, start, end);
    std::stringstream ss;

    if (path.empty()) {
        ss << "No path exists from " << start + 1 << " to " << end + 1;
    } else {
        ss << "Shortest path from " << start + 1 << " to " << end + 1 << ":\n";
        ss << "Distance: " << distance << "\n";
        ss << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) ss << " → ";
            ss << path[i] + 1;
        }
    }

    return ss.str();
}

} // namespace task8
