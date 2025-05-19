#include "task1.h"
#include <stack>
#include <sstream>

namespace task1 {

std::vector<std::vector<int>> DFS(const Graph& g, int start_vertex) {
    std::vector<std::vector<int>> all_paths;
    std::vector<int> current_path;

    if (start_vertex < 0 || start_vertex >= g.get_cnt_vertexes()) {
        return all_paths;
    }

    std::vector<bool> visited(g.get_cnt_vertexes(), false);
    std::stack<std::pair<int, std::vector<int>>> stack;
    stack.push({start_vertex, {start_vertex}});

    while (!stack.empty()) {
        auto [current, path] = stack.top();
        stack.pop();

        if (!path.empty() && path.back() != current) {
            // Это случай, когда мы возвращаемся из тупика
            path.push_back(current);
        }

        all_paths.push_back(path);

        if (visited[current]) continue;

        visited[current] = true;
        current_path = path;

        auto neighbors = g.get_sorted_neighbors(current);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            int neighbor = *it;
            if (!visited[neighbor]) {
                std::vector<int> new_path = path;
                new_path.push_back(neighbor);
                stack.push({neighbor, new_path});
            }
        }
    }

    return all_paths;
}

std::string print_DFS(const Graph& g, int start_vertex) {
    auto all_paths = DFS(g, start_vertex);
    std::stringstream ss;
    std::stringstream final_ss; // Для итогового пути
    vector<char> vc = g.get_vs_name();

    // Собираем итоговый путь (первое вхождение каждой вершины)
    std::vector<int> final_path;
    std::vector<bool> visited(g.get_cnt_vertexes(), false);
    for (const auto& path : all_paths) {
        for (int v : path) {
            if (!visited[v]) {
                final_path.push_back(v);
                visited[v] = true;
            }
        }
    }

    // Выводим все пути с возвратами
    for (size_t i = 0; i < all_paths.size(); ++i) {
        if (i != 0) ss << "<br>"; // Разделяем пути переносами строк
        for (size_t j = 0; j < all_paths[i].size(); ++j) {
            if (j != 0) ss << " → ";
            ss << "<b>" << vc[all_paths[i][j]] << "</b>";
        }
    }

    // Выводим итоговый путь
    final_ss << "<br><br>Final DFS path: ";
    for (size_t i = 0; i < final_path.size(); ++i) {
        if (i != 0) final_ss << " → ";
        final_ss << "<b>" << vc[final_path[i]] << "</b>";
    }

    return ss.str() + final_ss.str() + "<br>";
}
} // namespace task1
