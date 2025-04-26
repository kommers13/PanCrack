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


void TestGraph::test_undirected_graph_data() {
    // INIT DATA
    // TEST 1
    // string in1 = "5 \
    //              0   3   inf inf -2 \
    //              3   0   6   inf 4 \
    //              inf 5   0   10  inf \
    //              inf inf 10  0   6 \
    //              2  0   inf 6   0";
    //              stringstream ss1(in1);
    // Graph g1(ss1);
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
    // Graph g3(ss3);
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
