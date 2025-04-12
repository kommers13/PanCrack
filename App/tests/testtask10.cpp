#include "include/testtask10.h"
#include <task10.h>

void TestTask10::test_sum(){
    std::string tree_n1 = "5";
    std::string tree_n1_ans = "5";
    std::string task10_ans1 = task10::coding(tree_n1);
    QCOMPARE(task10_ans1, tree_n1_ans);

    std::string tree_n2 = "8";
    std::string tree_n2_ans = "8";
    std::string task10_ans2 = task10::coding(tree_n2);
    QCOMPARE(task10_ans2, tree_n2_ans);
}

Q_DECLARE_METATYPE(TestTask10)
#include "testtask10.moc"
