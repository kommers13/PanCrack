#ifndef TASK5_H
#define TASK5_H

#include <graph.h>
#include <vector>
#include <string>

namespace task5 {

// Функция для поиска компонент связности
std::vector<std::vector<int>> find_connected_components(const Graph& g);

// Функция для вывода компонент связности
std::string print_connected_components(const Graph& g);

} // namespace task5

#endif // TASK5_H
