#include "include/testtask0.h"
using namespace std;
void TestTask0::test(){
    Graph g(6);
    g.add_edge(0,3,1);
    g.add_edge(1,4,1);
    g.add_edge(2,5,1);
    string ans1 = "0: 1\n1: 1\n2: 1\n3: 1\n4: 1\n5: 1\n";
    string prog_ans1 = task0::input(g, "0");
    string prog_ans4 = task0::input(g, "1");
    string prog_ans2 = task0::input(g, "2");
    string prog_ans3 = task0::input(g, "3");
    string ans3 = "Yes, current Graph is bipart graph";
    string ans4 = "Graph has component connection 3";
    string ans2 = "No, current Graph isn't Eulers graph";
    //cout <<prog_ans4 << '\n' << ans4;
    QCOMPARE(ans4, prog_ans4);
    QCOMPARE(ans2, prog_ans2);
    QCOMPARE(ans3, prog_ans3);
}
Q_DECLARE_METATYPE(TestTask0)
#include "testtask0.moc"
