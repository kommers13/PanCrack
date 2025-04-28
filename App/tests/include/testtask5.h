#ifndef TESTTASK5_H
#define TESTTASK5_H

#include <QObject>
#include <QTest>

class TestTask5 : public QObject
{
    Q_OBJECT
private slots:
    void test_connected_components();
};

#endif // TESTTASK5_H
