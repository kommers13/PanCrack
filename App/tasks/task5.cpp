#include "task5.h"
#include <stack>
#include <algorithm>
#include <sstream>

namespace task5 {

namespace {
std::vector<int> DFS(const Graph& g, int start_vertex, std::vector<bool>& visited) {
    std::vector<int> component;
    if (start_vertex < 0 || start_vertex >= g.get_cnt_vertexes()) return component;

    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (visited[current]) continue;
        visited[current] = true;
        component.push_back(current);

        auto neighbors = g.get_sorted_neighbors(current);
        std::reverse(neighbors.begin(), neighbors.end());

        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                stack.push(neighbor);
            }
        }
    }

    return component;
}
}

std::vector<std::vector<int>> find_connected_components(const Graph& g) {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(g.get_cnt_vertexes(), false);

    for (int i = 0; i < g.get_cnt_vertexes(); ++i) {
        if (!visited[i]) {
            std::vector<int> component = DFS(g, i, visited);
            components.push_back(component);
        }
    }

    return components;
}

std::string print_connected_components(const Graph& g) {
    auto components = find_connected_components(g);
    std::stringstream ss;

    ss << "Number of connected components: " << components.size() << "\n";
    ss << "Connected components:\n";
    int cnt = 1;
    vector<char> vc = g.get_vs_name();
    for (const auto& component : components) {
        ss << to_string(cnt) << " level"<<", vertexes: ";
        ++cnt;
        for (size_t i = 0; i < component.size(); ++i) {
            if (i != 0) ss << " ";
            ss << vc[component[i]]; // Convert to 1-based for output
        }
        ss << "\n";
    }

    return ss.str();
}

} // namespace task5
