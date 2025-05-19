#include "include/testtask2.h"
#include "task2.h"
#include <vector>
#include <sstream>
#include <unordered_set>
#include <random>

void TestTask2::test_DFS() {
    // Тест 1: Граф из 3 вершин (1-based)
    {
        qDebug() << "тест 1";
        std::string in = "3\ninf 1 1\n1 inf inf\n1 inf inf";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto result = task2::DFS(g, 1);

        // Ожидаемый результат: 1 -> 3 -> 2 или 1 -> 2 -> 3
        bool valid1 = (result == std::vector<int>{1, 3, 2});
        bool valid2 = (result == std::vector<int>{1, 2, 3});
        if (!valid1 && !valid2) {
            qDebug() << "Неожиданный DFS: " << result;
        }
        //qDebug() << result;
        //qDebug() << valid1;
        //qDebug() << valid2;
        QVERIFY(valid1 || valid2);
    }

    // Тест 2: Несвязный граф
    {
        qDebug() << "тест 2";
        std::string in = "4\ninf 1 inf inf\n1 inf inf inf\ninf inf inf 1\ninf inf 1 inf";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto result = task2::DFS(g, 1);

        //Ожидаемый результат: только вершины 1 и 2 в любом порядке
        bool valid1 = (result == std::vector<int>{1, 2});
        bool valid2 = (result == std::vector<int>{2, 1});
        if (!valid1 && !valid2) {
            qDebug() << "Unexpected DFS result:" << result;
        }
        //qDebug() << result;
        QVERIFY(valid1 || valid2);
    }
    // Тест 3: Граф из 10 вершин (связный)
    {
        qDebug() << "тест 3: Граф из 10 вершин";
        std::string in =
            "10\n"
            "inf 1 1 inf inf inf inf inf inf inf\n"
            "1 inf 1 1 inf inf inf inf inf inf\n"
            "1 1 inf inf 1 inf inf inf inf inf\n"
            "inf 1 inf inf 1 1 inf inf inf inf\n"
            "inf inf 1 1 inf 1 1 inf inf inf\n"
            "inf inf inf 1 1 inf inf 1 inf inf\n"
            "inf inf inf inf 1 inf inf inf 1 1\n"
            "inf inf inf inf inf 1 inf inf 1 inf\n"
            "inf inf inf inf inf inf 1 1 inf 1\n"
            "inf inf inf inf inf inf 1 inf 1 inf";

        std::stringstream ss(in);
        Graph g(0, ss);
        int start_vertex = 5; // Начинаем с вершины 5 (1-based)
        auto result = task2::DFS(g, start_vertex);

        // Проверяем базовые условия
        QVERIFY(!result.empty());
        QCOMPARE(result[0], start_vertex); // Первая вершина должна быть стартовой

        // Проверяем, что все вершины уникальны
        std::unordered_set<int> unique_vertices(result.begin(), result.end());
        QCOMPARE(unique_vertices.size(), static_cast<size_t>(10)); // Все 10 вершин должны быть посещены

        // Проверяем, что порядок допустим для DFS
        QVERIFY(task2::check_user_DFS(g, start_vertex, result));

        // qDebug() << "DFS для графа из 10 вершин (стартовая вершина" << start_vertex << "):" << result;
    }
}

void TestTask2::test_generate_random_graph() {
    // Тестируем генерацию графов разного размера
    for (int vertices = 3; vertices <= 6; ++vertices) {
        Graph g = task2::generate_random_graph(vertices);

        // Проверяем количество вершин
        QCOMPARE(g.get_cnt_vertexes(), static_cast<size_t>(vertices));

        // Проверяем связность через DFS
        auto traversal = task2::DFS(g, 1); // Начинаем с вершины 1 (1-based)
        QCOMPARE(traversal.size(), static_cast<size_t>(vertices));

        // Проверяем, что все вершины уникальны
        std::unordered_set<int> unique_vertices(traversal.begin(), traversal.end());
        QCOMPARE(unique_vertices.size(), static_cast<size_t>(vertices));
    }
}

void TestTask2::test_check_user_DFS() {
    std::string in = "3\ninf 1 1\n1 inf inf\n1 inf inf";
    std::stringstream ss(in);
    Graph g(0, ss);

    //qDebug() << "Корректные варианты: ";
    // Проверяем оба возможных корректных варианта
    bool check1 = task2::check_user_DFS(g, 1, {1, 2, 3});
    bool check2 = task2::check_user_DFS(g, 1, {1, 3, 2});

    //qDebug() << "Check1 (1-2-3):" << check1;
    //qDebug() << "Check2 (1-3-2):" << check2;

    if (!check1 && !check2) {
        qDebug() << "Оба варианта обхода не прошли проверку";
    }
    QVERIFY(check1 || check2);

    //qDebug() << "Некорректные варианты: ";
    // Проверяем некорректные варианты
    bool check3 = task2::check_user_DFS(g, 1, {1, 2});
    bool check4 = task2::check_user_DFS(g, 1, {1, 3, 2, 4});
    bool check5 = task2::check_user_DFS(g, 1, {2, 1, 3});
    //qDebug() << check3;
    //qDebug() << check4;
    //qDebug() << check5;


    //QVERIFY(!task2::check_user_DFS(g, 1, {1, 2}));          // Неполный обход
    //QVERIFY(!task2::check_user_DFS(g, 1, {1, 3, 2, 4}));    // Лишняя вершина
    //QVERIFY(!task2::check_user_DFS(g, 1, {2, 1, 3}));       // Неправильная начальная вершина
}

// Добавьте эту строку, если используете qmake
// #include "testtask2.moc"
