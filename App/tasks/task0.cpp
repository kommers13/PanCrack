#include "task0.h"
using namespace std;
string task0::input(Graph g, string choice){
    int ch = stoi(choice);
    switch(ch)
    {
    case 0:
        // степени вершин
        return task0::check_deg(g);
    case 1:
        // количество компонент связности
        return task0::cnt_comp_connect(g);

    case 2:
        // проверяем на эйлеровый граф
        return task0::if_eulers_graph(g);

    case 3:
        // проверяем на двудольность
        return task0::if_bipart_graph(g);
    }
    return "empty choice";

}
string task0::check_deg(Graph g){
    string ans = "No, current Graph doesn't have vertexs!!!";
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    string n_ans = "";
    for(auto& [ver, _] : uiuii_graph){
        n_ans += (to_string(g.get_v_degree(ver))+ " :" + to_string(ver) + "\n");
    }
    reverse(n_ans.begin(), n_ans.end());
    ans = n_ans;
    return ans;
}
string task0::cnt_comp_connect(Graph g){
    string ans = "Current Graph doesn't have component connection!!!";
    std::unordered_set<int> visited;
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    int components = 0;

    for (const auto& [ver, _] : uiuii_graph) {
        if (visited.find(ver) == visited.end()) {
            stack<int> stack;
            stack.push(ver);
            visited.insert(ver);
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();
                for (const auto& [neighbor, _] : uiuii_graph[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        stack.push(neighbor);
                    }
                }
            }
            components++;
        }
    }
    if(components != 0)
        ans = "Graph has component connection " + to_string(components);
    return ans;
}
string task0::if_eulers_graph(Graph g){
    string ans = "No, current Graph isn't Eulers graph";
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    int cnt = 0;
    for(auto& [ver, _] : uiuii_graph){
        if(g.get_v_degree(ver) % 2 == 0){
            cnt++;
        }
    }
    if(cnt == g.get_cnt_edges()) ans = "Yes, current Graph is Eulers graph";
    else if(cnt == (g.get_cnt_edges() - 2)) ans = "Yes, current Graph is half Eulers graph";

    return ans;
}
string task0::if_bipart_graph(Graph g){
    string ans = "No, current Graph isn't bipart graph";
    string tt = task12::input(g);
    istringstream iss(tt);
    string word;
    set<string> s;
    while (iss >> word) {
        s.insert(word);
    }
    if(s.size() == 2) ans = "Yes, current Graph is bipart graph";
    return ans;
}
