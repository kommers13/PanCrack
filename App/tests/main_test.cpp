#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "include/testgraph.h"
#include "include/testtask10.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QTest::qExec(new TestGraph);
    QTest::qExec(new TestTask10);
}


