#include "task1.h"
#include <stack>
#include <sstream>

namespace task1 {

std::vector<int> DFS(const Graph& g, int start_vertex) {

    std::vector<int> traversal;
    if (start_vertex < 1 || start_vertex > g.get_cnt_vertexes()) {
        return traversal;
    }

    std::vector<bool> visited(g.get_cnt_vertexes() + 1, false); // 1-based
    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (visited[current]) continue;
        visited[current] = true;
        traversal.push_back(current);

        // Получаем отсортированных соседей (0-based)
        auto neighbors = g.get_sorted_neighbors(current - 1);
        // Добавляем в стек в обратном порядке
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            int neighbor = *it + 1; // переводим в 1-based
            if (!visited[neighbor]) {
                stack.push(neighbor);
            }
        }
    }

    return traversal;
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
