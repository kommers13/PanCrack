#include "include/testtask3.h"
using namespace std;

void TestTask3::test1_BFS(){
    string str_graph = "6 \
    inf 1 inf inf 1 inf \
    1 inf inf inf inf 1 \
    inf inf inf 1 1 inf \
    inf inf 1 inf inf 1 \
    1 inf 1 inf inf inf \
    inf 1 inf 1 inf inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "0");
    string ans_way = "0 -> 4 -> 1 -> 2 -> 5 -> 3";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test2_BFS(){
    string str_graph = "15 \
        inf 1 inf inf inf inf inf 1 inf inf inf inf 1 inf inf \
        1 inf inf inf inf inf inf inf inf inf inf inf inf inf inf \
        inf inf inf inf inf inf inf 1 inf 1 inf inf inf inf inf \
        inf inf inf inf 1 inf 1 inf inf inf inf inf inf inf inf \
        inf inf inf 1 inf inf inf inf inf inf inf inf inf inf inf \
        inf inf inf inf inf inf inf 1 inf 1 inf inf inf inf inf \
        inf inf inf 1 inf inf inf inf 1 inf inf inf inf inf inf \
        1 inf 1 inf inf 1 inf inf 1 inf inf 1 inf inf inf \
        inf inf inf inf inf inf 1 1 inf inf inf inf inf inf inf \
        inf inf 1 inf inf 1 inf inf inf inf 1 inf inf inf inf \
        inf inf inf inf inf inf inf inf inf 1 inf inf inf inf inf \
        inf inf inf inf inf inf inf 1 inf inf inf inf inf 1 1 \
        1 inf inf inf inf inf inf inf inf inf inf inf inf inf 1 \
        inf inf inf inf inf inf inf inf inf inf inf 1 inf inf inf \
        inf inf inf inf inf inf inf inf inf inf inf 1 1 inf inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "14");
    //cout << task_way << '\n';
    string ans_way = "14 -> 12 -> 11 -> 0 -> 13 -> 7 -> 1 -> 8 -> 5 -> 2 -> 6 -> 9 -> 3 -> 10 -> 4";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test3_BFS(){
    string str_graph = "1 \
        inf";
        stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "0");
    string ans_way = "0";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test4_BFS(){
    string str_graph = "9 \
        inf inf inf 1 inf 1 inf inf 1 \
        inf inf 1 inf inf inf inf inf 1 \
        inf 1 inf inf inf inf inf 1 inf \
        1 inf inf inf inf inf inf 1 inf \
        inf inf inf inf inf inf 1 inf 1 \
        1 inf inf inf inf inf inf 1 inf \
        inf inf inf inf 1 inf inf 1 inf \
        inf inf 1 1 inf 1 1 inf inf \
        1 1 inf inf 1 inf inf inf inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "7");
    //cout << task_way;
    string ans_way = "7 -> 6 -> 5 -> 3 -> 2 -> 4 -> 0 -> 1 -> 8";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test5_BFS(){
    string str_graph = "5 \
        inf 1 1 inf inf \
        1 inf inf 1 inf \
        1 inf inf inf inf \
        inf 1 inf inf 1 \
        inf inf inf 1 inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "2");
    //cout << task_way;
    string ans_way = "2 -> 0 -> 1 -> 3 -> 4";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test6_BFS(){
    string str_graph = "3 \
        inf 1 inf \
        1 inf 1 \
        inf 1 inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "1");
    //cout << task_way;
    string ans_way = "1 -> 2 -> 0";
    QCOMPARE(ans_way,task_way);
}
void TestTask3::test7_BFS(){
    string str_graph = "7 \
        inf inf inf inf inf inf 1 \
        inf inf inf inf inf inf 1 \
        inf inf inf 1 inf inf 1 \
        inf inf 1 inf inf inf inf \
        inf inf inf inf inf 1 1 \
        inf inf inf inf 1 inf inf \
        1 1 1 inf 1 inf inf inf";
    stringstream ss(str_graph);
    Graph g(0, ss);
    string task_way = task3::input(g, "6");
    //cout << task_way;
    string ans_way = "6 -> 4 -> 2 -> 1 -> 0 -> 5 -> 3";
    QCOMPARE(ans_way,task_way);
}

Q_DECLARE_METATYPE(TestTask3)
#include "testtask3.moc"
