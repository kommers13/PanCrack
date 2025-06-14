#include <graph.h>



size_t TupleHash::operator()(const tuple<int, int, int>& t) const {
    auto hash_int = hash<int>{};
    size_t h1 = hash_int(get<0>(t));
    size_t h2 = hash_int(get<1>(t));
    size_t h3 = hash_int(get<2>(t));
    return h1 ^ (h2 << 1) ^ (h3 << 2);
}


// построение графа при помощи матрицы смежности
void Graph::create_from_madj(const vector<vector<int>>& madj) {

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
    string nbuffer;
    int n;
    in >> nbuffer;
    n = stoi(nbuffer);  // обработка исключения invalid_argument
    // проверяем количество вершин
    if (n < 0) {
        throw logic_error("Number of vertices is negative or absent!");
    }
    vector<vector<int>> madj(n, vector<int>(n, inf));
    string buffer;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> buffer;
            if (buffer == "i") {
                madj[i][j] = inf;
            }
            else {
                madj[i][j] = stoi(buffer);  // обработка исключения invalid_argument
            }
        }
    }
    create_from_madj(madj);
}

// создание графа из матрицы инцидентности из строкового потока
// это просто прямоугольная матрица из inf и чисел
void Graph::construct_from_string_incm(istream& in) {
    string vbuffer, ebuffer;
    int v = 0, e = 0;
    in >> vbuffer >> ebuffer;
    v = stoi(vbuffer);  // обработка исключения invalid argument
    e = stoi(ebuffer);  // обработка исключения invalid argument
    // если граф имеет отрицательное количество вершин или ребер (ERROR)
    if (v < 0) {
        throw logic_error("Number of vertices is negative!");
    }
    if (e < 0) {
        throw logic_error("Number of edges is negative!");
    }
    // если граф имеет ребер больше, чем может иметь (мультиграф) (ERROR)
    if (e > v * (v - 1) / 2) {
        throw logic_error("Number of edges is more than it can be!");
    }
    // добавляем в граф v вершин
    for (int i = 0; i < v; i++) {
        this->add_vertex();
    }
    // читаем граф из строкового потока в vector<vector<int>>
    vector<vector<int>> incm(v, vector<int>(e));
    string buffer;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < e; j++) {
            in >> buffer;
            if (buffer == "i") {
                incm[i][j] = inf;
            }
            else {
                incm[i][j] = stoi(buffer);  // обработка исключения
            }
        }
    }
    // создание графа по матрице инцидентности
    // если в столбце одно значение или больше 2, то это ОШИБКА
    // идем по ребрам
    for (int i = 0; i < e; i++) {
        vector<int> n_vs;        // соседние вершины (вектор должен иметь размер 2)
        for (int j = 0; j < v; j++) {
            if (incm[j][i] != inf) {
                n_vs.push_back(j);
            }
        }
        if (n_vs.size() > 2) {
            throw logic_error("Multiple edge!");
        }
        if (n_vs.size() == 1) {
            throw logic_error("Edge with one end!");
        }
        if (n_vs.size() != 0) {
            // если веса у вершин неодинаковы
            if (incm[n_vs[0]][i] != incm[n_vs[1]][i]) {
                throw logic_error("Weights of vertices aren`t the same");
            }
            // добавляем ребро
            this->add_edge(n_vs[0], n_vs[1], incm[n_vs[0]][i]);
        }
    }
}

