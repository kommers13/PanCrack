#ifndef TESTGRAPH_H
#define TESTGRAPH_H

#include <QObject>

#include <QTest>


class TestGraph : public QObject
{
    Q_OBJECT

private slots:

    void test_creating_graph_data();
    void test_creating_graph();
};

#endif // TESTGRAPH_H
