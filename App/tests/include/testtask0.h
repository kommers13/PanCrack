#ifndef TESTTASK__H
#define TESTTASK__H

#include <QObject>
#include <iostream>
class TestTask0 : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TESTTASK__H
