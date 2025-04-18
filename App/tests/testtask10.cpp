#include "include/testtask10.h"


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

}

Q_DECLARE_METATYPE(TestTask10)
#include "testtask10.moc"
