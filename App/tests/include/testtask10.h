#ifndef TESTTASK1__H
#define TESTTASK1__H

#include <QObject>
#include <QTest>
#include <string>
#include <graph.h>
#include <task10.h>

#include <task10.h>

class TestTask10 : public QObject
{
    Q_OBJECT

private slots:

    void test_code_data();
    void test_code();
    //void test_creating_graph();
};

#endif // TESTTASK1__H
