#include "task11.h"
using namespace std;

Graph task11::input(string code, string points){
    Graph g =(task11::decoding(code, points));
    return g;
}
Graph task11::decoding(string code, string n){
    string c_size = "";
    for(const auto& el : code){
        if(el != ' ')
            c_size += el;
    }
    int sz = c_size.size()+1;
    Graph tree(sz);
    // Вектор кода прюфера
    vector<int> prufer;

    stringstream ss(code);
    int num;
    while (ss >> num) {
        prufer.push_back(num);
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
        tree.add_edge(u, v, 1);
        //cout << u << " " << v << '\n';
        // Обновляем структуры данных
        prufer.erase(prufer.begin());
        auto it = prufer_set.find(u);
        if (it != prufer_set.end()) {
            prufer_set.erase(it);
        }
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





