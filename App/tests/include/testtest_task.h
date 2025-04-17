#ifndef TESTTEST_TASK_H
#define TESTTEST_TASK_H

#include <QObject>

#include <QTest>


class TestTest_Task : public QObject
{
    Q_OBJECT

private slots:

    void test_code();
    //void test_creating_graph();
};

#endif // TESTTEST_TASK_H
