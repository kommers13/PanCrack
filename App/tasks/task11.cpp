#include "task11.h"
using namespace std;

Graph task11::input(string code, string points){
    return (task11::decoding(code, points));
}
Graph task11::decoding(string code, string n){
    Graph tree;
    // Вектор кода прюфера
    vector<int> prufer;

    for(char& el : code) {
        prufer.push_back(el - '0');
    }

    multiset<int> prufer_set(prufer.begin(), prufer.end());
    set<int> all_nodes;
    // Инициализация всех вершин
    for (int i = 0; i < stoi(n); ++i) {
        all_nodes.insert(i);
    }

    while (!prufer.empty()) {
        int u = prufer.front();
        // Находим минимальную вершину, не входящую в код Прюфера
        int v = -1;
        for (int node : all_nodes) {
            if (prufer_set.count(node) == 0) {
                v = node;
                break;
            }
        }
        // Добавляем ребро
        tree.add_edge(u, v, 0);
        //cout << u << " " << v << '\n';
        // Обновляем структуры данных
        prufer.erase(prufer.begin());
        prufer_set.erase(prufer_set.find(u));
        all_nodes.erase(v);
    }

    // Добавляем последнее ребро между оставшимися вершинами
    if (all_nodes.size() == 2) {
        auto it = all_nodes.begin();
        int u = *it++;
        int v = *it;
        tree.add_edge(u, v, 0);
    }

    return tree;
}





