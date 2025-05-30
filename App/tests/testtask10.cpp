#include "include/testtask10.h"
typedef unordered_map<int, unordered_map<int, int>> uniunii;
using namespace std;
void TestTask10::lection_test(){
    // LECTION TEST
    string tree_n1_ans = "0110";
    string in1 = "5 \
                 inf 1 1 inf inf \
                 1 inf inf 1 1 \
                 1 inf inf inf inf \
                 inf 1 inf inf inf \
                 inf 1 inf inf inf ";
    stringstream ss1(in1);
    Graph tree_n1(0, ss1);
    string task10_ans1 = task10::input(tree_n1);
    QCOMPARE(task10_ans1, tree_n1_ans);
}
void TestTask10::very_hard_test(){
    // VERY HARD TEST
    string tree_n2_ans = "0001110";
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
    Graph tree_n2(0, ss2);
    string task10_ans2 = task10::input(tree_n2);
    QCOMPARE(task10_ans2, tree_n2_ans);
}
void TestTask10::typical_test(){
    // MEDIUM TEST
    std::string tree_n3_ans = "331020";
    string in3 = "7 \
        inf 1 1 inf inf inf inf \
        1 inf inf 1 inf inf inf \
        1 inf inf inf inf inf 1 \
        inf 1 inf inf 1 1 inf \
        inf inf inf 1 inf inf inf \
        inf inf inf 1 inf inf inf \
        inf inf 1 inf inf inf inf";
    stringstream ss3(in3);
    Graph tree_n3(0, ss3);
    std::string task10_ans3 = task10::input(tree_n3);
    QCOMPARE(task10_ans3, tree_n3_ans);
}
void TestTask10::eight_test(){
    // HARD TEST
    std::string tree_n4_ans = "0114460";
    string in4 = "8 \
        inf 1 1 inf inf inf inf inf \
        1 inf inf 1 1 inf inf inf \
        1 inf inf inf inf inf inf inf\
        inf 1 inf inf inf inf inf inf \
        inf 1 inf inf inf 1 1 inf \
        inf inf inf inf 1 inf inf inf \
        inf inf inf inf 1 inf inf 1 \
        inf inf inf inf inf inf 1 inf";
    stringstream ss4(in4);
    Graph tree_n4(0, ss4);
    std::string task10_ans4 = task10::input(tree_n4);
    QCOMPARE(task10_ans4, tree_n4_ans);
}
void TestTask10::list_test(){
    // LIST TEST
    string tree_n5_ans = "120";
    string in5 = "4 \
        inf 1 inf inf \
        1 inf 1 inf \
        inf 1 inf 1 \
        inf inf 1 inf";

    stringstream ss5(in5);
    Graph tree_n5(0, ss5);
    string task10_ans5 = task10::input(tree_n5);
    QCOMPARE(task10_ans5, tree_n5_ans);
}
void TestTask10::trivial_test(){
    // TRIVIAL TEST
    string tree_n6_ans = "0";
    string in6 = "1 \
        1";

    stringstream ss6(in6);
    Graph tree_n6(0, ss6);
    string task10_ans6 = task10::input(tree_n6);
    QCOMPARE(task10_ans6, tree_n6_ans);
}
void TestTask10::star_test(){
    // TEST STAR
    string tree_n7_ans = "0000";
    string in7 = "5 \
        inf 1 1 1 1 \
        1 inf inf inf inf \
        1 inf inf inf inf \
        1 inf inf inf inf \
        1 inf inf inf inf";
    stringstream ss7(in7);
    Graph tree_n7(0, ss7);
    string task10_ans7 = task10::input(tree_n7);
    QCOMPARE(task10_ans7, tree_n7_ans);
}

Q_DECLARE_METATYPE(TestTask10)
#include "testtask10.moc"
