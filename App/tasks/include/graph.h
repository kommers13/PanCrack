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

    // создание графа из матрицы смежности из строкового потока
    void construct_from_string_madj(istream& in);   // НЕ РЕАЛИЗОВАН

    // создание графа из матрицы инцидентности из строкового потока
    void construct_from_string_incm(istream& in);   // НЕ РЕАЛИЗОВАН

    // создание графа из списков смежности из строкового потока
    void construct_from_string_ladj(istream& in);   // НЕ РЕАЛИЗОВАН


    // проверка, является ли граф неориентированным
    bool is_undirected(const vector<vector<int>>& madj);

    // проверка, является ли граф связным
    bool is_connected(const vector<vector<int>>& madj); // В АЛГОРИТМЫ

public:

    // нулевой граф
    Graph();

    // граф с n вершинами без ребер
    Graph(const int& n);

    // построение графа при помощи матрицы смежности
    Graph(const vector<vector<int>>& madj);

    // type = 0
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

    // type = 1
    // построение графа при помощи строкового потока с матрицей инцидентности
    /*



    */

    // type = 2
    // построение графа при помощи строкового потока со списками смежности
    /*

    0: (1, 3), (4, -2)
    1: (0, 3), (2, 5), (4, 4)
    2: (1, 5), (3, 10)
    3: (2, 10), (4, 6)
    4: (0, -2), (1, 0), (3, 6)

    */

    // istream является предком и stringstream и ifstream
    Graph(const int& type, istream& in);

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

    // проверка, является ли граф деревом
    bool is_tree() const;       // НЕ РЕАЛИЗОВАН    // В АЛГОРИТМЫ

    // GETTERS
    unordered_map<int, unordered_map<int, int>> get_graph() const;

    // является ли граф неориентированным или нет
    bool get_undirected() const;

    // tuple<int, int, int> - v1, v2, w
    // множество всех ребер графа
    unordered_set<tuple<int, int, int>, TupleHash> get_edges() const;

    // количество ребер
    int get_cnt_edges() const;

    // количество вершин
    int get_cnt_vertexes() const;

    // степень вершины v (номер вершины) графа
    // если такой вершины нет, возникнет исключение
    int get_v_degree(int v) const;

    // OPERATORS
    // сравнение графов
    bool operator==(const Graph& other) const;

    // вернуть все смежные вершины и веса
    // в виде unordered_map
    // если такой вершины не существует, то будет исключение
    unordered_map<int, int> operator[](const int& v) const;

    // вывод графа на консоль
    void print();

};

#endif // __GRAPH__
