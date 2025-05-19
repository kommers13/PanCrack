#ifndef GRAPHDRAW_H
#define GRAPHDRAW_H

#include <QVariantMap>

#include <graph.h>


namespace graphdraw {

// реальная ширина холста (в пикселях)
const int RWIDTH = 850;
// реальная высота холста (в пикселях)
const int RHEIGHT = 920;
// радиус вершины (в пикселях)
const int RADIUS = 15;
// отступ от краев холста (в пикселях)
const int MARGIN = 30;
// ширина и высота холста для наших нужд с отступами (в пикселях)
const int WIDTH = RWIDTH - 2 * MARGIN;
const int HEIGHT = RHEIGHT - 2 * MARGIN;
// расстояние чуть больше, чем RADIUS (в пикселях)
const int GAP = RADIUS / 2;

// коэффициент притяжения
// const int Ka = 2 * RADIUS;
// коэффициент отталкивания
// const int Kr = 10 * RADIUS;
// нормальная длина пружины
// const int L = 7 * RADIUS + GAP;
// const int L = sqrt(WIDTH * HEIGHT / 3);

/*
Данная функция создает QVariantMap, на основе которого JS-функция нарисует граф на Canvas
Пример:
    Вход:
        Граф G
        A: (B, 1), (C, 2), (D, 4);
        B: (A, 1), (C, -2), (D, 5);
        C: (B, -2), (A, 2);
        D: (B, 5), (A, 4);

        Массив цветов вершин
        0 0 0 0

    Выход:
        QVariantMap
        vertices: {
            A: (103, 104);
            B: (23, 90);
            C: (560, 400);
            D: (211, 343);
        }
        edges: [
              (A, B, 1),
              (A, C, -2),
              (A, D, 4),
              (B, C, -2),
              (B, D, 5)
        ]
        colors: {
            A: 0
            B: 0
            C: 0
            D: 0
        }
    Возвращается только QVariantMap, сама функция НЕ ВЫЗЫВАЕТ ОТРИСОВКИ ГРАФА
*/


// если эта функция вызывается, то граф УЖЕ СУЩЕСТВУЕТ
QVariantMap draw_graph(const Graph& G,
                       // в большинстве случаев вектора будут передаваться с одним и тем же числом,
                       // так как у каждой вершины один и тот же цвет
                       const vector<int>& v_c     // вектор цветов вершин
                       );


};

#endif // GRAPHDRAW_H
