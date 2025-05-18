#include "include/testtask9.h"
#include "task9.h"
#include <sstream>

void TestTask9::test_floyd_warshall() {
    // Тест 1: Простой неориентированный граф
    {
        qDebug() << "Тест 1: Простой граф";
        std::string in = "4\n"
                         "0 5 inf 10\n" //Диагональ всегда 0, остальное - inf
                         "5 0 3 inf\n"
                         "inf 3 0 1\n"
                         "10 inf 1 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 2: Полносвязный граф без INF
    {
        qDebug() << "\nТест 2: Полносвязный граф";
        std::string in = "3\n"
                         "0 2 3\n"
                         "2 0 1\n"
                         "3 1 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() <<task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 3: Граф с одним узлом
    {
        qDebug() << "\nТест 3: Одиночная вершина";
        std::string in = "1\n"
                         "0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 4: Двудольный граф
    {
        qDebug() << "\nТест 4: Двудольный граф";
        std::string in = "4\n"
                         "0 3 inf inf\n"
                         "3 0 inf 4\n"
                         "inf inf 0 2\n"
                         "inf 4 2 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 5: Граф с отрицательными весами (без отрицательных циклов)
    {
        qDebug() << "\nТест 5: Граф с отрицательными весами";
        std::string in = "4\n"
                         "0 -1 4 inf\n"
                         "-1 0 3 2\n"
                         "4 3 0 -5\n"
                         "inf 2 -5 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 6: Дерево
    {
        qDebug() << "\nТест 6: Дерево";
        std::string in = "5\n"
                         "0 2 inf inf inf\n"
                         "2 0 1 3 inf\n"
                         "inf 1 0 inf inf\n"
                         "inf 3 inf 0 4\n"
                         "inf inf inf 4 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }

    // Тест 7: Циклический граф
    {
        qDebug() << "\nТест 7: Циклический граф";
        std::string in = "4\n"
                         "0 5 inf 10\n"
                         "5 0 3 inf\n"
                         "inf 3 0 1\n"
                         "10 inf 1 0";
        std::stringstream ss(in);
        Graph g(0, ss);
        auto dist_matrix = task9::floyd_warshall(g);
        qDebug() << "Матрица расстояний:";
        qDebug() << task9::print_distance_matrix(dist_matrix).c_str();
    }
}

//#include "testtask9.moc"
