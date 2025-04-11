#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "include/testgraph.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QTest::qExec(new TestGraph);
}


