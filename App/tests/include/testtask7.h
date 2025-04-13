#ifndef TESTTASK7_H
#define TESTTASK7_H

#include <QObject>

#include <QTest>

#include <task7.h>

class TestTask7 : public QObject
{
    Q_OBJECT
private slots:

    void test_MST_data();
    void test_MST();
};

#endif // TESTTASK7_H
