#include "include/testgraph.h"


typedef unordered_map<int, unordered_map<int, int>> uniunii;
typedef unordered_set<tuple<int, int, int>, TupleHash> ustiiith;


void TestGraph::test_creating_graph_data() {

    // INIT DATA
    // TEST 1
    string in1 = "5 \
                 0   3   inf inf -2 \
                 3   0   5   inf 4 \
                 inf 5   0   10  inf \
                 inf inf 10  0   6 \
                 -2  4   inf 6   0";
    stringstream ss1(in1);
    Graph g1(0, ss1);

    uniunii ans1 = {
            {0,
                {{1, 3}, {4, -2}}
            },
            {1,
                {{0, 3}, {2, 5}, {4, 4}}
            },
            {2,
                {{1, 5}, {3, 10}}
            },
            {3,
                {{2, 10}, {4, 6}}
            },
            {4,
                {{0, -2}, {3, 6}, {1, 4}}
            }
        };

    // TEST 2
    string in2 = "3 \
        0   inf 1 \
        inf 0   6 \
        1   6   0 ";
    stringstream ss2(in2);
    Graph g2(0, ss2);

    uniunii ans2 = {
            {0,
                {{2, 1}}
            },
            {1,
                {{2, 6}}
            },
            {2,
                {{0, 1}, {1, 6}}
            }
        };

    // TEST 3
    string in3 = "2 \
                  0   inf \
                  inf 0";
        stringstream ss3(in3);
    Graph g3(0, ss3);

    uniunii ans3 = {
        {0,
            {}
        },
        {1,
            {}
        }
    };

    // TEST 4
    string in4 = "0";
        stringstream ss4(in4);
    Graph g4(0, ss4);

    uniunii ans4 = {};

    // TEST 5 (ERROR)
    string in5 = "-4 \
                 0 1 1 1 \
                 1 0 1 1 \
                 1 1 0 1 \
                 1 1 1 0";
    stringstream ss5(in5);
    try { Graph g5(0, ss5); } catch (const logic_error& e)
    { QCOMPARE(e.what(), "Number of vertices is negative or absent!"); }

    // TEST 6 (ERROR) (вершин больше либо меньше, чем размерность матрицы)
    // такое поведение можно считать непредсказуемым, так как количество вершин определяется
    // по первому числу, поэтому граф может стать не таким, как вы хотели его видеть,
    // более того, он может стать ориентированным (чаще всего)
    string in6 = "2 \
                  0 1   2   3 \
                  1 0   inf inf \
                  2 inf 0   4 \
                  3 inf 4   0";
    stringstream ss6(in6);
    try { Graph g6(0, ss6); } catch (const exception& e)
    { QCOMPARE(e.what(), "This is not undirected graph!"); }

    // END INIT DATA

    QTest::addColumn<Graph>("graph");   // object
    QTest::addColumn<uniunii>("ans");   // result

    QTest::newRow("graph 1") << g1 << ans1;
    QTest::newRow("graph 2") << g2 << ans2;
    QTest::newRow("graph 3") << g3 << ans3;
    QTest::newRow("graph 4") << g4 << ans4;
}
void TestGraph::test_creating_graph() {
    QFETCH(Graph, graph);
    QFETCH(uniunii, ans);
    QCOMPARE(graph.get_graph(), ans);
}


