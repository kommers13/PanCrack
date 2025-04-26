#ifndef TESTTASK1__H
#define TESTTASK1__H

#include <QObject>
#include <QTest>
#include <string>
#include <graph.h>
#include <task10.h>


class TestTask10 : public QObject
{
    Q_OBJECT

private slots:

    void lection_test();
    void very_hard_test();
    void typical_test();
    void eight_test();
    void list_test();
    void trivial_test();
    void star_test();
};

#endif // TESTTASK1__H
