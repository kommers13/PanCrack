#include "include/testtask10.h"
<<<<<<< HEAD
typedef unordered_map<int, unordered_map<int, int>> uniunii;
using namespace std;
void TestTask10::test_code(){

    string tree_n1_ans = "0110";
    string in1 = "5 \
                 inf 1 1 inf inf \
                 1 inf inf 1 1 \
                 1 inf inf inf inf \
                 inf 1 inf inf inf \
                 inf 1 inf inf inf ";
    stringstream ss1(in1);
    Graph tree_n1(ss1);
    std::string task10_ans1 = task10::input(tree_n1);
    QCOMPARE(task10_ans1, tree_n1_ans);

    std::string tree_n2_ans = "0001110";
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
    Graph tree_n2(ss2);
    std::string task10_ans2 = task10::input(tree_n2);
    QCOMPARE(task10_ans2, tree_n2_ans);
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
    stringstream ss3(in3);
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
    stringstream ss4(in4);
    Graph tree_n4(ss4);
    std::string task10_ans4 = task10::input(tree_n4);
    QCOMPARE(task10_ans4, tree_n4_ans);
    */
    std::string tree_n5_ans = "3210";
    string in5 = "5 \
        inf 1 inf inf inf \
        1 inf 1 inf inf \
        inf 1 inf 1 inf inf\
        inf inf inf inf 1";

    stringstream ss5(in5);
    Graph tree_n5(ss5);
    std::string task10_ans5 = task10::input(tree_n5);
    QCOMPARE(task10_ans5, tree_n5_ans);
=======


void TestTask10::test_code_data() {
    // INIT DATA

    // TEST 1
    std::string tree_n1 = "5";
    std::string tree_n1_ans = "1221";

    // TEST 2
    std::string tree_n2 = "8";
    std::string tree_n2_ans = "233124";
    // END INIT DATA

    QTest::addColumn<std::string>("tree");
    QTest::addColumn<std::string>("code");

    QTest::addRow("prufer 1") << tree_n1 << tree_n1_ans;
    QTest::addRow("prufer 2") << tree_n2 << tree_n2_ans;
}

void TestTask10::test_code(){

    QFETCH(std::string, tree);
    QFETCH(std::string, code);
    QCOMPARE(task10::coding(tree), code);

>>>>>>> origin/main
}

Q_DECLARE_METATYPE(TestTask10)
#include "testtask10.moc"
