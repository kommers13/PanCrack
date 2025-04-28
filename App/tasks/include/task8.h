// task8.h
#ifndef TASK8_H
#define TASK8_H

#include <graph.h>
#include <vector>
#include <string>
#include <utility>

extern const int inf;

namespace task8 {

std::pair<int, std::vector<int>> dijkstra(const Graph& g, int start, int end);
std::string print_shortest_path(const Graph& g, int start, int end);

} // namespace task8

#endif // TASK8_H
