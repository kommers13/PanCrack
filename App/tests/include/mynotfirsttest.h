#ifndef MYNOTFIRSTTEST_H
#define MYNOTFIRSTTEST_H

#include <QObject>

#include <QTest>

class MyNotFirstTest: public QObject
{
    Q_OBJECT

private slots:
    // void initTestCase() {
    //     qDebug("Called before everything else.");
    // }

    // void myFirstTest() {
    //     QVERIFY(true); // check that a condition is satisfied
    //     QCOMPARE(1, 1); // compare two values
    // }

    // void mySecondTest() {
    //     QVERIFY(myCondition());
    //     QVERIFY(sum(1, 2) != 2);
    // }

    void testSum();
    // void cleanupTestCase() {
    //     qDebug("Called after myFirstTest and mySecondTest.");
    // }
};

#endif // MYNOTFIRSTTEST_H