void TestGraph::test_creating_graph_inc_data() {
    // INIT DATA
    // TEST 1
    string in1 = "5 6\
        3   -2   inf inf inf inf \
        3   inf  5   4   inf inf \
        inf inf  5   inf 10  inf \
        inf inf  inf inf 10  6 \
        inf -2   inf 4   inf 6";
    stringstream ss1(in1);
    Graph g1(1, ss1);
    Graph ans1(5);
    ans1.add_edge(0, 1, 3);
    ans1.add_edge(0, 4, -2);
    ans1.add_edge(1, 2, 5);
    ans1.add_edge(1, 4, 4);
    ans1.add_edge(2, 3, 10);
    ans1.add_edge(3, 4, 6);

    // TEST 2
    string in2 = "3   2 \
                  1   inf \
                  inf 6 \
                  1   6";
    stringstream ss2(in2);
    Graph g2(1, ss2);
    Graph ans2(3);
    ans2.add_edge(0, 2, 1);
    ans2.add_edge(1, 2, 6);

    // TEST 3
    string in3 = "0 0"; // пустой граф
    stringstream ss3(in3);
    Graph g3(1, ss3);
    Graph ans3;

    // TEST 4 (ERROR) два ребра там, где 0 вершин
    // максимальное количество ребер в графе с n вершинами равно n * (n - 1) / 2
    string in4 = "0 2";
    stringstream ss4(in4);
    try { Graph g4(1, ss4); } catch (const logic_error& e)
    { QCOMPARE(e.what(), "Number of edges is more than it can be!"); }

    // TEST 5 (ERROR)
    // отрицательное количество вершин
    string in5 = "-4  4 \
                  2   3 \
                  2   3 \
                  inf inf \
                  inf inf";
    stringstream ss5(in5);
    try { Graph g5(1, ss5); } catch (const logic_error& e)
    { QCOMPARE(e.what(), "Number of vertices is negative!"); }

    // TEST 6 (ERROR)
    // ребер больше, чем может быть
    string in6 = "1 2 \
                  1 2";
    stringstream ss6(in6);
    try { Graph g6(1, ss6); } catch (const logic_error& e)
    { QCOMPARE(e.what(), "Number of edges is more than it can be!"); }

    // TEST 7
    // мультиграф (наша реализация графа его не поддерживает)
    // лучше разобраться с обычными
    // если в матрице инцидентности прописан мультиграф,
    // то просто в графе перезапишется значение ребра (молча)
    string in7 = "3 2 \
                  1 2 \
                  1 2  \
                  inf inf";
    stringstream ss7(in7);
    Graph g7(1, ss7);
    Graph ans7(3);
    ans7.add_edge(0, 1, 2);

    // TEST 8
    string in8 = "5 4 \
                  1   inf inf inf \
                  1   1   inf inf \
                  inf 1   1   inf \
                  inf inf 1   1 \
                  inf inf inf 1";
    stringstream ss8(in8);
    Graph g8(1, ss8);
    Graph ans8(5);
    ans8.add_edge(0, 1, 1);
    ans8.add_edge(1, 2, 1);
    ans8.add_edge(2, 3, 1);
    ans8.add_edge(3, 4, 1);

    // TEST 9 (Коронный граф из 8 вершин)
    string in9 = "8 12 \
        1   1   1   inf inf inf inf inf inf inf inf inf \
        inf inf 1   inf inf 1   inf inf 1   inf inf inf \
        inf inf inf 1   1   1   inf inf inf inf inf inf \
        inf inf inf 1   inf inf 1   inf inf 1   inf inf \
        inf inf inf inf inf inf 1   1   1   inf inf inf \
        1   inf inf inf inf inf inf 1   inf inf 1   inf \
        inf inf inf inf inf inf inf inf inf 1   1   1 \
        inf 1   inf inf 1   inf inf inf inf inf inf 1";
    stringstream ss9(in9);
    Graph g9(1, ss9);
    Graph ans9(8);

    ans9.add_edge(4, 1, 1);
    ans9.add_edge(3, 6, 1);
    ans9.add_edge(5, 6, 1);
    ans9.add_edge(6, 7, 1);

    ans9.add_edge(0, 5, 1);
    ans9.add_edge(0, 7, 1);
    ans9.add_edge(0, 1, 1);
    ans9.add_edge(2, 3, 1);

    ans9.add_edge(2, 7, 1);
    ans9.add_edge(1, 2, 1);
    ans9.add_edge(3, 4, 1);
    ans9.add_edge(4, 5, 1);

    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<Graph>("ans");

    QTest::newRow("graph inc 1") << g1 << ans1;
    QTest::newRow("graph inc 2") << g2 << ans2;
    QTest::newRow("graph inc 3") << g3 << ans3;
    QTest::newRow("graph inc 7") << g7 << ans7;
    QTest::newRow("graph inc 8") << g8 << ans8;
    QTest::newRow("graph inc 9") << g9 << ans9;
}

void TestGraph::test_creating_graph_inc() {
    QFETCH(Graph, graph);
    QFETCH(Graph, ans);
    QCOMPARE(graph, ans);
}


