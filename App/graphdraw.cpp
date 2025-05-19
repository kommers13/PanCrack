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


// вектор отталкивания
pair<double, double> v_rep(const pair<double, double>& sv,  // единичный векор
                           const double& d,
                           const double& L) {
    // вектор отталкивания направлен в противоположную сторону от направления вектора пружины
    return multiply(-(L * L) / d, sv);      // ДЛЯ ФРЮХТЕРМАНА-РЕЙНГОЛЬДА
    // return multiply(-Kr / (d * d), sv);  // ДЛЯ ИДЕСА
}

// вектор притяжения
pair<double, double> v_attr(const pair<double, double>& sv, // единичный вектор
                            const double& d,
                            const double& L) {
    return multiply((d * d) / L, sv);   // ДЛЯ ФРЮХТЕРМАНА-РЕЙНГОЛЬДА
    // если расстояние больше длины пружины, то это будет стягивание
    // если расстояние меньше длины пружмины, то это будет растяжение
    // return multiply(Ka * log(d / L), sv);   // ДЛЯ ИДЕСА
}




unordered_map<int, pair<double, double>> FR_algorithm(
                                                    const Graph& G,     // граф
                                                    unordered_map<int, pair<double, double>> vertices_coords,  // координаты вершин
                                                    const double& temp
                                                    ) {
    auto graph = G.get_graph();
    const double L = sqrt(HEIGHT * WIDTH) / graph.size();
    qDebug() << "L: " << L;


    qDebug() << "vertices_coords AT THE BEGINNING OF ITERATION";
    for (auto v_x_y: vertices_coords) {
        qDebug() << "v_x_y: " << v_x_y;
    }

    // массив сдвигов вершин, после мы их преобразуем в нормальные координаты
    unordered_map<int, pair<double, double>> displacements;

    qDebug() << "===========================";
    qDebug() << "Repulsion of vertices";
    // сначала мы расчитываем силы отталкиваний у ВСЕХ ВЕРШИН
    // и обновим их координаты соответствующе
    for (auto v_x_y: vertices_coords) {
        int v = v_x_y.first;
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;

        auto F_c = make_pair(0, 0);     // равнодействующая

        for (auto v1_x1_y1: vertices_coords) {
            int v1 = v1_x1_y1.first;
            double x1 = v1_x1_y1.second.first;
            double y1 = v1_x1_y1.second.second;

            if (v1 == v) {
                continue;
            }

            double dist = len<double>(tovec(make_pair(x, y), make_pair(x1, y1)));
            auto vecs = tosvec(make_pair(x, y), make_pair(x1, y1));

            auto vec_rep = v_rep(vecs, dist, L);        // вектор отталкивания у этой вершины
            qDebug() << "v, v1: " << v << ' ' << v1;
            // qDebug() << "v(x, y), v1(x, y): " << make_pair(x, y) << ' ' << make_pair(x1, y1);
            qDebug() << "dist: " << dist;
            qDebug() << "vec_rep: " << vec_rep;
            F_c = add<double>(F_c, vec_rep);
        }

        qDebug() << "F_c: " << F_c;

        // записываем в словарь смещений для вершин смещение данной вершины
        displacements[v] = F_c;
    }


    qDebug() << "================================";
    qDebug() << "Springs";
    // теперь рассчитываем силы притяжения у смежных вершин, чтобы они далеко не улетали
    for (auto v_x_y: vertices_coords) {
        int v = v_x_y.first;
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;

        for (auto v1_x1_y1: vertices_coords) {
            int v1 = v1_x1_y1.first;
            double x1 = v1_x1_y1.second.first;
            double y1 = v1_x1_y1.second.second;

            // вершины смежные
            // Т. е. есть пружина
            // Тогда рассчитываем силу притяжения между ними
            // вектор (v, v1), т. е. стрелочка от v к v1
            if (graph[v].find(v1) != graph[v].end()) {
                // расстояние между вершинами
                double dist = len<double>(tovec(make_pair(x, y), make_pair(x1, y1)));
                // единичный вектор (v, v1)
                auto v_v1_s = tosvec(make_pair(x, y), make_pair(x1, y1));   // единичный вектор
                // единичый вектор (v1, v)
                auto v1_v_s = negative(v_v1_s);   // единичный вектор

                // сдвигаем вершины ребра на встречу друг другу
                vertices_coords[v] = add<double>(make_pair(x, y), multiply(temp, v_attr(v_v1_s, dist, L)));
                vertices_coords[v1] = add<double>(make_pair(x1, y1), multiply(temp, v_attr(v1_v_s, dist, L)));
                qDebug() << "v, v1: " << v << ' ' << v1;
                // qDebug() << "v(x, y), v1(x, y): " << make_pair(x, y) << ' ' << make_pair(x1, y1);
                qDebug() << "dist: " << dist;
                qDebug() << "v_attr(v, v1): " << v_attr(v_v1_s, dist, L);
                qDebug() << "v_attr(v1, v): " << v_attr(v1_v_s, dist, L);
            }
        }
    }
    // проверяем, чтобы вершины не вылезли за пределы Canvas-а
    // ...

    return vertices_coords;
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
    // нужно сделать так, что со всех четырех сторон Canvas-а на частицы тоже действует сила
    // это нужно для того, чтобы частицы не выходили за пределы

    // нужно помнить, чтобы вершины не вышли за пределы Canvas-а
    auto graph = G.get_graph();
    // const double L = sqrt(WIDTH * HEIGHT) / graph.size();
    const double L = 25 * RADIUS;

    qDebug() << "vertices_coords AT THE BEGINNING OF ITERATION";
    for (auto v_x_y: vertices_coords) {
        qDebug() << "v_x_y: " << v_x_y;
    }

    // проходимся по каждой вершине, и вычисляем силу
    for (auto v_x_y: vertices_coords) {
        int v = v_x_y.first;
        double x = v_x_y.second.first;
        double y = v_x_y.second.second;

        pair<double, double> F_vec = make_pair(0, 0);       // равнодействующая сила

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
            // единичный вектор от (x, y) к (x1, y1), где равнодействующая сила вычисляется для точки
            // (x, y), поэтому вектор силы притяжения действует по направлению вектора, а отталкивания -
            // - в противоложном
            pair<double, double> vec_sspring = tosvec<double>(make_pair(x, y), make_pair(x1, y1));
            double dist = len(vec_spring);
            qDebug() << "========================================";
            qDebug() << "v, v1: " << v << ' ' << v1;
            qDebug() << "dist(v, v1): " << dist;

            // узнаем, есть ли пружина между вершинами
            // если есть
            if (graph[v].find(v1) != graph[v].end()) {
                pair<double, double> vec_attr = v_attr(vec_sspring, dist, L);     // вектор силы пружины
                qDebug() << "vec_attr(v, v1): " << vec_attr;
                F_vec = add<double>(F_vec, vec_attr);
                qDebug() << "F_vec: " << F_vec;
            }
            // если нет пружины между ребрами, значит между ними есть сила отталкивания (ДЛЯ ИДЕСА)
            else {
                pair<double, double> vec_rep = v_rep(vec_sspring, dist, L);     // вектор отталкивания идет в противоположную сторону
                qDebug() << "vec_rep(v, v1): " << vec_rep;
                F_vec = add<double>(F_vec, vec_rep);
                qDebug() << "F_vec: " << F_vec;
            }
            // // независимо от наличия пружины прибавляем вектор силы отталкивания (ДЛЯ ФРЮХТЕРМАНА-РЕЙНГОЛЬДА)
            // pair<double, double> vec_rep = v_rep(vec_sspring, dist);     // вектор отталкивания идет в противоположную сторону
            // qDebug() << "vec_rep(v, v1): " << vec_rep;
            // F_vec = add<double>(F_vec, vec_rep);
            // qDebug() << "F_vec: " << F_vec;
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
    double temp = 1;
    // количество итераций
    int cnt_iters = 1;
    // шаг температуры
    double step_temp = temp / cnt_iters;
    while (cnt_iters-->0) {

        vertices_coords = FR_algorithm(G, vertices_coords, temp);

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
