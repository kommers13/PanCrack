#ifndef TESTTASK__H
#define TESTTASK__H

#include <QObject>
#include <QTest>
#include <iostream>
#include <string>
#include <task0.h>
#include <graph.h>
class TestTask0 : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TESTTASK__H
