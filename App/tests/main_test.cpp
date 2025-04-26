#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "include/testgraph.h"
#include "include/testtask0.h"
#include "include/testtask1.h"
#include "include/testtask7.h"
#include "include/testtask10.h"
#include "include/testtask11.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QStringList args;
    // args << " " << "-o" << "testlog.xml,xml";
    QTest::qExec(new TestGraph, args);
    QTest::qExec(new TestTask0);
    QTest::qExec(new TestTask1);
    QTest::qExec(new TestTask7);
    QTest::qExec(new TestTask10);
    QTest::qExec(new TestTask11);
}


