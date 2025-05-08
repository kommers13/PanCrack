#include "include/dataconverse.h"

// функция преобразовывает объект типа Graph в QVariantMap
QVariantMap dataconverse::fromGraphToQVariantMap(const Graph& G) {
    QVariantMap qvmap;
    auto graph = G.get_graph();
    vector<char> name_vs = G.get_vs_name();
    for (auto l: graph) {   // list
        int v1 = l.first;   // номер вершины (НЕ ИМЯ)
        for (auto p: l.second) {    // pair
            int v2 = p.first;   // номер соседней вершины (НЕ ИМЯ)
            int w = p.second;   // вес ребра
            string name_v1 = to_string(name_vs[v1]);
            string name_v2 = to_string(name_vs[v2]);
            string ws = to_string(w);
            auto qpair = QPair(name_v2.c_str(), ws.c_str());
            qvmap[name_v1.c_str()] = QVariant::fromValue(qpair);
        }
    }
    return qvmap;
}

// функция записывает объект в JSON-файл
// создается новый файл
// эта функция выполняется тогда, когда файла с таким именем точно НЕТ
void dataconverse::fromGraphToJSONfile(const Graph& G, const string& filename) {
    const string path = "graphs";
    ofstream out(path + "\\" + filename + ".json");

    json j; // объект JSON
    auto graph = G.get_graph();
    vector<char> name_vs = G.get_vs_name();

    // записываем граф в JSON-файл
    for (auto l: graph) {   // list
        int v1 = l.first;   // номер вершины (НЕ ИМЯ)

        for (auto p: l.second) {    // pair

            int v2 = p.first;   // номер соседней вершины (НЕ ИМЯ)
            int w = p.second;   // вес ребра
            string name_v1 = to_string(v1); // ключ в JSON-файле, поэтому он СТРОКА
            string name_v2 = to_string(v2); // ключ в JSON-файле, поэтому он СТРОКА
            j["graph"][name_v1][name_v2] = w;

        }
    }
    // записываем имена вершин в JSON-файл
    for (auto name: name_vs) {
        j["namevs"].push_back(name);
    }
    out << j;

}

// функция преобразовывает JSON-файл в объект типа Graph
// <graph_name>.json - это имя файла, в котором хранится граф
// если эта функция выполняется, то такой файл УЖЕ ТОЧНО ЕСТЬ
Graph dataconverse::fromJSONfileToGraph(const string& graph_name) {
    return Graph();
}
