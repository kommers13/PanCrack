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
            char name_v1 = name_vs[v1];
            char name_v2 = name_vs[v2];
            // string ws = to_string(w);
            QVariantList qpair;
            qpair << QString(name_v2) << w;
            qvmap.insert(QString(name_v1), QVariant::fromValue(qpair));
        }
    }

    QVariantMap gmap;

    gmap.insert("graph", QVariant::fromValue(qvmap));
    gmap.insert("namevs", QVariant::fromValue(name_vs));

    // qDebug() << qvmap;

    return gmap;
}

// функция записывает объект в JSON-файл
// создается новый файл
// эта функция выполняется тогда, когда файла с таким именем точно НЕТ
void dataconverse::fromGraphToJSONfile(const Graph& G, const string& filename) {
    const string path = "graphs";
    ofstream out(path + "/" + filename + ".json");

    json j; // объект JSON
    auto graph = G.get_graph();
    vector<char> name_vs = G.get_vs_name();

    // в файле всегда должны быть два поля: graph и namevs
    j["graph"] = {};

    j["namevs"] = {};

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
// <graph_name>.json - это имя файла, в котором хранится граф.
// Если эта функция выполняется, то такой файл УЖЕ ТОЧНО ЕСТЬ
Graph dataconverse::fromJSONfileToGraph(const string& graph_name) {
    ifstream in("graphs/" + graph_name + ".json");
    json j = json::parse(in);

    Graph graph;

    for (auto namev: j["namevs"]) {
        graph.add_vertex((char)namev.get<int>());
    }

    for (auto [v1, edge]: j["graph"].items()) {
        // three - { "n": {"m": w} }
        for (auto [v2, w]: edge.items()) {
            graph.add_edge(stoi(v1),
                           stoi(v2),
                           w);
        }
    }

    return graph;

}