void TestGraph::test_creating_graph_ladj_data() {
    // INIT DATA
    // TEST 1
    string in1 = "A:(B,3), (E,-2); \
                  C: (B, 5), (D, 10); \
                  B: (A, 3), (C, 5), (E, 4); \
                  D: (C, 10), (E, 6); \
                  E: (A, -2), (B, 4), (D, 6);";
    stringstream ss1(in1);
    Graph g1(2, ss1);
    Graph ans1(5);
    ans1.add_edge(0, 1, 3);
    ans1.add_edge(0, 4, -2);
    ans1.add_edge(1, 2, 5);
    ans1.add_edge(1, 4, 4);
    ans1.add_edge(2, 3, 10);
    ans1.add_edge(3, 4, 6);

    // TEST 2
    string in2 = "a c 1;b: (c,6); c: (a,1) (b, 6)";
    stringstream ss2(in2);
    Graph g2(2, ss2);
    Graph ans2(3);
    ans2.add_edge(0, 2, 1);
    ans2.add_edge(1, 2, 6);

    // TEST 3
    // если список смежности пуст, то граф тоже будет пустой
    string in3 = ""; // пустой граф
    stringstream ss3(in3);
    Graph g3(2, ss3);
    Graph ans3;

    // TEST 4 (ERROR) (4 - число стабильности)
    // неполное количество ребер
    string in4 = "A: (B, 4) ; B: (A, 4) ;";
    stringstream ss4(in4);
    cout << "TEST 4" << '\n';
    try { Graph g4(2, ss4); g4.print(); } catch (const exception& e) {
        cout << e.what() << '\n';
    }

    // TEST 5 (ERROR)
    // без точки с запятой
    string in5 = "2: (1, 4)  1: (2, 4) ";
    stringstream ss5(in5);
    cout << "TEST 5" << '\n';
    try { Graph g5(2, ss5); g5.print(); } catch (const exception& e) {
        cout << e.what() << '\n';
    }

    // END INIT DATA

    QTest::addColumn<int>("test_n");
    QTest::addColumn<Graph>("graph_ladj");
    QTest::addColumn<Graph>("ans_ladj");

    QTest::newRow("graph ladj 1") << 1 << g1 << ans1;
    QTest::newRow("graph ladj 2") << 2 << g2 << ans2;
    QTest::newRow("graph ladj 3") << 3 << g3 << ans3;
    // QTest::newRow("graph ladj 4") << 4 << g4 << ans4;
    // QTest::newRow("graph ladj 5") << 5 << g5 << ans5;
}

void TestGraph::test_creating_graph_ladj() {
    QFETCH(int, test_n);
    QFETCH(Graph, graph_ladj);
    QFETCH(Graph, ans_ladj);

    cout << "test_creating_graph_ladj_data_" << test_n << '\n';
    cout << "TEST " << test_n << '\n';
    cout << "graph_ladj" << '\n';
    graph_ladj.print();
    cout << "and_ladj" << '\n';
    ans_ladj.print();
}

void TestGraph::test_undirected_graph_data() {
    // INIT DATA
    // TEST 1
    // string in1 = "5 \
    //              0   3   inf inf -2 \
    //              3   0   6   inf 4 \
    //              inf 5   0   10  inf \
    //              inf inf 10  0   6 \
    //              2  0   inf 6   0";
    // stringstream ss1(in1);
    // Graph g1(0, ss1);
    // bool ans1 = false;

    // TEST 2
    string in2 = "5 \
                 0   3   inf inf 2 \
                 3   0   5   inf 4 \
                 inf 5   0   10  inf \
                 inf inf 10  0   6 \
                 2  4   inf 6   0";
    stringstream ss2(in2);
    Graph g2(0, ss2);
    bool ans2 = true;

    // TEST 3
    // string in3 = "3 \
    //               0   inf 2 \
    //               inf 0   inf \
    //               1   6   0 ";
    // stringstream ss3(in3);
    // Graph g3(0, ss3);
    // bool ans3 = false;

    // TEST 4
    string in4 = "2 \
                  0   1 \
                  1  0   ";
    stringstream ss4(in4);
    Graph g4(0, ss4);
    bool ans4 = true;

    // TEST 5
    string in5 = "0";
        stringstream ss5(in5);
    Graph g5(0, ss5);
    bool ans5 = true;

    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<bool>("is_undirected");

    // QTest::newRow("und graph 1") << g1 << ans1;
    QTest::newRow("und graph 2") << g2 << ans2;
    // QTest::newRow("und graph 3") << g3 << ans3;
    QTest::newRow("und graph 4") << g4 << ans4;
    QTest::newRow("und graph 5") << g5 << ans5;
}
void TestGraph::test_undirected_graph() {
    QFETCH(Graph, graph);
    QFETCH(bool, is_undirected);
    QCOMPARE(graph.get_undirected(), is_undirected);
}


