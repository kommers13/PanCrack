#ifndef TASK3_H
#define TASK3_H
#include <string>
#include <graph.h>
#include <vector>
#include <queue>
#include <algorithm>
namespace task3{
std::string input(Graph g, string s_e);
std::string BFS(const Graph &g, const int &s_e);
}

#endif // TASK3_H
