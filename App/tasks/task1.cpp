#include "task1.h"
#include <stack>
#include <sstream>

namespace task1 {

std::vector<int> DFS(const Graph& g, int start_vertex) {
    std::vector<int> traversal_order;
    auto graph = g.get_graph();
    int vertex_count = g.get_cnt_vertexes();

    // Проверка на корректность вершины
    if (start_vertex < 1 || start_vertex > vertex_count) {
        return traversal_order;
    }

    std::vector<bool> visited(vertex_count + 1, false); // Индексация с 1
    std::stack<int> stack;

    int internal_start = start_vertex - 1;
    stack.push(internal_start);
    visited[internal_start] = true;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        traversal_order.push_back(current + 1); // Возвращаем 1-based

        auto neighbors = graph.at(current);
        for (const auto& neighbor : neighbors) {
            int neighbor_vertex = neighbor.first;
            if (!visited[neighbor_vertex]) {
                visited[neighbor_vertex] = true;
                stack.push(neighbor_vertex);
            }
        }
    }

    return traversal_order;
}

std::string print_DFS(const Graph& g, int start_vertex) {
    auto traversal = DFS(g, start_vertex);
    std::stringstream ss;

    for (size_t i = 0; i < traversal.size(); ++i) {
        if (i != 0) ss << " ";
        ss << traversal[i]; // Уже 1-based
    }

    return ss.str();
}
}
