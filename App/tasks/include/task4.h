#ifndef TASK4_H
#define TASK4_H
#include <string>
#include <graph.h>
#include <queue>
#include <random>
#include <unordered_map>
namespace task4
{
    bool input(string user_input, string start_edge, Graph g);
    Graph rand(int vertexs);
    string parse(string& s);
    string BFS(const Graph &g, const int &start_edge);
}

#endif // TASK4_H
