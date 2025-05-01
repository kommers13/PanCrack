#ifndef TESTTASK3_H
#define TESTTASK3_H

#include <QObject>
#include <QTest>
#include <string>
#include <sstream>
#include <graph.h>
#include <iostream>
#include <task3.h>
class TestTask3 : public QObject
{
    Q_OBJECT
private slots:
    void test1_BFS();
    void test2_BFS();
    void test3_BFS();
    void test4_BFS();
    void test5_BFS();
    void test6_BFS();
    void test7_BFS();
};

#endif // TESTTASK3_H
