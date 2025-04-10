#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include <test.hpp>
#include <test1.hpp>


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QTest::qExec(new MyFirstTest, argc, argv);
    QTest::qExec(new MyFirstTest1, argc, argv);
}


