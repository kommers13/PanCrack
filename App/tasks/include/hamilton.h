#ifndef HAMILTON_H
#define HAMILTON_H

#include <graph.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

namespace hamilton {

vector<string> hamilton_cycles(const Graph& G);

}

#endif // HAMILTON_H
