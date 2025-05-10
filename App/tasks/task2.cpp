#include "task2.h"
#include <stack>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>

namespace task2 {

std::vector<int> DFS(const Graph& g, int start_vertex) {
    std::vector<int> traversal;
    if (start_vertex < 1 || start_vertex > g.vertex_count()) return traversal;

    std::vector<bool> visited(g.vertex_count() + 1, false);
    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (visited[current]) continue;
        visited[current] = true;
        traversal.push_back(current);

        auto neighbors = g.get_sorted_neighbors(current - 1);
        std::reverse(neighbors.begin(), neighbors.end());

        for (int neighbor : neighbors) {
            if (!visited[neighbor + 1]) {
                stack.push(neighbor + 1);
            }
        }
    }

    return traversal;
}

bool check_user_DFS(const Graph& g, int start_vertex, const std::vector<int>& user_traversal) {
    // Проверяем базовые условия
    if (user_traversal.empty() || user_traversal[0] != start_vertex) {
        return false;
    }

    // Проверяем, что все вершины уникальны и существуют в графе
    std::unordered_set<int> visited;
    for (int v : user_traversal) {
        if (v < 1 || v > g.vertex_count() || visited.count(v)) {
            return false;
        }
        visited.insert(v);
    }

    // Создаем копию для проверки порядка
    std::vector<int> traversal = user_traversal;
    std::reverse(traversal.begin(), traversal.end());

    std::vector<bool> marked(g.vertex_count() + 1, false);
    std::stack<int> stack;
    stack.push(start_vertex);
    marked[start_vertex] = true;

    while (!stack.empty() && !traversal.empty()) {
        int current = stack.top();
        if (current == traversal.back()) {
            traversal.pop_back();
            stack.pop();

            // Добавляем соседей в обратном порядке
            auto neighbors = g.get_sorted_neighbors(current - 1);
            std::reverse(neighbors.begin(), neighbors.end());

            for (int neighbor : neighbors) {
                int nb = neighbor + 1; // 1-based
                if (!marked[nb]) {
                    marked[nb] = true;
                    stack.push(nb);
                }
            }
        } else {
            // Проверяем, есть ли текущая вершина в оставшемся пути
            if (std::find(traversal.begin(), traversal.end(), current) == traversal.end()) {
                return false;
            }
            stack.pop();
        }
    }

    // Проверяем, что обошли всю компоненту связности
    auto correct_traversal = DFS(g, start_vertex);
    std::unordered_set<int> correct_visited(correct_traversal.begin(), correct_traversal.end());
    std::unordered_set<int> user_visited(user_traversal.begin(), user_traversal.end());

    return correct_visited == user_visited;
}

Graph generate_random_graph(int vertices) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices, 0));

    // Заполняем матрицу случайными значениями
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            matrix[i][j] = matrix[j][i] = dis(gen);
        }
    }

    // Гарантируем связность графа
    for (int i = 1; i < vertices; ++i) {
        matrix[i-1][i] = matrix[i][i-1] = 1;
    }

    return Graph(matrix);
}

} // namespace task2
