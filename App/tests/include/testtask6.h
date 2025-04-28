#ifndef TESTTASK6_H
#define TESTTASK6_H

#include <QObject>
#include <QTest>

class TestTask6 : public QObject {
    Q_OBJECT
private slots:
    void test_graph_generation();
    void test_answer_checking();
};

#endif // TESTTASK6_H
