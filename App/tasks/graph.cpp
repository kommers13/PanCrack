#include <graph.h>



size_t TupleHash::operator()(const tuple<int, int, int>& t) const {
    auto hash_int = hash<int>{};
    size_t h1 = hash_int(get<0>(t));
    size_t h2 = hash_int(get<1>(t));
    size_t h3 = hash_int(get<2>(t));
    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

const int inf = 1e9;


// построение графа при помощи матрицы смежности
void Graph::create_from_madj(const vector<vector<int>>& madj) {

    undirected = is_undirected(madj);


    // DEBUG
    if (!undirected) {
        throw domain_error("This is not undirected graph!");
    }
    // END DEBUG (remove on release)


    for (int i = 0; i < madj.size(); i++) {

        vs.push_back((char)(i + 'A'));    // по умолчанию вершины будут называться заглавными буквами английского алфавита

        unordered_map<int, int> neighbours;

        for (int j = 0; j < madj.size(); j++) {

            if (i != j && madj[i][j] != inf) {
                neighbours[j] = madj[i][j];
            }
        }
        graph[i] = neighbours;
    }
}

// создание графа из матрицы смежности из строкового потока
void Graph::construct_from_string_madj(istream& in) {
    int n;
    in >> n;
    vector<vector<int>> madj(n, vector<int>(n));
    string buffer;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> buffer;
            if (buffer == "inf") {
                madj[i][j] = inf;
            }
            else {
                madj[i][j] = stoi(buffer);
            }
        }
    }
    create_from_madj(madj);
}

// создание графа из матрицы инцидентности из строкового потока
void Graph::construct_from_string_incm(istream& in) {

}   // НЕ РЕАЛИЗОВАН

// создание графа из списков смежности из строкового потока
void Graph::construct_from_string_ladj(istream& in) {

}   // НЕ РЕАЛИЗОВАН


// проверка, является ли граф неориентированным
bool Graph::is_undirected(const vector<vector<int>>& madj) {
    for (int i = 0; i < madj.size(); i++) {
        for (int j = 0; j < madj.size(); j++) {
            if (madj[i][j] != madj[j][i]) {
                return false;
            }
        }
    }
    return true;
}


// нулевой граф
Graph::Graph() {}

// граф с n вершинами без ребер
Graph::Graph(const int& n) {
    for (int i = 0; i < n; i++) {
        this->add_vertex();
    }
}

// построение графа при помощи матрицы смежности
Graph::Graph(const vector<vector<int>>& madj) : graph() {
    create_from_madj(madj);
}


// построение графа при помощи строкового потока
Graph::Graph(const int& type, istream& in) : graph() {
    switch (type) {
        case 0: {
            construct_from_string_madj(in);
            break;
        }
        case 1: {
            // construct_from_string_incm(in);
            break;
        }
        case 2: {
            // construct_from_string_ladj(in);
            break;
        }
    }
}

// добавление вершины
void Graph::add_vertex() {
    graph[vs.size()] = {};
    if (vs.size() == 0) {
        vs.push_back('A');
    }
    else {
        vs.push_back((char)(vs[vs.size() - 1] + 1));
    }
}

// добавление ребра
// нумерация вершин начинается с 0
// в данном случае ребро может затирать вес уже существующего
void Graph::add_edge(int v1, int v2, int w) {
    int sz = vs.size();
    if (v1 != v2 &&     // если не кольцо
        ((v1 < sz) && (v2 < sz))    // если вершины уже есть в графе
        ) {
        graph[v1][v2] = w;
        graph[v2][v1] = w;
    }
    else {
        // exception
    }

}

bool Graph::is_tree() const {
    return 0;
}

// GETTERS
int Graph::get_cnt_edges() const {
    int cntedges = 0;
    for(auto [point, way] : graph){
        int cnt_point_ways = way.size();
        cntedges += cnt_point_ways;
    }
    return cntedges / 2;
}

int Graph::get_cnt_vertexes() const {
    return graph.size();
}

// степень вершины v (номер вершины) графа
// если такой вершины нет, возникнет исключение
int Graph::get_v_degree(int v) const {
    return (*this)[v].size();
}

unordered_map<int, unordered_map<int, int>> Graph::get_graph() const {
    return graph;
}

bool Graph::get_undirected() const {
    return undirected;
}

unordered_set<tuple<int, int, int>, TupleHash> Graph::get_edges() const {
    unordered_set<tuple<int, int, int>, TupleHash> edges;
    for (auto v1: graph) {
        for (auto v2w: v1.second) {
            tuple<int, int, int> t1 = make_tuple(v1.first, v2w.first, v2w.second);
            tuple<int, int, int> t2 = make_tuple(v2w.first, v1.first, v2w.second);
            if (edges.find(t1) == edges.end() &&
                edges.find(t2) == edges.end()) {
                edges.insert(t1);
            }
        }
    }
    return edges;
}

// вывод графа на консоль
void Graph::print() {
    cout << "Graph " << this << '\n';
    for (auto key: graph) {

        cout << vs[key.first] << ": ";

        for (auto neighbour: key.second) {
            cout << "(" << vs[neighbour.first] << ", " << neighbour.second << "); ";
        }
        cout << '\n';
    }
    cout << '\n';
}


// OPERATORS
// сравнение графов
bool Graph::operator==(const Graph& other) const {
    return this->get_graph() == other.get_graph();
}

// вернуть все смежные вершины и веса
// в виде unordered_map
// если такой вершины не существует, то будет исключение
unordered_map<int, int> Graph::operator[](const int& v) const {
    if (this->get_cnt_vertexes() <= v) {
        // ИСКЛЮЧЕНИЕ
        throw domain_error("No such vertex");
    }
    return this->get_graph()[v];
}
