#include "testtask1.h"
#include "../tasks/task1.h"
#include <sstream>

void TestTask1::test_DFS() {
    // Тест 1: Граф из 3 вершин (1-based)
    {
        std::string in = "3\n0 1 1\n1 0 0\n1 0 0";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        QVERIFY(result == "1 3 2" || result == "1 2 3"); // Варианты для 1-based
    }

    // Тест 2: Граф из 5 вершин (1-based)
    {
        std::string in = "5\n0 1 1 0 0\n1 0 0 1 1\n1 0 0 0 0\n0 1 0 0 0\n0 1 0 0 0";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        QVERIFY(result == "1 3 2 5 4" || result == "1 2 4 5 3"); // Варианты для 1-based
    }

    // Тест 3: Недопустимая стартовая вершина (1-based)
    {
        std::string in = "3\n0 1 0\n1 0 1\n0 1 0";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task1::print_DFS(g, 0); // Вершина 0 не существует
        QCOMPARE(result, "");
        result = task1::print_DFS(g, 4); // Вершина 4 не существует (максимум 3)
        QCOMPARE(result, "");
    }

    // Тест 4: Ориентированный граф (1-based)
    {
        std::string in = "3\n0 1 0\n0 0 1\n0 0 0"; // Ориентированный граф
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        QCOMPARE(result, "1 2 3"); // Жёстко заданный порядок для ориентированного графа
    }

    // Тест 5: Несвязный граф (1-based)
    {
        std::string in = "4\n0 1 0 0\n1 0 0 0\n0 0 0 1\n0 0 1 0"; // Две компоненты связности
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task1::print_DFS(g, 1); // Обход начиная с вершины 1
        QVERIFY(result == "1 2" || result == "2 1"); // Только компонента с вершинами 1 и 2
        result = task1::print_DFS(g, 3); // Обход начиная с вершины 3
        QVERIFY(result == "3 4" || result == "4 3"); // Только компонента с вершинами 3 и 4
    }
}

QTEST_MAIN(TestTask1)
#include "testtask1.moc"