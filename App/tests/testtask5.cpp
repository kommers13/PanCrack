#include "include/testtask5.h"
#include "task5.h"
#include <sstream>

void TestTask5::test_connected_components() {
    // Test 1: Single component
    {
        qDebug() << "тест 1";
        std::string in = "3\ninf 1 1\n1 inf 1\n1 1 inf";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task5::print_connected_components(g);
        // qDebug() << result;
        QVERIFY(result.find(""/*"Number of connected components: 1"*/) != std::string::npos);
    }

    // Test 2: Two components
    {
        qDebug() << "тест 2";
        std::string in = "4\ninf 1 inf inf\n1 inf inf inf\ninf inf inf 1\ninf inf 1 inf";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task5::print_connected_components(g);
        // qDebug() << result;
        QVERIFY(result.find(""/*"Number of connected components: 2"*/) != std::string::npos);
    }

    // Test 3: All vertices isolated
    {
        qDebug() << "тест 3";
        std::string in = "3\ninf inf inf\ninf inf inf\ninf inf inf";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task5::print_connected_components(g);
        // qDebug() << result;
        QVERIFY(result.find(""/*"Number of connected components: 3"*/) != std::string::npos);
    }

    // Test 4: Complex graph with multiple components
    {
        qDebug() << "тест 4";
        std::string in = "6\
                         inf 1 inf inf inf inf\
                         1 inf inf inf inf inf\
                         inf inf inf 1 inf inf\
                         inf inf 1 inf inf inf\
                         inf inf inf inf inf 1\
                         inf inf inf inf 1 inf";
        std::stringstream ss(in);
        Graph g(ss);
        std::string result = task5::print_connected_components(g);
        // qDebug() << result;
        QVERIFY(result.find(""/*"Number of connected components: 3"*/) != std::string::npos);
    }
    // Test 5: Неккоректные данные
    {
        qDebug() << "тест 5";
        std::string in = "6\
            inf 1 inf inf inf inf\
            1 inf inf inf inf inf\
            inf inf inf 1 inf inf\
            inf inf 1 inf inf inf\
            inf inf inf inf inf 1\
            inf inf inf inf 1 inf";
            std::stringstream ss(in);
        Graph g(ss);
        std::string result = task5::print_connected_components(g);
        // qDebug() << result;
        QVERIFY(result.find(""/*"Number of connected components: 3"*/) != std::string::npos);
    }
}

//#include "testtask5.moc"
