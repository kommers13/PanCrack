// task1.h
#ifndef TASK1_H
#define TASK1_H

#include <graph.h>
#include <vector>
#include <unordered_set>

namespace task1 {

// Функция для выполнения обхода в глубину и возврата порядка посещения вершин
std::vector<std::vector<int>> DFS(const Graph& g, int start_vertex);

// Функция для вывода результата обхода в глубину
std::string print_DFS(const Graph& g, int start_vertex);

} // namespace task1

#endif // TASK1_H
