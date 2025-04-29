#include "include/task3.h"
using namespace std;
string task3::input(const Graph g, const string s_e){
    string ans = "";
    int start_edge = stoi(s_e);
    ans = task3::BFS(g, start_edge);
    
    return ans;
}

string task3::BFS(const Graph &g, const int &start_edge){
    if(g.get_cnt_edges() == 0){
        return "0";
    }
    if(g.get_cnt_vertexes() <= start_edge || 0 > start_edge){
        return "ERROR: start edge out of range";
    }
    string bfs_ans = "";
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    int n = g.get_cnt_edges();
    vector<bool> visited(n, false);
    queue<int> que_edges;
    que_edges.push(start_edge);
    visited[start_edge] = true;
    while(!que_edges.empty()){
        int edge = que_edges.front();
        que_edges.pop();
        bfs_ans += to_string(edge);
        if(uiuii_graph.count(edge)){
            for(auto& [ed, pii] : uiuii_graph[edge]){
                if(visited[ed] == false){
                    que_edges.push(ed);
                    visited[ed] = true;
                }
            }
        }
        if(que_edges.size() != 0){
            bfs_ans += " -> ";
        }
    }
    //cout << bfs_ans;
    return bfs_ans;
}
