#include "include/testtask1.h"
#include <task1.h>
#include <sstream>

void TestTask1::test_DFS() {
    // Тест 1: Граф из 3 вершин (1-based)
    {
        qDebug() << "1 тест";
        std::string in = "3\ninf 1 1\n1 inf inf\n1 inf inf";
        std::stringstream ss(in);
        Graph g(0, ss);
        std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        // qDebug() << result;
        QVERIFY(result == "1 3 2" || result == "1 2 3"); // Варианты для 1-based
    }

    // Тест 2: Граф из 5 вершин (1-based)
    {
        qDebug() << "2 тест";
        std::string in = "5\ninf 1 1 inf inf\n1 inf inf 1 1\n1 inf inf inf inf\ninf 1 inf inf inf\ninf 1 inf inf inf";
        std::stringstream ss(in);
        Graph g(0, ss);
        std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        // qDebug() << result;

        QVERIFY(result == "1 3 2 5 4" || result == "1 2 4 5 3"); // Варианты для 1-based
    }

    // Тест 3: Недопустимая стартовая вершина (1-based)
    {
        qDebug() << "3 тест";
        std::string in = "3\n0 1 0\n1 0 1\n0 1 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        std::string result = task1::print_DFS(g, 0); // Вершина 0 не существует
        QCOMPARE(result, "");
        result = task1::print_DFS(g, 4); // Вершина 4 не существует (максимум 3)
        QCOMPARE(result, "");
        // qDebug() << result;
    }

    // Тест 4: Ориентированный граф (1-based) У НАС ТОЛЬКО НЕОРИЕНТИРОВАННЫЕ ГРАФЫ

    //{
        //qDebug() << "4 тест";
        //std::string in = "3\ninf 1 inf\ninf inf 1\ninf inf inf"; // Ориентированный граф
        //std::stringstream ss(in);
        //Graph g(ss);
        //std::string result = task1::print_DFS(g, 1); // Начинаем с вершины 1
        //QCOMPARE(result, "1 2 3"); // Жёстко заданный порядок для ориентированного графа
    //}

    // Тест 5: Несвязный граф (1-based)
    {
        qDebug() << "5 тест";
        std::string in = "4\ninf 1 inf inf\n1 inf inf inf\ninf inf inf 1\ninf inf 1 inf"; // Две компоненты связности
        std::stringstream ss(in);
        Graph g(0, ss);
        std::string result = task1::print_DFS(g, 1); // Обход начиная с вершины 1
        // qDebug() << result;
        QVERIFY(result == "1 2" || result == "2 1"); // Только компонента с вершинами 1 и 2
        result = task1::print_DFS(g, 3); // Обход начиная с вершины 3
        // qDebug() << result;
        QVERIFY(result == "3 4" || result == "4 3"); // Только компонента с вершинами 3 и 4
    }
    // Тест 6: Граф из 10 вершин (1-based)
    {
        qDebug() << "6 тест";
        std::string in = "10 \
            inf 1 1 inf inf inf inf inf inf inf \
            1 inf 1 1 inf inf inf inf inf inf \
            1 1 inf inf 1 inf inf inf inf inf \
            inf 1 inf inf 1 1 inf inf inf inf \
            inf inf 1 1 inf 1 1 inf inf inf \
            inf inf inf 1 1 inf inf 1 inf inf \
            inf inf inf inf 1 inf inf inf 1 1 \
            inf inf inf inf inf 1 inf inf 1 inf \
            inf inf inf inf inf inf 1 1 inf 1 \
            inf inf inf inf inf inf 1 inf 1 inf";


        std::stringstream ss(in);
        Graph g(0, ss);
        std::string result = task1::print_DFS(g, 5); // Начинаем с вершины 5
        // qDebug() << result;
        QVERIFY(result == "5 3 1 2 4 6 8 9 7 10" || result == "5 3 1 2 4 6 8 9 10 7");
    }
}

//#include "testtask1.moc"