void TestGraph::test_add_vertex_data() {
    // INIT DATA
    // TEST 1
    string in1 = "4               \
                 0   3   inf inf  \
                 3   0   5   inf  \
                 inf 5   0   10   \
                 inf inf 10  0   ";
    stringstream ss1(in1);
    Graph g1(0, ss1);
    g1.add_vertex();

    uniunii ans1 = {
        {0,
            {{1, 3}}
        },
        {1,
            {{0, 3}, {2, 5}}
        },
        {2,
            {{1, 5}, {3, 10}}
        },
        {3,
            {{2, 10}}
        },
        {4,
         {}
        }
    };

    // TEST 2
    string in2 = "3 \
        0   inf 1 \
        inf 0   6 \
        1   6   0 ";
    stringstream ss2(in2);
    Graph g2(0, ss2);

    g2.add_vertex();

    uniunii ans2 = {
        {0,
            {{2, 1}}
        },
        {1,
            {{2, 6}}
        },
        {2,
            {{0, 1}, {1, 6}}
        },
        {3,
         {}
        }
    };

    // TEST 3
    string in3 = "2 \
                  0   inf \
                  inf 0";
    stringstream ss3(in3);
    Graph g3(0, ss3);

    g3.add_vertex();

    uniunii ans3 = {
        {0,
            {}
        },
        {1,
            {}
        },
        {2,
            {}
        }
    };
    // TEST 4
    string in4 = "0";
    stringstream ss4(in4);
    Graph g4(0, ss4);

    g4.add_vertex();

    uniunii ans4 = {
        {0,
         {}
        }
    };
    // END INIT DATA

    QTest::addColumn<Graph>("graph");   // object
    QTest::addColumn<uniunii>("ans");   // result

    QTest::newRow("vertex 1") << g1 << ans1;
    QTest::newRow("vertex 2") << g2 << ans2;
    QTest::newRow("vertex 3") << g3 << ans3;
    QTest::newRow("vertex 4") << g4 << ans4;
}
void TestGraph::test_add_vertex() {
    QFETCH(Graph, graph);
    QFETCH(uniunii, ans);
    QCOMPARE(graph.get_graph(), ans);
}


void TestGraph::test_add_edge_data() {
    // TEST1
    string s1 = "2 \
                 0 1 \
                 1 0 ";
    stringstream ss1(s1);
    Graph g1(0, ss1);

    g1.add_edge(0, 1, 2);

    uniunii ans1 = {
        {0,
         {{1, 2}}
        },
        {1,
         {{0, 2}}
        }
    };

    // TEST2
    string s2 = "2 \
                 0 1 \
                 1 0 ";
    stringstream ss2(s2);
    Graph g2(0, ss2);

    g2.add_edge(1, 0, 2);

    uniunii ans2 = {
        {0,
            {{1, 2}}
        },
        {1,
            {{0, 2}}
        }
    };

    // TEST3
    string s3 = "3 \
        0   1 inf \
        1   0 inf \
        inf inf 0";
        stringstream ss3(s3);
    Graph g3(0, ss3);

    g3.add_edge(2, 0, 100);
    g3.add_edge(0, 2, 1203);

    uniunii ans3 = {
        {0,
            {{1, 1}, {2, 1203}}
        },
        {1,
            {{0, 1}}
        },
        {2,
            {{0, 1203}}
        }
    };

    // TEST 4
    string s4 = "0";
    stringstream ss4(s4);
    Graph g4(0, ss4);

    g4.add_vertex();
    g4.add_vertex();
    g4.add_edge(1, 0, 100);
    g4.add_edge(0, 1, 1203);

    uniunii ans4 = {
        {0,
            {{1, 1203}}
        },
        {1,
            {{0, 1203}}
        }
    };

    // TEST 5
    string s5 = "3 \
                0   inf 1 \
                inf 0   6 \
                1   6   0 ";
    stringstream ss5(s5);
    Graph g5(0, ss5);

    g5.add_edge(1, 0, 100);
    g5.add_edge(45, 435, 12);
    g5.add_edge(0, 0, 45);

    uniunii ans5 = {
        {0,
            {{2, 1}, {1, 100}}
        },
        {1,
            {{2, 6}, {0, 100}}
        },
        {2,
            {{0, 1}, {1, 6}}
        }
    };
    // END INIT DATA


    QTest::addColumn<Graph>("graph");
    QTest::addColumn<uniunii>("ans");

    QTest::newRow("edge 1") << g1 << ans1;
    QTest::newRow("edge 2") << g2 << ans2;
    QTest::newRow("edge 3") << g3 << ans3;
    QTest::newRow("edge 4") << g4 << ans4;
    QTest::newRow("edge 5") << g5 << ans5;

}
void TestGraph::test_add_edge() {
    QFETCH(Graph, graph);
    QFETCH(uniunii, ans);
    QCOMPARE(graph.get_graph(), ans);
}


