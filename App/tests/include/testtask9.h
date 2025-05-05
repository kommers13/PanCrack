#ifndef TESTTASK9_H
#define TESTTASK9_H

#include <QObject>
#include <QTest>
#include <QDebug>

class TestTask9 : public QObject
{
    Q_OBJECT
private slots:
    void test_floyd_warshall();
};

#endif // TESTTASK9_H
