#include "include/testtask11.h"
typedef unordered_map<int, unordered_map<int, int>> uniunii;
using namespace std;
void TestTask11::lection_test(){

    string tree_n1 = "0 1 1 0";
    Graph tree_n1_ans(5);
    tree_n1_ans.add_edge(0, 2, 1);
    tree_n1_ans.add_edge(1, 3, 1);
    tree_n1_ans.add_edge(1, 4, 1);
    tree_n1_ans.add_edge(0, 1, 1);
    Graph task11_ans1 = task11::input(tree_n1, "5");

    QCOMPARE(task11_ans1, tree_n1_ans);
}
void TestTask11::hard_test(){
    string tree_n2 = "0 0 0 1 1 1 0";
    string in2 = "8 \
        inf 1 1 1 1 inf inf inf \
        1 inf inf inf inf 1 1 1 \
        1 inf inf inf inf inf inf inf \
        1 inf inf inf inf inf inf inf \
        1 inf inf inf inf inf inf inf \
        inf 1 inf inf inf inf inf inf \
        inf 1 inf inf inf inf inf inf \
        inf 1 inf inf inf inf inf inf";
    stringstream ss2(in2);
    Graph tree_n2_ans(0, ss2);
    Graph task11_ans2 = task11::input(tree_n2, "8");

    QCOMPARE(tree_n2_ans, task11_ans2);
}
void TestTask11::test3(){

    std::string tree_n3 = "1 0 2 0 5 0";
    string in3 = "7 \
        inf 1 1 inf inf 1 inf \
        1 inf inf 1 inf inf inf \
        1 inf inf inf 1 inf inf \
        inf 1 inf inf inf inf inf \
        inf inf 1 inf inf inf inf \
        1 inf inf inf inf inf 1 \
        inf inf inf inf inf 1 inf";
    stringstream ss3(in3);
    Graph tree_n3_ans(0, ss3);
    Graph task11_ans3 = task11::input(tree_n3, "7");
    QCOMPARE(task11_ans3, tree_n3_ans);
}
void TestTask11::test4(){
    std::string tree_n4 = "3 2 1 0";
    string in4 = "5 \
        inf 1 inf inf inf \
        1 inf 1 inf inf \
        inf 1 inf 1 inf \
        inf inf 1 inf 1 \
        inf inf inf 1 inf";

    stringstream ss4(in4);
    Graph tree_n4_ans(0, ss4);
    Graph task11_ans4 = task11::input(tree_n4, "5");

    QCOMPARE(task11_ans4, tree_n4_ans);
}
void TestTask11::star_test(){
    string tree_n5 = "0  0 0 0";
    string in5 = "5 \
        inf 1 1 1 1 \
        1 inf inf inf inf \
        1 inf inf inf inf \
        1 inf inf inf inf \
        1 inf inf inf inf";
    stringstream ss5(in5);
    Graph tree_n5_ans(0, ss5);
    Graph task11_ans5 = task11::input(tree_n5, "5");
    QCOMPARE(task11_ans5, tree_n5_ans);

}
void TestTask11::zero_test(){
    string tree_n6 = "0";
    string in6 = "2 \
        inf 1 \
        1 inf";
    stringstream ss6(in6);
    Graph tree_n6_ans(0, ss6);
    Graph task11_ans6 = task11::input(tree_n6, "2");
    QCOMPARE(tree_n6_ans, task11_ans6);
}

Q_DECLARE_METATYPE(TestTask11)
#include "testtask11.moc"
