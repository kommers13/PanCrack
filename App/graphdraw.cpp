#include "include/graphdraw.h"

using namespace graphdraw;

template<typename T>
pair<T, T> tovec(const pair<T, T>& p1,
                 const pair<T, T>& p2) {
    return make_pair(p2.first - p1.first, p2.second - p1.second);
}

template<typename T>
double len(const pair<T, T>& v) {
    return sqrt(v.first * v.first + v.second * v.second);
}

template<typename T>
pair<T, T> add(const pair<T, T>& v1,
               const pair<T, T>& v2) {
    return make_pair(v1.first + v2.first, v1.second + v2.second);
}

template<typename T>
pair<T, T> negative(const pair<T, T>& v) {
    return make_pair(-v.first, -v.second);
}

long long int vprod(const pair<int, int>& v1,
                    const pair<int, int>& v2) {
    long long int x1, y1, x2, y2;
    x1 = v1.first; y1 = v1.second;
    x2 = v2.first; y2 = v2.second;
    return x1 * y2 - x2 * y1;
}

// проверяет, чтобы точка p была на расстоянии не менее RADIUS + GAP от вектора,
// построенного на точках p1 и p2
// true - пересечений нет
// false - пересечение есть
bool check_overlap(const pair<int, int>& p1,
                   const pair<int, int>& p2,
                   const pair<int, int>& p) {
    // вектор по точкам p1 и p2
    // проверяем, чтобы точка p была на расстоянии RADIUS + GAP от вектора
    // создаем вектор по p1 и p2
    pair<int, int> v = tovec(p1, p2);
    // создаем вектор по p1 и p
    pair<int, int> v0 = tovec(p1, p);
    // вычисляем векторное произведение v и v0
    long long int prod = vprod(v, v0);
    prod *= prod;   // делаем квадрат
    qDebug() << "len(v) " << len(v);
    qDebug() << ( ( prod / len(v) ) >= ( (RADIUS + GAP) * (RADIUS + GAP) ) );
    return ( prod / len(v) ) >= ( (RADIUS + GAP) * (RADIUS + GAP) );
}


// сила отталкивания
double f_rep(const double& d) {
    return Kr / (d * d);
}

// сила притяжения
double f_attr(const double& d) {
    return Ka * log2(d);
}

/*
Суть алгоритма: задается начальная позиция вершин и сам граф. Одна итерация алгоритма - это вычисление
для каждой вершины результирующей силы, действующей на нее со стороны других вершин. В этом алгоритме ребра
представляются пружинами, которые могут сжиматься и разжиматься, а вершины - заряженными частицами.
По расстоянию между вершинами мы можем узнать силу отталкивания, а если между ними еще есть и ребро, то
сможем узнать еще и силу притяжения для пружины (силу сжатия). Сложив все эти вектора сил, действующие на вершину,
мы узнаем результирующий вектор силы, на который и нужно сдвинуть эту вершину, помноженный на коэффициент
температуры.

*/
// одна итерация выполнения алгоритма
unordered_map<char, pair<double, double>> Eades_algorithm(const Graph& G,     // граф
                                                    const unordered_map<char, pair<double, double>> vertices_coords,  // координаты вершин
                                                    const double& temp      // температура
                                                    ) {
    // нужно помнить, чтобы вершины не вышли за пределы Canvas-а
    auto graph = G.get_graph();

    // проходимся по каждой вершине, и вычисляем силу
    for (auto v_x_y: vertices_coords) {
        char v = v_x_y.first;
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;

        pair<double, double> F_vec = make_pair(0, 0);       // Общая воздействующая сила

        // проходимся по всем остальным
        for (auto v1_x1_y1: vertices_coords) {
            char v1 = v1_x1_y1.first;
            double x1 = v1_x1_y1.second.first;
            double y1 = v1_x1_y1.second.second;

            // если вершины равны, то пропускаем итерацию
            if (v1 == v) {
                continue;
            }

            // узнаем расстояние между точками
            pair<double, double> vec_spring = tovec(make_pair(x, y), make_pair(x1, y1));
            double dist = len(vec_spring);

            // узнаем, есть ли пружина между вершинами
            // если есть
            if (graph[v].find(v1) != graph[v].end()) {
                double F_spring = f_attr(dist);     // скалярная сила пружины
                // вычислим координаты вектора силы пружины
                double k = dist / F_spring;         // узнаем коэффициент пропорциональность
                pair<int, int> vec_attr = make_pair(x / k, y / k);  // узнаем вектор силы пружины
                F_vec = add<double>(F_vec, vec_attr);
            }

            // независимо от наличия пружины прибавляем вектор силы отталкивания
            double F_rep = f_rep(dist);     // скалярная сила отталкивания
            // вычисляем координаты
        }
    }
}


unordered_map<char, pair<int, int>> gen_vertices_coords(const Graph& G) {

    auto vsn = G.get_vs_name();
    auto graph = G.get_graph();


    // определим позиции вершин
    // температура
    double temp = 20;
    // выставляем начальные условия
    unordered_map<char, pair<int, int>> vertices_coords; // имя вершины, пара координат

    // выставим вершины случайно внутри области меньшей, чем Canvas
    for (auto v1_neighbours: graph) {
        char v1 = vsn[v1_neighbours.first];
        int x = rand() % (WIDTH - 4 * MARGIN + 1) + 4 * MARGIN;
        int y = rand() % (HEIGHT - 4 * MARGIN + 1) + 4 * MARGIN;
        vertices_coords[v1] = make_pair(x, y);
    }


    return vertices_coords;
}



QVariantMap graphdraw::draw_graph(const Graph& G, const vector<int>& v_c) {
    QVariantMap graph_coords;   // сюда мы будем складывать остальные QVariant<Structure>
    QVariantMap vertices;
    QVariantList edges;
    QVariantMap colors;


    auto graph = G.get_graph();
    auto vsn = G.get_vs_name();


    // перенесем цвета из v_c в colors
    for (auto v1_neighbours: graph) {
        int v1 = v1_neighbours.first;
        colors.insert(QString(vsn[v1]), QVariant::fromValue(v_c[v1]));
    }

    // определим позицию вершин
    unordered_map<char, pair<int, int>> vertices_coords = gen_vertices_coords(G);
    // перенесем данные из vertices_coords в vertices
    for (auto v_x_y: vertices_coords) {
        char v = v_x_y.first;
        int x = v_x_y.second.first;
        int y = v_x_y.second.second;
        QVariantList coord;
        coord << x << y;
        vertices.insert(QString(v), coord);
    }


    // заполним edges
    unordered_map<char, unordered_map<char, bool>> checked_edges;
    for (auto v1_neighbours: graph) {
        for (auto v2_w: v1_neighbours.second) {
            char v1 = vsn[v1_neighbours.first];
            char v2 = vsn[v2_w.first];
            int w = v2_w.second;
            // если такое ребро уже было, то пропускаем его
            if (checked_edges[v1][v2] || checked_edges[v1][v2]) {
                continue;
            }
            // добавляем элементы в ребро
            QVariantList edge;
            edge << QString(v1) << QString(v2) << w;
            edges << QVariant(edge);
            // отмечаем, что мы уже проверили это ребро
            checked_edges[v1][v2] = true;
            checked_edges[v2][v1] = true;
        }
    }

    graph_coords.insert(QString("vertices"), vertices);
    graph_coords.insert(QString("edges"), edges);
    graph_coords.insert(QString("colors"), colors);

    return graph_coords;
}
