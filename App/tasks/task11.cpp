#include "task11.h"
using namespace std;

Graph task11::input(string code, string points){
    Graph g =(task11::decoding(code, points));
    return g;
}
Graph task11::decoding(string code, string n_str){
    // Парсим количество вершин (n >= 0)
    int n = stoi(n_str);
    if (n <= 0) return Graph(0);  // Пустой граф при n = 0 или ошибке

    // Парсим код Прюфера (числа от 0 до n-1)
    vector<int> prufer;
    stringstream ss(code);
    string token;

    while (ss >> token) {
        int num = stoi(token);
        if (num < 0 || num >= n) return Graph(0);  // Проверка 0-индексации
        prufer.push_back(num);
    }

    // Проверка длины кода Прюфера (должно быть n-2 элементов)
    if (prufer.size() != n - 2 && n != 1) return Graph(0);

    // Специальный случай: дерево из одной вершины (пустой код Прюфера)
    if (n == 1) return Graph(1);

    // Инициализация графа и степеней вершин
    Graph tree(n);
    vector<int> degree(n, 1);  // degree[u] = 1 для всех вершин

    // Увеличиваем степень для вершин из кода Прюфера
    for (int u : prufer) degree[u]++;

    // Множество листьев (вершины со степенью 1)
    set<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) leaves.insert(i);
    }

    // Восстановление рёбер
    for (int u : prufer) {
        if (leaves.empty()) return Graph(0);  // Ошибка в коде

        int v = *leaves.begin();  // Наименьший лист
        leaves.erase(leaves.begin());


        // Обновляем степени
        if (--degree[u] == 1) leaves.insert(u);
    }

    // Последнее ребро между оставшимися двумя вершинами
    if (leaves.size() == 2) {
        int u = *leaves.begin();
        leaves.erase(leaves.begin());
        int v = *leaves.begin();
    }

    return tree;
}
