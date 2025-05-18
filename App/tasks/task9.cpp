#include "task9.h"
#include <algorithm>
#include <sstream>
#include <climits>

namespace task9 {

std::vector<std::vector<int>> floyd_warshall(const Graph& g) {
    int n = g.get_cnt_vertexes();
    const int INF = INT_MAX / 2;
    const int NEG_INF = -INF; // Для обозначения -∞

    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));

    // Инициализация матрицы расстояний
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        auto neighbors = g[i];
        for (const auto& neighbor : neighbors) {
            int j = neighbor.first;
            int weight = neighbor.second;
            dist[i][j] = weight;
        }
    }

    // Основной алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Проверка на переполнение и обновление расстояния
                if (dist[i][k] < INT_MAX / 2 && dist[k][j] < INT_MAX / 2) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Обнаружение отрицательных циклов
    for (int k = 0; k < n; ++k) {
        if (dist[k][k] < 0) { // Найден отрицательный цикл через вершину k
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    // Если путь проходит через вершину k с отрицательным циклом
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        // Помечаем путь как -∞
                        dist[i][j] = NEG_INF;
                    }
                }
            }
        }
    }

    return dist;
}

std::string print_distance_matrix(const std::vector<std::vector<int>>& dist_matrix) {
    std::stringstream ss;
    int n = dist_matrix.size();
    const int INF = INT_MAX / 2;
    const int NEG_INF = -INF;

    ss << "\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist_matrix[i][j] >= INF) {
                ss << "INF ";
            } else if (dist_matrix[i][j] <= NEG_INF) {
                ss << "-INF ";
            } else {
                ss << dist_matrix[i][j] << " ";
            }
        }
        ss << "\n";
    }

    return ss.str();
}

} // namespace task9
