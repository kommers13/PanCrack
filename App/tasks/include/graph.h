#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <algorithm>



using namespace std;

struct TupleHash {
    size_t operator()(const std::tuple<int, int, int>& t) const;
};


class Graph {

    /* A: (B, 1), (C, -2)
       B: (A, 1), (C, 3), (D, 5)
       C: (B, 3), (A, -2)
       D: (B, 5), (E, 10), (G, 7)
       E: (D, 10), (F, 0)
       F: (G, 8), (E, 0)
       G: (D, 7), (F, 8)
    */

    // названия вершин
    vector<char> vs;
    // хранение графа в виде неотсортированного map-а
    unordered_map<int, unordered_map<int, int>> graph;
    // для некоторых задачи ориентированный граф может не работать (в данном случае для всех)
    bool undirected;    // true - неориентированный, false - ориентированный

    // является ли граф связным
    // true - DEBUG, пока считаем, что все графы - связные
    bool connected = true;     // true - связный граф, false - несвязный граф

private:

    // создании графа из матрицы смежности
    void create_from_madj(const vector<vector<int>>& madj);

    // проверка, является ли граф неориентированным
    bool is_undirected(const vector<vector<int>>& madj);

    // проверка, является ли граф связным
    bool is_connected(const vector<vector<int>>& madj);

public:

    const std::unordered_map<int, int>& get_raw_neighbors(int vertex) const {
        return graph.at(vertex);
    }

    // Объявление без реализации
    std::vector<int> get_sorted_neighbors(int vertex) const;

    bool has_vertex(int vertex) const;
    size_t vertex_count() const;

    // нулевой граф
    Graph();

    // граф с n вершинами без ребер
    Graph(const int& n);

    // построение графа при помощи матрицы смежности
    Graph(const vector<vector<int>>& madj);


    // построение графа при помощи строкового потока с матрицей смежности
    // ввод
    /*

    5
    0 3 inf inf -2
    3 0 5 inf 4
    inf 5 0 10 inf
    inf inf 10 0 6
    -2 0 inf 6 0

    */
    // istream является предком и stringstream и ifstream
    Graph(istream& in);

    // добавить вершину
    void add_vertex();

    // удалить вершину по номеру
    void delete_vertex(int num);            // НЕ РЕАЛИЗОВАН

    // добавить ребро
    // v1, v2 - вершины, которые будут соединяться ребрами
    // w - вес ребра
    // нумерация вершин начинается с 0
    void add_edge(int v1, int v2, int w);

    // удалить ребро по вершинам, которые его соединяют
    // если ребро не существует, то выбросится исключение
    void delete_edge(int v1, int v2);           // НЕ РЕАЛИЗОВАН

    // GETTERS
    unordered_map<int, unordered_map<int, int>> get_graph() const;

    bool get_undirected() const;

    // tuple<int, int, int> - v1, v2, w
    // множество все ребер графа
    unordered_set<tuple<int, int, int>, TupleHash> get_edges() const;

    // вывод графа на консоль
    void print();

    // OPERATORS
    // сравнение графов
    bool operator==(const Graph& other) const;

    // проверка, является ли граф деревом
    bool is_tree() const;

    // количество ребер
    int cnt_edges() const;

    // количество вершин
    int cnt_vertexes() const;

};

#endif // __GRAPH__
