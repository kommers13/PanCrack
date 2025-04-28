#include "include/testtask6.h"
#include "task6.h"
#include <sstream>

void TestTask6::test_graph_generation() {
    qDebug() << "=== Тест генерации графа ===";
    Graph g = task6::generate_random_graph(5);
    qDebug() << "Сгенерирован граф с" << g.vertex_count() << "вершинами";
    qDebug() << "Матрица смежности:\n" << task6::graph_to_string(g).c_str();
    QVERIFY(g.vertex_count() == 5);
    qDebug() << "Тест пройден успешно\n";
}

void TestTask6::test_answer_checking() {
    qDebug() << "=== Тест проверки компонент связности ===";

    // Тест 1: Правильный ответ
    {
        qDebug() << "Тест 1: Ожидается верный ответ (2 компоненты)";
        Graph g(4);
        g.add_edge(0, 1, 1);
        g.add_edge(2, 3, 1);

        auto [result1, msg1] = task6::check_answer(g, 2);
        qDebug() << msg1.c_str();
        QVERIFY(result1);
    }

    // Тест 2: Неправильный ответ
    {
        qDebug() << "Тест 2: Ожидается ошибка (неправильный ответ)";
        Graph g(4);
        g.add_edge(0, 1, 1);
        g.add_edge(2, 3, 1);

        auto [result2, msg2] = task6::check_answer(g, 1);
        qDebug() << msg2.c_str();
        QVERIFY(!result2);
    }

    // Тест 3: Все вершины изолированы
    {
        qDebug() << "Тест 3: Все вершины изолированы (4 компоненты)";
        Graph g(4); // Граф без рёбер

        auto [result3, msg3] = task6::check_answer(g, 4);
        qDebug() << msg3.c_str();
        QVERIFY(result3);
    }

    // Тест 4: Полносвязный граф
    {
        qDebug() << "Тест 4: Полносвязный граф (1 компонента)";
        Graph g(3);
        g.add_edge(0, 1, 1);
        g.add_edge(0, 2, 1);
        g.add_edge(1, 2, 1);

        auto [result4, msg4] = task6::check_answer(g, 1);
        qDebug() << msg4.c_str();
        QVERIFY(result4);
    }

    // Тест 5: Неверный ответ
    {
        qDebug() << "Тест 5: Все вершины изолированы (4 компоненты)";
        Graph g(4); // Граф без рёбер

        auto [result5, msg5] = task6::check_answer(g, 3);
        qDebug() << msg5.c_str();
        QVERIFY(!result5); // Исправлено: ожидается FAIL при неверном ответе
    }

    // Новые дополнительные тесты
    {
        // Тест 6: Граф с тремя компонентами (неверный ответ)
        qDebug() << "Тест 6: Граф с тремя компонентами (ответ 2 вместо 3)";
        Graph g(6);
        g.add_edge(0, 1, 1);
        g.add_edge(2, 3, 1);
        // Вершины 4 и 5 изолированы

        auto [result6, msg6] = task6::check_answer(g, 2);
        qDebug() << msg6.c_str();
        QVERIFY(!result6);
    }

    {
        // Тест 7: Сложная структура (неверный ответ)
        qDebug() << "Тест 7: Сложный граф (ответ 1 вместо 2 компонент)";
        Graph g(5);
        g.add_edge(0, 1, 1);
        g.add_edge(1, 2, 1);
        g.add_edge(3, 4, 1);

        auto [result7, msg7] = task6::check_answer(g, 1);
        qDebug() << msg7.c_str();
        QVERIFY(!result7);
    }

    {
        // Тест 8: Граф-звезда (неверный ответ)
        qDebug() << "Тест 8: Граф-звезда (ответ 2 вместо 1 компоненты)";
        Graph g(4);
        g.add_edge(0, 1, 1);
        g.add_edge(0, 2, 1);
        g.add_edge(0, 3, 1);

        auto [result8, msg8] = task6::check_answer(g, 2);
        qDebug() << msg8.c_str();
        QVERIFY(!result8);
    }

    {
        // Тест 9: Большой граф (неверный ответ)
        qDebug() << "Тест 9: Большой граф (ответ 3 вместо 4 компонент)";
        Graph g(8);
        g.add_edge(0, 1, 1);
        g.add_edge(2, 3, 1);
        g.add_edge(4, 5, 1);
        g.add_edge(6, 7, 1);

        auto [result9, msg9] = task6::check_answer(g, 3);
        qDebug() << msg9.c_str();
        QVERIFY(!result9);
    }
}

//#include "testtask6.moc"
