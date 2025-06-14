#include "hamilton.h"


vector<int> status;

int v_start;

vector<int> chain;

int cnt;

vector<string> chains;


// от одной стартовой вершины
void hamilton_cycles_from_start(const Graph& G,
                                int k,
                                int v_cur) {
    auto graph = G.get_graph();

    for (auto [ neighbour, _ ]: graph[v_cur]) {

        if (status[neighbour]) {
            continue;
        }

        if (k == graph.size() - 1 && graph[neighbour].find(v_start) != graph[neighbour].end()) {

            auto names = G.get_vs_name();

            string chain_s = "";

            for (int i = 0; i < chain.size() - 1; i++) {
                chain_s += names[chain[i]];
                chain_s += "->";
            }
            chain_s += names[neighbour];
            chain_s += "->";
            chain_s += names[v_start];
            chains.push_back(chain_s);
        }
        else {
            status[neighbour] = 1;
            chain[k] = neighbour;
            hamilton_cycles_from_start(G, k + 1, neighbour);
            status[neighbour] = 0;
            // chain[k] = -1;
        }
    }
}

vector<string> hamilton::hamilton_cycles(const Graph& G) {

    chains.resize(0);

    cnt = 0;

    status = vector<int>(G.get_cnt_vertexes(), 0);

    v_start = 0;

    status[v_start] = 1;

    chain = vector<int>(G.get_cnt_vertexes(), -1);

    chain[0] = v_start;

    hamilton_cycles_from_start(G, 1, v_start);

    return chains;
}
