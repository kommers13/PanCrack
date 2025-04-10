#include <task7.h>

#include <QTest>

class MyFirstTest1: public QObject
{
    Q_OBJECT

private slots:
    void test1Sum() {
        QCOMPARE(sum(1, 1), 2);
    }
};

Q_DECLARE_METATYPE(MyFirstTest1)
// QTEST_MAIN(MyFirstTest1)
#include "test1.moc"
