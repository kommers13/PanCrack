#ifndef TASK6_H
#define TASK6_H

#include <graph.h>
#include <string>
#include <utility> // для std::pair

namespace task6 {

// Генерирует случайный граф с n вершинами
Graph generate_random_graph(int n);

// Возвращает строковое представление матрицы смежности
std::string graph_to_string(const Graph& g);

// Проверяет ответ пользователя
std::pair<bool, std::string> check_answer(const Graph& g, int user_answer);

} // namespace task6

#endif // TASK6_H
