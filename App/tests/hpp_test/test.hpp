#include <task7.h>

#include <QTest>

class MyFirstTest: public QObject
{
    Q_OBJECT

private:
    bool myCondition()
    {
        return true;
    }

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

    void testSum() {
        QCOMPARE(sum(254, 666), 920);
    }

    // void cleanupTestCase() {
    //     qDebug("Called after myFirstTest and mySecondTest.");
    // }
};

Q_DECLARE_METATYPE(MyFirstTest)
#include "test.moc"
