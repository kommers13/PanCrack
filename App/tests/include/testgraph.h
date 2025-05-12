#ifndef TESTGRAPH_H
#define TESTGRAPH_H

#include <QObject>

#include <QTest>

#include <graph.h>

#include <exception>

class TestGraph : public QObject
{
    Q_OBJECT

private slots:

    void test_creating_graph_data();
    void test_creating_graph();

    void test_creating_graph_inc_data();
    void test_creating_graph_inc();

    void test_creating_graph_ladj_data();
    void test_creating_graph_ladj();

    void test_undirected_graph_data();
    void test_undirected_graph();

    void test_add_vertex_data();
    void test_add_vertex();

    void test_add_edge_data();
    void test_add_edge();

    void test_get_edges_data();
    void test_get_edges();

    void test_get_degree_data();
    void test_get_degree();

    void test_equal_data();
    void test_equal();

};

#endif // TESTGRAPH_H
