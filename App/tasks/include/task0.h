#ifndef TASK0_H
#define TASK0_H
#include <graph.h>
#include <iostream>
#include <algorithm>
class task0
{
public:
    void input(Graph g, string choose);
    string check_deg(Graph g);
    string cnt_comp_connect(Graph g);
    string if_eulers_graph(Graph g);
    string if_bipart_graph(Graph g);

};

#endif // TASK0_H
