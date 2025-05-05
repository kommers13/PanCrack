#include "include/testtask4.h"
using namespace std;
void TestTask4::test1(){
    string str_graph = "6 \
        inf 1 inf inf 1 inf \
        1 inf inf inf inf 1 \
        inf inf inf 1 1 inf \
        inf inf 1 inf inf 1 \
        1 inf 1 inf inf inf \
        inf 1 inf 1 inf inf";
    stringstream ss(str_graph);
    Graph rand_graph(0, ss);
    string input_user = " 0 ->  4->1 -> 2-> 5   -> 3 ";
    bool task_way = task4::input(input_user, "0", rand_graph);
    QCOMPARE(true,task_way);
}
void TestTask4::test2(){/*
    string str_graph = "12 \
    inf 1 inf inf 1 inf inf 1 inf inf 1 inf \
    1 inf inf inf 1 inf inf inf inf inf inf inf \
    inf inf inf inf inf 1 inf inf inf inf inf inf \
    inf inf inf inf inf 1 1 inf inf 1 inf inf \
    1 1 inf inf inf inf inf 1 1 1 inf 1 \
    inf inf 1 1 inf inf 1 inf inf inf inf inf \
    inf inf inf 1 inf 1 inf inf inf inf inf inf \
    1 inf inf inf inf inf inf inf inf inf inf 1 \
    inf inf inf inf 1 inf inf inf inf inf inf inf \
    inf inf inf 1 1 inf inf inf inf inf inf 1 \
    1 inf inf inf inf inf inf inf inf inf inf inf \
    inf inf inf inf 1 inf inf 1 inf 1 inf inf";
    stringstream ss(str_graph);
    Graph rand_graph(0, ss);
    string input_user = " 11 ->  9->7 -> 5-> 8   -> 3 -> 1 -> 0   -> 10 ->6 ->5->2      ";
    bool task_way = task4::input(input_user, "11", rand_graph);
    QCOMPARE(true,task_way);*/

}
void TestTask4::test3(){
    string str_graph = "4 \
        inf 1 1 inf \
        1 inf inf 1 \
        1 inf inf 1 \
        inf 1 1 inf";
    stringstream ss(str_graph);
    Graph rand_graph(0, ss);
    string input_user = "   3-> 2 ->1- >0 ";
    bool task_way = task4::input(input_user, "3", rand_graph);
    QCOMPARE(true,task_way);
}
void TestTask4::test4(){
    string str_graph = "7 \
        inf inf 1 inf inf 1 inf \
        inf inf inf inf 1 inf inf \
        1 inf inf inf inf inf 1 \
        inf inf inf inf 1 inf inf \
        inf 1 inf 1 inf inf inf \
        1 inf inf inf inf inf 1 \
        inf inf 1 inf inf 1 inf";
    stringstream ss(str_graph);
    Graph rand_graph(0, ss);
    string input_user = "   2-> 6 ->0- >5->  4 ->3 ->1 ";
    bool task_way = task4::input(input_user, "2", rand_graph);
    QCOMPARE(true,task_way);
}
Q_DECLARE_METATYPE(TestTask4)
#include "testtask4.moc"
