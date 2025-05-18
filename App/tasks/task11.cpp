#include "task11.h"
using namespace std;

Graph task11::input(string code, string points){
    Graph g =(task11::decoding(code));
    return g;
}
Graph task11::decoding(string code){
    // Парсим количество вершин (n >= 0)
    vector<int> P;
    stringstream ss(code);
    string numStr;
    while (getline(ss, numStr, ',')) {
        P.push_back(stoi(numStr));
    }

    int n = P.size() + 1; // Количество вершин в дереве
    Graph tr(n); // Инициализация матрицы INF

    vector<int> degree(n, 1); // степени вершин (изначально все листья)

    // Увеличиваем степени для вершин из кода Прюфера
    for (int u : P) {
        degree[u]++;
    }

    set<int> leaves;
    // Находим все листья (степень = 1)
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            leaves.insert(i);
        }
    }

    for (int u : P) {
        // Берем минимальный лист
        int v = *leaves.begin();
        leaves.erase(leaves.begin());

        // Добавляем ребро в матрицу (для неориентированного дерева симметрично)
        tr.add_edge(u,v,1);
        // Обновляем степени
        if (--degree[u] == 1) {
            leaves.insert(u);
        }
    }

    // Добавляем последнее ребро
    if (leaves.size() == 2) {
        int u = *leaves.begin();
        leaves.erase(leaves.begin());
        int v = *leaves.begin();
        tr.add_edge(u,v,1);
    }
    return tr;

}
