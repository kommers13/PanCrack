#ifndef TASK4_H
#define TASK4_H
#include <string>
#include <graph.h>
#include <queue>
#include <random>
#include <unordered_map>
#include <cctype>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
namespace task4
{
    string input(string user_input, string start_edge, Graph g);
    Graph rand(int vertexs);
    string parse(string& s);
    string BFS(const Graph &g, const int &start_edge);
}

#endif // TASK4_H
