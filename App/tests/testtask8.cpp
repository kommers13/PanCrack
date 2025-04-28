// testtask8.cpp
#include "include/testtask8.h"
#include "task8.h"
#include <sstream>
#include <QDebug>

void TestTask8::test_dijkstra() {
    // Test 1: Simple connected graph with inf
    {
        qDebug() << "\n=== Test 1: Simple connected graph with inf ===";
        std::string in = "4 \
                         inf 1 4 inf \
                         1 inf 2 5 \
                         4 2 inf 1 \
                         inf 5 1 inf";
        std::stringstream ss(in);
        Graph g(ss);

        // qDebug() << "Input matrix:";
        std::istringstream temp(in);
        std::string line;
        while (std::getline(temp, line)) {
            // qDebug() << line.c_str();
        }

        std::string result = task8::print_shortest_path(g, 0, 3);
        // qDebug() << "Result:\n" << result.c_str();

        QVERIFY2(result.find("Distance: 4") != std::string::npos, "Distance should be 4");
        QVERIFY2(result.find("1 → 2 → 3 → 4") != std::string::npos, "Path should be 1→2→3→4");
    }

    // Test 2: No path exists (isolated vertex)
    {
        qDebug() << "\n=== Test 2: No path exists ===";
        std::string in = "3\n"
                         "inf 1 inf\n"
                         "1 inf inf\n"
                         "inf inf inf";
        std::stringstream ss(in);
        Graph g(ss);

        // qDebug() << "Input matrix:";
        std::istringstream temp(in);
        std::string line;
        while (std::getline(temp, line)) {
            // qDebug() << line.c_str();
        }

        std::string result = task8::print_shortest_path(g, 0, 2);
        // qDebug() << "Result:\n" << result.c_str();

        QVERIFY2(result.find("No path exists") != std::string::npos, "Should detect no path");
    }

    // Test 3: Direct connection is shortest
    {
        qDebug() << "\n=== Test 3: Direct connection is shortest ===";
        std::string in = "3\n"
                         "inf 5 2\n"
                         "5 inf 1\n"
                         "2 1 inf";
        std::stringstream ss(in);
        Graph g(ss);

        // qDebug() << "Input matrix:";
        std::istringstream temp(in);
        std::string line;
        while (std::getline(temp, line)) {
            // qDebug() << line.c_str();
        }

        std::string result = task8::print_shortest_path(g, 0, 2);
        // qDebug() << "Result:\n" << result.c_str();

        QVERIFY2(result.find("Distance: 2") != std::string::npos, "Distance should be 2");
        QVERIFY2(result.find("1 → 3") != std::string::npos, "Path should be direct 1→3");
    }
}
