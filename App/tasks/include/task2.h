#ifndef TASK2_H
#define TASK2_H

#include <graph.h>
#include <vector>
#include <string>

namespace task2 {

// Функция для выполнения обхода в глубину и возврата порядка посещения вершин
std::vector<int> DFS(const Graph& g, int start_vertex);

// Функция для проверки пользовательского обхода
bool check_user_DFS(const Graph& g, int start_vertex, const std::vector<int>& user_traversal);

// Функция для генерации случайного графа
Graph generate_random_graph(int vertices);

} // namespace task2

#endif // TASK2_H
