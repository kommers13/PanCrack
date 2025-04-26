#include "include/testtask11.h"
typedef unordered_map<int, unordered_map<int, int>> uniunii;
using namespace std;
void TestTask11::lection_test(){

    string tree_n1 = "0110";
    string in1 = "5 \
        inf 1 1 inf inf \
        1 inf inf 1 1 \
        1 inf inf inf inf \
        inf 1 inf inf inf \
        inf 1 inf inf inf ";
    stringstream ss1(in1);
    Graph tree_n1_ans(0, ss1);
    Graph task11_ans1 = task11::input(tree_n1, "01234");
    QCOMPARE(task11_ans1, tree_n1_ans);
}
void TestTask11::hard_test(){
    string tree_n2 = "0001110";
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
    Graph task11_ans2 = task11::input(tree_n2, "01234567");
    QCOMPARE(task11_ans2, tree_n2_ans);
}
    /*
    std::string tree_n3_ans = "010220";
    string in3 = "7 \
        inf 1 1 1 inf inf inf \
        1 inf inf 1 inf inf inf \
        1 inf inf inf 1 1 inf \
        1 inf inf inf inf inf inf \
        inf 1 inf inf inf inf inf \
        inf inf 1 inf inf inf inf \
        inf inf 1 inf inf inf inf";
    stringstream ss3(0, in3);
    Graph tree_n3(ss3);
    std::string task10_ans3 = task10::input(tree_n3);
    QCOMPARE(task10_ans3, tree_n3_ans);

    std::string tree_n4_ans = "0146410";
    string in4 = "8 \
        inf 1 1 inf inf inf inf inf inf \
        1 inf inf 1 1 inf inf inf inf \
        1 inf inf inf inf inf inf inf \
        inf 1 inf inf inf inf inf inf \
        inf 1 inf inf inf 1 1 inf inf \
        inf inf inf inf 1 inf inf inf \
        inf inf inf inf 1 inf inf inf 1 \
        inf inf inf inf inf inf 1 inf";
    stringstream ss4(0, in4);
    Graph tree_n4(ss4);
    std::string task10_ans4 = task10::input(tree_n4);
    QCOMPARE(task10_ans4, tree_n4_ans);

    std::string tree_n5 = "3210";
    string in5 = "5 \
        inf 1 inf inf inf \
        1 inf 1 inf inf \
        inf 1 inf 1 inf inf\
        inf inf inf inf 1";

    stringstream ss5(in5);
    Graph tree_n5_ans(0, ss5);
    Graph task11_ans5 = task11::input(tree_n5, "01234");
    QCOMPARE(task11_ans5, tree_n5_ans);
*/

Q_DECLARE_METATYPE(TestTask11)
#include "testtask11.moc"
