#ifndef TASK1__H
#define TASK1__H

#include <string>
#include <graph.h>
#include <map>
#include <unordered_map>
namespace task10 {

std::string coding(Graph a);

std::map<int, pair<int, int>> buildTreeMap(int n);

void printTreeMap(const std::map<int, pair<int, int>>& tree, int n);

std::string input(Graph a);

void output(std::string ans);

std::string rec_code(std::unordered_map<int, std::unordered_map<int, int>>& tree, std::string& answer);
}

#endif // TASK1__H
