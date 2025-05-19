#include "include/task3.h"
using namespace std;
string task3::input(const Graph g, const string s_e){
    string ans = "";
    int start_edge = s_e[0]-65;
    ans = task3::BFS(g, start_edge);

    return ans;
}

string task3::BFS(const Graph &g, const int &start_edge) {
    if(g.get_cnt_edges() == 0) {
        return "";
    }
    if(g.get_cnt_vertexes() <= start_edge || 0 > start_edge) {
        return "";
    }

    std::stringstream bfs_ss;
    std::stringstream wave_ss;
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    int n = g.get_cnt_vertexes();
    vector<bool> visited(n, false);
    queue<int> que_edges;
    vector<char> vc = g.get_vs_name();

    que_edges.push(start_edge);
    visited[start_edge] = true;
    int current_level = 0;

    wave_ss << "BFS by levels:<br>";
    vector<vector<char>> levels; // Для хранения вершин по уровням

    while(!que_edges.empty()) {
        int level_size = que_edges.size();
        wave_ss << "level " << current_level << ": ";
        vector<char> current_level_nodes;

        for(int i = 0; i < level_size; ++i) {
            int edge = que_edges.front();
            que_edges.pop();

            // Сохраняем вершину текущего уровня
            current_level_nodes.push_back(vc[edge]);

            // Добавляем в общий порядок BFS
            bfs_ss << "<b>" << vc[edge] << "</b>";
            if(!que_edges.empty() || i != level_size - 1) {
                bfs_ss << " → ";
            }

            // Добавляем в вывод по уровням
            wave_ss << "<b>" << vc[edge] << "</b>";
            if(i != level_size - 1) {
                wave_ss << ", ";
            }

            // Добавляем соседей в очередь
            if(uiuii_graph.count(edge)) {
                for(auto& [ed, pii] : uiuii_graph[edge]) {
                    if(visited[ed] == false) {
                        que_edges.push(ed);
                        visited[ed] = true;
                    }
                }
            }
        }

        levels.push_back(current_level_nodes);
        wave_ss << "<br>";
        current_level++;
    }

    std::stringstream final_order_levels;
    for (size_t i = 0; i < levels.size(); ++i) {
        for (size_t j = 0; j < levels[i].size(); ++j) {
            final_order_levels << "<b>" << levels[i][j] << "</b>";
            if (j != levels[i].size() - 1) {
                final_order_levels << " → ";
            }
        }
        if (i != levels.size() - 1) {
            final_order_levels << " → ";
        }
    }

    wave_ss << "<br>Final BFS order:<br>" << final_order_levels.str() << "<br>";

    return wave_ss.str();
}
