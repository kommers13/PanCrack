#include "task6.h"
#include <random>
#include <sstream>
#include <algorithm>
#include <stack>

namespace task6 {

Graph generate_random_graph(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    Graph g(n);
    double p = 0.4; // Вероятность наличия ребра

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dis(gen) < p) {
                g.add_edge(i, j, 1);
            }
        }
    }
    return g;
}

std::string graph_to_string(const Graph& g) {
    std::stringstream ss;
    int n = g.get_cnt_vertexes();

    ss << "Сгенерированный граф (" << n << " вершин):\n";
    ss << "Матрица смежности:\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ss << (g.get_graph().at(i).count(j) ? "1 " : "0 ");
        }
        ss << "\n";
    }
    return ss.str();
}

std::pair<bool, std::string> check_answer(const Graph& g, int user_answer) {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(g.get_cnt_vertexes(), false);

    for (int i = 0; i < g.get_cnt_vertexes(); ++i) {
        if (!visited[i]) {
            std::vector<int> component;
            std::stack<int> s;
            s.push(i);

            while (!s.empty()) {
                int current = s.top();
                s.pop();

                if (visited[current]) continue;
                visited[current] = true;
                component.push_back(current);

                // Получаем соседей через get_sorted_neighbors
                auto neighbors = g.get_sorted_neighbors(current);
                for (auto neighbor : neighbors) {
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
            components.push_back(component);
        }
    }

    int correct_answer = components.size();
    bool is_correct = (user_answer == correct_answer);

    std::string message = "Ваш ответ: " + std::to_string(user_answer) + "\n"
                                                                        "Правильный ответ: " + std::to_string(correct_answer) + "\n"
                                                             "Результат: " + (is_correct ? "ПРАВИЛЬНО" : "НЕПРАВИЛЬНО");

    return {is_correct, message};
}

} // namespace task6
