#ifndef TESTTASK4_H
#define TESTTASK4_H

#include <QObject>
#include <QTest>
#include <unordered_map>
#include <graph.h>
#include <string>
#include <sstream>
#include <task4.h>
class TestTask4 : public QObject
{
    Q_OBJECT
private slots:
    void test1();
    void test2();
    void test3();
    void test4();
};

#endif // TESTTASK4_H
