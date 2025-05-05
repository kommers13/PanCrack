#ifndef TASK9_H
#define TASK9_H

#include <graph.h>
#include <vector>
#include <string>
#include <stdexcept> // Добавьте этот include

namespace task9 {

// Функция для алгоритма Флойда-Уоршелла (возвращает матрицу расстояний)
std::vector<std::vector<int>> floyd_warshall(const Graph& g);

// Функция для форматированного вывода матрицы расстояний
std::string print_distance_matrix(const std::vector<std::vector<int>>& dist_matrix);

} // namespace task9

#endif // TASK9_H
