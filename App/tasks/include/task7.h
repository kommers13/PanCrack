#ifndef TASK7_H
#define TASK7_H

#include <graph.h>

#include <map>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>

/*
Задача: реализовать алгоритм построения минимального остовного дерева
Входные данные: связный неориентированный граф (пока считаем, что все графы связные)
Выходные данные: минимальное остовное дерево
*/

using namespace std;

namespace task7 {

const int inf = 1e9;

// считаем, что все графы, которые подаются на вход, связные неориентированные
Graph create_MST(const Graph& g);

}

#endif // TASK7_H
