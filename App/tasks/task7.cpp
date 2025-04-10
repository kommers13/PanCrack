#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>


using namespace std;


// как представлять графы


const int inf = 1e9;

class Graph {

    /* A: (B, 1), (C, -2)
       B: (A, 1), (C, 3), (D, 5)
       C: (B, 3), (A, -2)
       D: (B, 5), (E, 10), (G, 7)
       E: (D, 10), (F, 0)
       F: (G, 8), (E, 0)
       G: (D, 7), (F, 8)
    */

    // множество вершин (по умолчанию называются буквами алфавита A, B, C и т. д.
    vector<char> vs;
    unordered_map<int, unordered_map<int, int>> graph;

public:
    // матрица смежности
    Graph(const vector<vector<int>>& madj) : vs(madj.size()) {
        for (int i = 0; i < madj.size(); i++) {

            vs[i] = (char)(i + 'A');

            unordered_map<int, int> neighbours;

            for (int j = 0; j < madj.size(); j++) {

                if (i != j && madj[i][j] != inf) {   // чтобы не дублировать ребра тип I -- I
                    neighbours[j] = madj[i][j];
                }
            }
            graph[i] = neighbours;
        }
    }

    // чтение из файла с матрицей смежности
    Graph(const string& file) {

    }

    void print() {
        cout << "Graph " << this << '\n';
        for (auto key: graph) {

            cout << vs[key.first] << ": ";

            for (auto neighbour: key.second) {
                cout << "(" << vs[neighbour.first] << ", " << neighbour.second << "); ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
};


void test() {
    // A B C D E
    // inf, т. е. все ребер меньше inf
    vector<vector<int>> madj = {
        {0, 3, inf, inf, -2},
        {3, 0, 5, inf, 4},
        {inf, 5, 0, 10, inf},
        {inf, inf, 10, 0, 6},
        {-2, 0, inf, 6, 0},
                                };
    Graph G = Graph(madj);
    G.print();
}

int main() {
    test();
}
