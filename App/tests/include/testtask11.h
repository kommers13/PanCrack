#ifndef TESTTASK11_H
#define TESTTASK11_H
#include <QObject>
#include <QTest>
#include <string>
#include <graph.h>
#include <task11.h>

class TestTask11 : public QObject
{
    Q_OBJECT
private slots:

    void lection_test();
    void hard_test();
    void test3();
    void test4();
    void star_test();
    void zero_test();

};

#endif // TESTTASK11_H
