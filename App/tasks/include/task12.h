#ifndef TASK12_H
#define TASK12_H
#include <iostream>
#include <graph.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
namespace task12
{
    std::string input(Graph g);
    std::pair<vector<int>, string> coloring(Graph& g);
}

#endif // TASK12_H
