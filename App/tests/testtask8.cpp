#include "include/testtask8.h"
#include "task8.h"
#include <graph.h>
#include <QTest>
#include <QDebug>

void TestTask8::test_dijkstra() {
    // Тест 1: Простой граф с 3 вершинами
    {
        std::string in = "3\ninf 5 10\n5 inf 3\n10 3 inf";
        std::stringstream ss(in);
        Graph g(0, ss);

        qDebug() << "\n=== Тест 1: Простой треугольный граф ===";

        // 1 → 2 (прямое соединение)
        auto [dist1, path1] = task8::find_shortest_path(g, 1, 2);
        QVERIFY(dist1 == 5);
        QCOMPARE(path1, std::vector<int>({1, 2}));
        //qDebug() << "1 → 2: Ожидается расстояние 5, путь [1,2]";
        qDebug() << "Расстояние:" << dist1 << "путь:" << path1;

        // 1 → 3 (через вершину 2)
        auto [dist2, path2] = task8::find_shortest_path(g, 1, 3);
        QVERIFY(dist2 == 8);
        QCOMPARE(path2, std::vector<int>({1, 2, 3}));
        //qDebug() << "1 → 3: Ожидается расстояние 8, путь [1,2,3]";
        qDebug() << "Расстояние:" << dist2 << "путь:" << path2;
    }

    // Тест 2: Граф без путей
    {
        std::string in = "3\ninf inf inf\ninf inf inf\ninf inf inf";
        std::stringstream ss(in);
        Graph g(0, ss);

        qDebug() << "\n=== Тест 2: Граф без соединений ===";

        auto [dist, path] = task8::find_shortest_path(g, 1, 3);
        QVERIFY(dist == task8::inf);
        QVERIFY(path.empty());
        //qDebug() << "1 → 3: Ожидается отсутствие пути";
        qDebug() << "Расстояние:" << dist << "путь:" << path;//(dist == task8::inf ? "INF" : QString::number(dist)) << "путь пуст";
    }

    // Тест 3: Сложный граф с 5 вершинами
    {
        std::string in = "5\ninf 10 inf 30 100\n10 inf 50 inf inf\n"
                         "inf 50 inf 20 10\n30 inf 20 inf 60\n100 inf 10 60 inf";
        std::stringstream ss(in);
        Graph g(0, ss);

        qDebug() << "\n=== Тест 3: Сложный граф с 5 вершинами ===";

        // 1 → 5 (через 4 → 3 → 5)
        auto [dist, path] = task8::find_shortest_path(g, 1, 5);
        QVERIFY(dist == 60);
        QCOMPARE(path, std::vector<int>({1, 4, 3, 5}));
        //qDebug() << "1 → 5: Ожидается расстояние 60, путь [1,4,3,5]";
        qDebug() << "Расстояние" << dist << "путь:" << path;

        // 2 → 4 (через 1 → 4)
        auto [dist2, path2] = task8::find_shortest_path(g, 2, 4);
        QVERIFY(dist2 == 40);
        QCOMPARE(path2, std::vector<int>({2, 1, 4}));
        //qDebug() << "2 → 4: Ожидается расстояние 40, путь [2,1,4]";
        qDebug() << "Расстояние" << dist2 << "путь:" << path2;
    }

    // Тест 4: Невалидные вершины
    {
        std::string in = "3\ninf 1 1\n1 inf inf\n1 inf inf";
        std::stringstream ss(in);
        Graph g(0, ss);

        qDebug() << "\n=== Тест 4: Проверка невалидных вершин ===";

        // Слишком большие номера
        auto [dist1, path1] = task8::find_shortest_path(g, 1, 5);
        QVERIFY(dist1 == task8::inf);
        QVERIFY(path1.empty());
        //qDebug() << "1 → 5: Ожидается ошибка (несуществующая вершина)";
        qDebug() << "Расстояние:" << dist1 << "путь:" << path1;

        // Отрицательные номера
        auto [dist2, path2] = task8::find_shortest_path(g, -1, 2);
        QVERIFY(dist2 == task8::inf);
        QVERIFY(path2.empty());
        //qDebug() << "-1 → 2: Ожидается ошибка (невалидная вершина)";
        qDebug() << "Расстояние:" << dist1 << "путь:" << path1;
    }
}
