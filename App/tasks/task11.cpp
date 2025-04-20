#include "task11.h"
using namespace std;

Graph task11::input(string code, string points){
    vector<int> vec_points;
    for(auto el : points){
        vec_points.push_back(int(el));
    }
    Graph g = task11::decoding(code, vec_points);
    return g;
}
Graph task11::decoding(string code, vector<int> points){
    Graph tree;
    std::vector<int> prufer(code.begin(), code.end());
    for (auto& c : prufer) {
        c -= '0';
    }
    while (!prufer.empty()) {
        // 1. Берём первый элемент кода Прюфера
        int u = prufer.front();
        // 2. Находим минимальную вершину, отсутствующую в коде
        int v = -1;
        set<int>pruferSet(prufer.begin(), prufer.end());
        for (int point : points) {
            if (pruferSet.find(point) == pruferSet.end()) {
                v = point;
                break;
            }
        }
        if (v == -1) {
            // Если все вершины есть в коде, берём минимальную
            v = *min_element(points.begin(), points.end());
        }
        // Добавляем ребро в граф
        tree.add_edge(u, v, 0);

        // Удаляем использованные элементы
        prufer.erase(prufer.begin());
        points.erase(remove(points.begin(), points.end(), v), points.end());
    }

    // Добавляем последнее ребро между оставшимися вершинами
    if (points.size() == 2) {
        tree.add_edge(points[0], points[1], 0);
    }

    return tree;
}





