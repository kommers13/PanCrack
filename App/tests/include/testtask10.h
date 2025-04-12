#ifndef TESTTASK1__H
#define TESTTASK1__H

#include <QObject>

#include <QTest>
#include <string>

class TestTask10 : public QObject
{
    Q_OBJECT

private slots:

    void test_sum();
    //void test_creating_graph();
};

#endif // TESTTASK1__H
