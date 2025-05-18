#ifndef TESTTASK12_H
#define TESTTASK12_H

#include <QObject>
#include <graph.h>
#include <QTest>
#include <string>
#include <task12.h>
class TestTask12 : public QObject
{
    Q_OBJECT
private slots:
    void test1();
    void problemtest();
    void test20();
    void startest();
    void treetest();
    void squaretest();
    void pantest();
};

#endif // TESTTASK12_H
