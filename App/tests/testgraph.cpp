#include "include/testgraph.h"
#include <graph.h>


typedef unordered_map<int, unordered_map<int, int>> uniunii;


void TestGraph::test_creating_graph_data() {

    // INIT DATA
    // TEST 1
    string in1 = "5 \
                 0   3   inf inf -2 \
                 3   0   5   inf 4 \
                 inf 5   0   10  inf \
                 inf inf 10  0   6 \
                 -2  0   inf 6   0";
    stringstream ss1(in1);
    Graph g1(ss1);

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
                {{0, -2}, {3, 6}, {1, 0}}
            }
        };

    // TEST 2
    string in2 = "3 \
        0   inf 1 \
        inf 0   6 \
        1   6   0 ";
    stringstream ss2(in2);
    Graph g2(ss2);

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
    Graph g3(ss3);

    uniunii ans3 = {
        {0,
            {}
        },
        {1,
            {}
        }
    };
    // END INIT DATA

    QTest::addColumn<Graph>("graph");   // object
    QTest::addColumn<uniunii>("ans");   // result

    QTest::newRow("graph 1") << g1 << ans1;
    QTest::newRow("graph 2") << g2 << ans2;
    QTest::newRow("graph 3") << g3 << ans3;
}


void TestGraph::test_creating_graph() {
    QFETCH(Graph, graph);
    QFETCH(uniunii, ans);
    QCOMPARE(graph.get_graph(), ans);
}


void TestGraph::test_undirected_graph_data() {
    // INIT DATA
    // TEST 1
    string in1 = "5 \
                 0   3   inf inf -2 \
                 3   0   6   inf 4 \
                 inf 5   0   10  inf \
                 inf inf 10  0   6 \
                 2  0   inf 6   0";
                 stringstream ss1(in1);
    Graph g1(ss1);
    bool ans1 = false;

    // TEST 2
    string in2 = "5 \
                 0   3   inf inf 2 \
                 3   0   5   inf 4 \
                 inf 5   0   10  inf \
                 inf inf 10  0   6 \
                 2  4   inf 6   0";
    stringstream ss2(in2);
    Graph g2(ss2);
    bool ans2 = true;

    // TEST 3
    string in3 = "3 \
                  0   inf 2 \
                  inf 0   inf \
                  1   6   0 ";
    stringstream ss3(in3);
    Graph g3(ss3);
    bool ans3 = false;

    // TEST 4
    string in4 = "2 \
                  0   1 \
                  1  0   ";
    stringstream ss4(in4);
    Graph g4(ss4);
    bool ans4 = true;

    // END INIT DATA

    QTest::addColumn<Graph>("graph");
    QTest::addColumn<bool>("is_undirected");

    QTest::newRow("und graph 1") << g1 << ans1;
    QTest::newRow("und graph 2") << g2 << ans2;
    QTest::newRow("und graph 3") << g3 << ans3;
    QTest::newRow("und graph 4") << g4 << ans4;
}

void TestGraph::test_undirected_graph() {
    QFETCH(Graph, graph);
    QFETCH(bool, is_undirected);
    QCOMPARE(graph.get_undirected(), is_undirected);
}

Q_DECLARE_METATYPE(TestGraph)
#include "testgraph.moc"
