// testtask8.h
#ifndef TESTTASK8_H
#define TESTTASK8_H

#include <QObject>
#include <QTest>

class TestTask8 : public QObject
{
    Q_OBJECT
private slots:
    void test_dijkstra();
};

#endif // TESTTASK8_H
