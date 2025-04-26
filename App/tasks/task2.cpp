#include "task2.h"
#include <stack>
#include <algorithm>

namespace task2 {

    std::vector<int> get_correct_DFS(const Graph& g, int start_vertex) {
        std::vector<int> traversal;
        auto graph = g.get_graph();
        int vertex_count = g.cnt_vertexes();

        if (start_vertex < 0 || start_vertex >= vertex_count) {
            return traversal;
        }

        std::vector<bool> visited(vertex_count, false);
        std::stack<int> stack;

        stack.push(start_vertex);
        visited[start_vertex] = true;

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            traversal.push_back(current);

            auto neighbors = graph.at(current);
            for (const auto& neighbor : neighbors) {
                int neighbor_vertex = neighbor.first;
                if (!visited[neighbor_vertex]) {
                    visited[neighbor_vertex] = true;
                    stack.push(neighbor_vertex);
                }
            }
        }

        return traversal;
    }

    bool check_DFS(const Graph& g, const std::vector<int>& user_traversal, int start_vertex) {
        auto correct_traversal = get_correct_DFS(g, start_vertex);

        // Фильтрация некорректных значений (1-based vs 0-based)
        std::vector<int> filtered_user;
        for (int v : user_traversal) {
            if (v >= 1 && v <= g.cnt_vertexes()) {
                filtered_user.push_back(v - 1); // Конвертируем в 0-based
            }
        }

        return filtered_user == correct_traversal;
    }

} // namespace task2