void TestGraph::test_get_edges_data() {
    // TEST1
    string s1 = "2 \
        0 1 \
        1 0 ";
    stringstream ss1(s1);
    Graph g1(0, ss1);

    g1.add_edge(0, 1, 200);

    ustiiith ans1 = {
        make_tuple(1, 0, 200)
    };

    // TEST2
    string s2 = "3 \
        0 1 3 \
        1 0 2 \
        3 2 0";
    stringstream ss2(s2);
    Graph g2(0, ss2);

    ustiiith ans2 = {
        make_tuple(1, 0, 1),
        make_tuple(2, 0, 3),
        make_tuple(2, 1, 2),
    };

    // TEST3
    string s3 = "4   \
        0  1    3    -2  \
        1  0    inf  2   \
        3  inf  0    inf \
        -2 2    inf  0";
    stringstream ss3(s3);
    Graph g3(0, ss3);

    ustiiith ans3 = {
        make_tuple(1, 0, 1),
        make_tuple(2, 0, 3),
        make_tuple(3, 0, -2),
        make_tuple(3, 1, 2),
    };
    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<ustiiith>("ans");

    QTest::newRow("get edges 1") << g1 << ans1;
    QTest::newRow("get edges 2") << g2 << ans2;
    QTest::newRow("get edges 3") << g3 << ans3;
    // QTest::newRow("get edges 4") << g4 << ans4;
    // QTest::newRow("get edges 5") << g5 << ans5;
}
void TestGraph::test_get_edges() {
    QFETCH(Graph, graph);
    QFETCH(ustiiith, ans);
    QCOMPARE(graph.get_edges(), ans);
}


void TestGraph::test_equal_data() {
    // TEST1
    string s1 = "2 \
        0 1 \
        1 0 ";
        stringstream ss1(s1);
    Graph g1(0, ss1);

    Graph ans1;
    ans1.add_vertex();
    ans1.add_vertex();
    ans1.add_edge(0, 1, 1);

    // TEST2
    string s2 = "4   \
                0  1    3    -2  \
                1  0    inf  2   \
                3  inf  0    inf \
                -2 2    inf  0";
    stringstream ss2(s2);
    Graph g2(0, ss2);


    Graph ans2;
    ans2.add_vertex();
    ans2.add_vertex();
    ans2.add_vertex();
    ans2.add_vertex();
    ans2.add_edge(0, 2, 3);
    ans2.add_edge(0, 1, 1);
    ans2.add_edge(1, 3, 2);
    ans2.add_edge(3, 0, -2);

    // TEST3
    string s3 = "1 \
                 0";        // одна вершина в матрице
    stringstream ss3(s3);
    Graph g3(0, ss3);

    Graph ans3;
    ans3.add_vertex();
    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<Graph>("my_graph");
    QTest::newRow("equal 1") << g1 << ans1;
    QTest::newRow("equal 2") << g2 << ans2;
    QTest::newRow("equal 3") << g3 << ans3;
}
void TestGraph::test_equal() {
    QFETCH(Graph, graph);
    QFETCH(Graph, my_graph);
    QCOMPARE(graph, my_graph);
}

void TestGraph::test_get_degree_data() {
    // TEST1
    string s1 = "2 \
        0 1 \
        1 0 ";
        stringstream ss1(s1);
    Graph g1(0, ss1);

    int ans1 = 1;

    // TEST2
    string s2 = "4   \
                0  1    3    -2  \
                1  0    inf  2   \
                3  inf  0    inf \
                -2 2    inf  0";
                stringstream ss2(s2);
    Graph g2(0, ss2);


    int ans2 = 3;

    // TEST3
    string s3 = "1 \
        0";        // одна вершина в матрице
        stringstream ss3(s3);
    Graph g3(0, ss3);

    int ans3 = 0;

    // TEST4
    string s4 = "0";
    stringstream ss4(s4);
    Graph g4(0, ss4);

    int ans4 = 0;
    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<int>("degree");
    QTest::newRow("degree 1") << g1 << ans1;
    QTest::newRow("degree 2") << g2 << ans2;
    QTest::newRow("degree 3") << g3 << ans3;
    // QTest::newRow("degree 4") << g4 << ans4; // ИСКЛЮЧЕНИЕ, ВСЕ НОРМАЛЬНО

}
void TestGraph::test_get_degree() {
    QFETCH(Graph, graph);
    QFETCH(int, degree);
    QCOMPARE(graph.get_v_degree(0), degree);
}

Q_DECLARE_METATYPE(TestGraph)
#include "testgraph.moc"
