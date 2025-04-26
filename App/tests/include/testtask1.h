#ifndef TESTTASK1_H
#define TESTTASK1_H

#include <QObject>
#include <QTest>

class TestTask1 : public QObject
{
    Q_OBJECT
private slots:
    void test_DFS();
};

#endif // TESTTASK1_H