// создание графа из списков смежности из строкового потока
void Graph::construct_from_string_ladj(istream& in) {
    vector<string> prs;    // обработанная строка, разбитая на токены
    string buffer;
    while (in >> buffer) {
        // проходимся по buffer и закидываем в prs только то, что подходит
        string nbuffer = "";
        buffer += ',';
        for (int i = 0; i < buffer.size(); i++) {
            char c = buffer[i];
            if (c == '-' ||
                ('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z')
                ) {
                nbuffer += c;
            }
            else {
                if (nbuffer.size() > 0) {
                    prs.push_back(nbuffer);
                    nbuffer = "";
                }
                if (c == ';') {
                    prs.push_back(";");
                }
            }
        }
    }
    // for (auto e: prs) {
    //     cout << e << ' ';
    // }
    // cout << '\n';

    // теперь у нас есть разбитая на токены строка, можно начать собирать вектор
    int cnt = 1; // счетчик чисел в списке смежности
    int current_vertex, add_vertex, weight; // добавляемая вершина и вес
    unordered_map<char, int> name_ind;  // имя вершины отображается на ее индекс
    for (int i = 0; i < prs.size(); i++) {
        string token = prs[i];
        if (token[0] == ';') {
            cnt = 1;
            continue;
        }
        if (cnt == 1) {
            // проверяем, что токен состоит из одного символа
            if (token.size() > 1) {
                throw domain_error("Name of vertex must be a one character");
            }
            // добавляем вершину с именем token[0], если такой еще не существует
            if (name_ind.find(token[0]) == name_ind.end()) {
                this->add_vertex(token[0]);
                current_vertex = vs.size() - 1;
                name_ind[token[0]] = current_vertex;
            }
            else { // если вершина уже существовала, то мы просто берем ее индекс
                current_vertex = name_ind[token[0]];
            }
        }
        else if (cnt % 2 == 0) {    // если порядок четный, то это зависимая вершина
            // проверяем, что токен состоит из одного символа
            if (token.size() > 1) {
                throw domain_error("Name of vertex must be a character");
            }
            // добавляем вершину с именем token[0], если такой еще не существует
            if (name_ind.find(token[0]) == name_ind.end()) {
                this->add_vertex(token[0]);
                add_vertex = vs.size() - 1;
                name_ind[token[0]] = add_vertex;
            }
            else { // если вершина уже существовала, то мы просто берем ее индекс
                add_vertex = name_ind[token[0]];
            }
        }
        else {  // если порядок нечетный, то это вес
            weight = stoi(token);   // выбрасывается исключение, если нельзя преобразовать к числу
            // добавляем ребро вручную, так как add_edge добавляет ребро как
            // для неориентированного графа
            if (current_vertex == add_vertex) { // ПЕТЛЯ в графе
                throw domain_error("Loops can`t be in unoriented graph!");
            }
            this->graph[current_vertex][add_vertex] = weight;
        }
        // увеличиваем счетчик чисел в списке смежности
        ++cnt;
    }
}


// проверка, является ли граф неориентированным
// он проверяет атрбиут graph на то, чтобы он был НЕОРИЕНТИРОВАННЫМ
bool Graph::is_undirected() {
    for (const auto [v, neighbours]: graph) {
        for (const auto [u, w]: neighbours) {
            // если из v в u вес не равен из u в v, то граф ориентированный
            // BUG с 0
            if (graph[v][u] != graph[u][v]) {
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

    undirected = is_undirected();

    // DEBUG
    if (!undirected) {
        throw domain_error("This is not undirected graph!");
    }
    // END DEBUG (remove on release)
}


// построение графа при помощи строкового потока
Graph::Graph(const int& type, istream& in) : graph() {
    switch (type) {
        case 0: {
            construct_from_string_madj(in);
            break;
        }
        case 1: {
            construct_from_string_incm(in);
            break;
        }
        case 2: {
            construct_from_string_ladj(in);
            break;
        }
    }
    undirected = is_undirected();

    // DEBUG
    if (!undirected) {
        throw domain_error("This is not undirected graph!");
    }
    // END DEBUG (remove on release)
}

// добавление вершины
// letter имеет значение по умолчанию равное ' '
void Graph::add_vertex(const char& letter) {
    graph[vs.size()] = {};
    if (letter == ' ') {
        if (vs.size() == 0) {
            vs.push_back('A');
        }
        else {
            vs.push_back((char)(vs[vs.size() - 1] + 1));
        }
    }
    else {
        vs.push_back(letter);
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



// GETTERS
int Graph::get_cnt_edges() const {
    int cntedges = 0;
    for(auto [point, way] : graph){
        int cnt_point_ways = way.size();
        cntedges += cnt_point_ways;
    }
    return cntedges / 2;
}

size_t Graph::get_cnt_vertexes() const {
    return graph.size();
}

// степень вершины v (номер вершины) графа
// если такой вершины нет, возникнет исключение
int Graph::get_v_degree(int v) const {
    return (*this)[v].size();
}

// граф в виде строки
// по умолчанию nl_sign равен "\n"
string Graph::get_str_graph(const string& nl_sign) const {
    string str_graph = "";
    for (auto key: graph) {

        str_graph += vs[key.first];
        str_graph += ": ";

        for (auto neighbour: key.second) {
            str_graph += "(";
            str_graph += vs[neighbour.first];
            str_graph += ", ";
            str_graph += to_string(neighbour.second);
            str_graph += "); ";
        }
        str_graph += nl_sign;
    }
    return str_graph;
}

unordered_map<int, unordered_map<int, int>> Graph::get_graph() const {
    return graph;
}

// имена вершин графа
vector<char> Graph::get_vs_name() const {
    return vs;
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
    cout << this->get_str_graph() << '\n';
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


vector<int> Graph::get_sorted_neighbors(int vertex) const {
    vector<int> neighbors;
    for (const auto& pair : graph.at(vertex)) {
        neighbors.push_back(pair.first);
    }
    sort(neighbors.begin(), neighbors.end());
    return neighbors;
}

bool Graph::has_vertex(int vertex) const {
    return graph.find(vertex) != graph.end();
}
