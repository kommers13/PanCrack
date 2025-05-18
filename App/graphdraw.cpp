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

// единичный вектор по двум точкам
template<typename T>
pair<T, T> tosvec(const pair<T, T>& p1,
                  const pair<T, T>& p2) {
    pair<T, T> vec = tovec<T>(p1, p2);
    return make_pair((p2.first - p1.first) / len<T>(vec), (p2.second - p1.second) / len<T>(vec));
}

template<typename T>
pair<T, T> add(const pair<T, T>& v1,
               const pair<T, T>& v2) {
    return make_pair(v1.first + v2.first, v1.second + v2.second);
}

template<typename T>
pair<T, T> multiply(const T& c,
                    const pair<T, T>& v) {
    return make_pair(c * v.first, c * v.second);
}

template<typename T>
pair<T, T> negative(const pair<T, T>& v) {
    return multiply<T>(-1, v);
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
unordered_map<int, pair<double, double>> Eades_algorithm(
                                                    const Graph& G,     // граф
                                                    unordered_map<int, pair<double, double>> vertices_coords,  // координаты вершин
                                                    const double& temp      // температура
                                                    ) {


    // НЕ ЗАБУДЬ, ЧТО ТЫ ЗАБЫЛ УЧЕСТЬ, ЧТО ТВОИ ВЕРШИНЫ МОГУТ ВЫЙТИ ЗА ПРЕДЕЛЫ CANVAS-А

    // нужно помнить, чтобы вершины не вышли за пределы Canvas-а
    auto graph = G.get_graph();

    // проходимся по каждой вершине, и вычисляем силу
    for (auto v_x_y: vertices_coords) {
        int v = v_x_y.first;
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;

        pair<double, double> F_vec = make_pair(0, 0);       // Общая воздействующая сила

        // проходимся по всем остальным
        for (auto v1_x1_y1: vertices_coords) {
            int v1 = v1_x1_y1.first;
            double x1 = v1_x1_y1.second.first;
            double y1 = v1_x1_y1.second.second;

            // если вершины равны, то пропускаем итерацию
            if (v1 == v) {
                continue;
            }

            // узнаем расстояние между точками
            pair<double, double> vec_spring = tovec<double>(make_pair(x, y), make_pair(x1, y1));
            double dist = len(vec_spring);
            qDebug() << "========================================";
            qDebug() << "v, v1: " << v << ' ' << v1;
            qDebug() << "dist(v, v1): " << dist;

            // узнаем, есть ли пружина между вершинами
            // если есть
            if (graph[v].find(v1) != graph[v].end()) {
                double F_spring = f_attr(dist);     // скалярная сила пружины
                qDebug() << "F_spring: " << F_spring;
                // вычисляем координаты вектора силы пружины
                double k = dist / F_spring;         // узнаем коэффициент пропорциональность
                qDebug() << "k spring: " << k;
                pair<double, double> vec_attr = make_pair(x / k, y / k);  // узнаем вектор силы пружины
                qDebug() << "vec_attr(v, v1): " << vec_attr;
                F_vec = add<double>(F_vec, vec_attr);
            }

            // независимо от наличия пружины прибавляем вектор силы отталкивания
            double F_rep = f_rep(dist);     // скалярная сила отталкивания
            qDebug() << "F_rep: " << F_rep;
            // вычисляем координаты
            double k = dist / F_rep;        // коэффициент пропорциональности
            qDebug() << "k rep: " << k;
            pair<double, double> vec_rep = make_pair(-x / k, -y / k);     // вектор отталкивания идет в противоположную сторону
            qDebug() << "vec_rep(v, v1): " << vec_rep;
            F_vec = add<double>(F_vec, vec_rep);
            qDebug() << "F_vec: " << F_vec;
        }

        // обновляем позицию вершины
        // прибавляем к вектор-точке текущей вершины результирующую силу с температурой
        pair<double, double> vec = add<double>(make_pair(x, y), multiply(temp, F_vec));     // вектор-точка текущей вершины
        vertices_coords[v] = vec;
    }
    return vertices_coords;
}


unordered_map<int, pair<double, double>> gen_vertices_coords(const Graph& G) {

    auto vsn = G.get_vs_name();
    auto graph = G.get_graph();


    // определим позиции вершин
    // выставляем начальные условия
    unordered_map<int, pair<double, double>> vertices_coords; // имя вершины, пара координат

    // выставим вершины случайно внутри области меньшей, чем Canvas
    for (auto v1_neighbours: graph) {
        int v1 = v1_neighbours.first;
        // ТОЧКИ МОГУТ НАСЛОИТЬСЯ, ЧТО ПРИВЕДЕТ К ДЕЛЕНИЮ НА НОЛЬ
        double x = rand() % (WIDTH - 2 * 4 * MARGIN + 1) + 4 * MARGIN;      // [4 * MARGIN; WIDTH - 4 * MARGIN] - случайное число
        double y = rand() % (HEIGHT - 2 * 4 * MARGIN + 1) + 4 * MARGIN;
        // qDebug() << RAND_MAX;
        // qDebug() << x << ' ' << y;
        // qDebug() << "WIDTH, HEIGHT, MARGIN: " << WIDTH - 4 * MARGIN << ' ' << HEIGHT - 4 * MARGIN << ' ' << 4 * MARGIN;
        vertices_coords[v1] = make_pair(x, y);
    }

    // температура
    double temp = 20;
    // количество итераций
    int cnt_iters = 1;
    // шаг температуры
    double step_temp = temp / cnt_iters;
    while (cnt_iters-->0) {

        vertices_coords = Eades_algorithm(G, vertices_coords, temp);

        temp -= step_temp;
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
    unordered_map<int, pair<double, double>> vertices_coords = gen_vertices_coords(G);
    // перенесем данные из vertices_coords в vertices
    for (auto v_x_y: vertices_coords) {
        char v = vsn[v_x_y.first];
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;
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
