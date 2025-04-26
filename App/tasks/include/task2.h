#ifndef TASK2_H
#define TASK2_H

#include "graph.h"
#include <vector>
#include <string>

namespace task2 {
    bool check_DFS(const Graph& g, const std::vector<int>& user_traversal, int start_vertex);
    std::vector<int> get_correct_DFS(const Graph& g, int start_vertex);
} // namespace task2

#endif // TASK2_H