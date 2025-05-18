#include "include/graphdraw.h"

using namespace graphdraw;


pair<int, int> tovec(const pair<int, int>& p1,
                     const pair<int, int>& p2) {
    return make_pair(p2.first - p1.first, p2.second - p1.second);
}

long long int len_sq(const pair<int, int>& v) {
    return v.first * v.first + v.second * v.second;
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
    qDebug() << "len_sq(v) " << len_sq(v);
    qDebug() << ( ( prod / len_sq(v) ) >= ( (RADIUS + GAP) * (RADIUS + GAP) ) );
    return ( prod / len_sq(v) ) >= ( (RADIUS + GAP) * (RADIUS + GAP) );
}


unordered_map<char, pair<int, int>> gen_vertices_coords(const Graph& G) {

    auto vsn = G.get_vs_name();
    auto graph = G.get_graph();


    // определим позиции вершин
    unordered_map<char, pair<int, int>> vertices_coords;    // имя вершины, пара координат
    for (auto v1_neighbours: graph) {
        char v1 = vsn[v1_neighbours.first];                 // имя очередной добавляемой вершины
        int x = rand() % (WIDTH - MARGIN + 1) + MARGIN;     // генерация случайной координаты по оси абсцисс
        int y = rand() % (HEIGHT - MARGIN + 1) + MARGIN;    // генерации случайной координаты по оси ординат
        qDebug() << "x, y: " << x << ' ' << y;
        int attempts = 10;
        bool isExit = false;    // на выход из внешнего цикла [for (auto cv_cx_cy: vertices_coords)]
        while (attempts-->0) {

            // qDebug() << "CHOICE";
            // строим прямые от добавляемой вершины ко всем остальным
            // когда построили прямую, то мы должны проверить, что все оставшиеся вершины,
            // которые не задействованы в прямой, должны находится от нее на определенном расстоянии

            // перебираем все вершины, с которыми будет построена прямая из точки (x, y)
            for (auto cv_cx_cy: vertices_coords) {
                // char cv = cv_cx_cy.first;
                int cx = cv_cx_cy.second.first;
                int cy = cv_cx_cy.second.second;

                // проверяем оставшиеся вершины, чтобы они находились на нужном расстоянии
                // от этой вершины
                for (auto c1v_c1x_c1y: vertices_coords) {
                    // char c1v = c1v_c1x_c1y.first;
                    int c1x = c1v_c1x_c1y.second.first;
                    int c1y = c1v_c1x_c1y.second.second;

                    // // если такая прямая уже строилась, то пропускаем эту итерацию
                    // if (checked_vertices[cv][c1v] || checked_vertices[c1v][cv]) {
                    //     continue;
                    // }

                    if (cx != c1x || cy != c1y) { // когда вершины разные, тогда только можно строить прямую
                        // если пересечение есть
                        if (!check_overlap(make_pair(x, y),
                                           make_pair(cx, cy),
                                           make_pair(c1x, c1y)
                                           )
                            ) {
                            isExit = true;  // выходим из внешнего цикла и начинаем все по новой
                            break;
                        }
                        // checked_vertices[cv][c1v] = true;
                        // checked_vertices[c1v][cv] = true;
                        // если она не прошла, то нужно по новому задать координаты вставляемой вершины
                        // координаты x и y
                        // иначе, добавить вершину с ее координатами и перейти к следующей вершине
                    }
                }
                if (isExit) {
                    // выходим из внешнего цикла, но уже с новыми координатами
                    x = rand() % (WIDTH - MARGIN + 1) + MARGIN;     // генерация случайной координаты по оси абсцисс
                    y = rand() % (HEIGHT - MARGIN + 1) + MARGIN;    // генерации случайной координаты по оси ординат
                    // qDebug() << "x, y: " << x << ' ' << y;
                    // checked_vertices = {};
                    break;
                }
            }

            // СЕЙЧАС МЫ ДЕЙСТВУЕМ НА УДАЧУ, ПОТОМУ ЧТО ВТОРАЯ ВЕРШИНА БУДЕТ ДОБАВЛЯТЬСЯ КАК ПОПАЛО
            // мы ни разу не захотели выйти из цикла for, т. е. не было пересечений
            if (!isExit) {
                // поэтому добавляем вершину с ее координатами и выходим из цикла while
                vertices_coords[v1] = make_pair(x, y);
                // qDebug() << "COORDS and vertex: " << v1 << ' ' << x << " " << y;
                // qDebug() << "END CHOICE";
                break;
            }
            else {  // если мы вышли из цикла (т. е. пересечение было),
                    // то должны обновить isExit обратно на false
                isExit = false;
            }
        }
        // если не получилось, то запихиваем как есть
        if (attempts == -1) {
            qDebug() << "WTF";
            vertices_coords[v1] = make_pair(x, y);
        }
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
