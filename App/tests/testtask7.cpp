#include "include/testtask7.h"


typedef unordered_map<int, unordered_map<int, int>> uniunii;


void TestTask7::test_MST_data() {
    // INIT DATA
    // TEST 1
    string s1 = "3 \
                0 2 3 \
                2 0 -2 \
                3 -2 0";
    stringstream ss1(s1);
    Graph g1(ss1);

    Graph ans1(3);  // граф с 3 вершинами без ребер
    ans1.add_edge(0, 1, 2);
    ans1.add_edge(1, 2, -2);

    // TEST2
    string s2 = "3 \
                0   1  inf \
                1   0  -3 \
                inf -3 0";
                stringstream ss2(s2);
    Graph g2(ss2);

    Graph ans2(3);  // граф с 3 вершинами без ребер
    ans2.add_edge(0, 1, 1);
    ans2.add_edge(2, 1, -3);

    // TEST3
    string s3 = "0";
    stringstream ss3(s3);
    Graph g3(ss3);

    Graph ans3;

    // TEST4
    string s4 = "1 \
                 0";
    stringstream ss4(s4);
    Graph g4(ss4);

    Graph ans4(1);

    // TEST5 (PANTELEEV TEST)
    string s5 = "8                         \
                 0   2   inf inf 6   3   inf inf    \
                 2   0   4   inf inf 1   7   inf \
                 inf 4   0   1   inf inf 6   5   \
                 inf inf 1   0   inf inf inf 6 \
                 6   inf inf inf 0   5   inf inf \
                 3   1   inf inf 5   0   7   inf  \
                 inf 7   6   inf inf 7   0   3    \
                 inf inf 5   6   inf inf 3   0";
    stringstream ss5(s5);
    Graph g5(ss5);

    Graph ans5(8);
    ans5.add_edge(0, 1, 2);
    ans5.add_edge(1, 5, 1);
    ans5.add_edge(1, 2, 4);
    ans5.add_edge(2, 3, 1);
    ans5.add_edge(2, 7, 5);
    ans5.add_edge(6, 7, 3);
    ans5.add_edge(4, 5, 5);

    // END INIT DATA


    QTest::addColumn<Graph>("graph");
    QTest::addColumn<Graph>("MST");

    QTest::newRow("MST 1") << g1 << ans1;
    QTest::newRow("MST 2") << g2 << ans2;
    QTest::newRow("MST 3") << g3 << ans3;
    QTest::newRow("MST 4") << g4 << ans4;
    QTest::newRow("MST 5") << g5 << ans5;


}
void TestTask7::test_MST() {
    QFETCH(Graph, graph);
    QFETCH(Graph, MST);
    QCOMPARE(task7::create_MST(graph), MST);
}
