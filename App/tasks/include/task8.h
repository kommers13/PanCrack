// task8.h
#ifndef TASK8_H
#define TASK8_H

#include <graph.h>
#include <vector>
#include <utility>

namespace task8 {

extern const int inf;

// Функция для поиска кратчайшего пути (1-based вершины)
// Возвращает пару: расстояние и вектор вершин пути
std::pair<int, std::vector<int>> find_shortest_path(const Graph& g, int start, int end);

} // namespace task8

#endif // TASK8_H
