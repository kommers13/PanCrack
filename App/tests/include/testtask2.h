#ifndef TESTTASK2_H
#define TESTTASK2_H

namespace task2 {

#include <QObject>
#include <QTest>
#include <vector>

class TestTask2 : public QObject
{
    Q_OBJECT
private slots:
    void test_DFS();
    void test_check_user_DFS();
    void test_generate_random_graph();
};

#endif // TESTTASK2_H
