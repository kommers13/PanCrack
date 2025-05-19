#include "task2.h"
#include <stack>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>

namespace task2 {
std::vector<int> DFS(const Graph& g, int start_vertex) {
    std::vector<int> traversal;

    // Проверка корректности стартовой вершины (0-based)
    if (start_vertex < 0 || start_vertex >= g.get_cnt_vertexes()) {
        return traversal;
    }

    std::vector<bool> visited(g.get_cnt_vertexes(), false); // 0-based
    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (visited[current]) continue;
        visited[current] = true;
        traversal.push_back(current);

        // Получаем отсортированных соседей (0-based)
        auto neighbors = g.get_sorted_neighbors(current);
        // Добавляем в стек в обратном порядке
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            int neighbor = *it;
            if (!visited[neighbor]) {
                stack.push(neighbor);
            }
        }
    }

    return traversal;
}

bool is_valid_dfs(const Graph& g, const std::vector<int>& traversal) {
    if (traversal.empty()) return false;

    std::vector<bool> visited(g.get_cnt_vertexes() + 1, false);
    visited[traversal[0]] = true;

    for (size_t i = 1; i < traversal.size(); ++i) {
        int current = traversal[i];
        if (current < 1 || current > g.get_cnt_vertexes() || visited[current]) {
            return false;
        }

        auto neighbors = g.get_sorted_neighbors(traversal[i-1] - 1);
        bool is_neighbor = std::find(neighbors.begin(), neighbors.end(), current - 1) != neighbors.end();
        if (!is_neighbor) {
            return false;
        }

        visited[current] = true;
    }

    return true;
}


bool check_user_DFS(const Graph& g, int start_vertex, const std::vector<int>& user_traversal) {
    // Проверяем базовые условия
    if (user_traversal.empty() || user_traversal[0] != start_vertex) {
        return false;
    }

    // Проверяем, что все вершины уникальны и существуют в графе
    std::unordered_set<int> visited;
    for (int v : user_traversal) {
        if (v < 1 || v > g.get_cnt_vertexes() || visited.count(v)) {
            return false;
        }
        visited.insert(v);
    }

    // Создаем копию для проверки порядка
    std::vector<int> traversal = user_traversal;
    std::reverse(traversal.begin(), traversal.end());

    std::vector<bool> marked(g.get_cnt_vertexes() + 1, false);
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

void dfs_permutations(const Graph& g, int current, std::vector<bool>& visited,
                      std::vector<int>& path, std::vector<std::vector<int>>& results) {
    visited[current] = true;
    path.push_back(current + 1); // Переводим в 1-based индекс

    auto neighbors = g.get_sorted_neighbors(current);

    if (neighbors.empty()) {
        results.push_back(path);
    } else {
        do {
            bool has_unvisited = false;
            for (int neighbor : neighbors) {
                if (!visited[neighbor]) {
                    has_unvisited = true;
                    dfs_permutations(g, neighbor, visited, path, results);
                    break;
                }
            }
            if (!has_unvisited) {
                results.push_back(path);
            }
        } while (std::next_permutation(neighbors.begin(), neighbors.end()));
    }

    visited[current] = false;
    path.pop_back();
}

std::vector<std::vector<int>> generate_all_possible_dfs(const Graph& g, int start_vertex) {
    std::vector<std::vector<int>> results;
    if (start_vertex < 1 || start_vertex > g.get_cnt_vertexes()) return results;

    std::vector<bool> visited(g.get_cnt_vertexes(), false);
    std::vector<int> path;
    dfs_permutations(g, start_vertex - 1, visited, path, results);

    return results;
}


Graph generate_random_graph(int vertices) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));

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

std::string print_DFS(const Graph& g, int start_vertex) {
    auto all_paths = DFS(g, start_vertex);
    std::stringstream ss;
    vector<char> vc = g.get_vs_name();

    for (size_t j = 0; j < all_paths.size(); ++j) {
        ss << vc[all_paths[j]];
    }


    return ss.str();
}
} // namespace task2
