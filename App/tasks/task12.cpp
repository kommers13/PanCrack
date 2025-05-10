#include "include/task12.h"
using namespace std;
string task12::input(Graph g) {
    return coloring(g);
}
string task12::coloring(Graph& g){
    map<int, string> colors{{0, "Transparent"}, {1, "#FF0000"}, {2, "#FFFF00"}, {3, "#00BFFF"},
    {4, "#00FF00"}, {5, "#F0E68C"}, {6, "#EE82EE"}, {7, "#DEB887"}, {8, "#808000"},
    {9, "#B0E0E6"}, {10, "#FFE4E1"}, {11, "#A9A9A9"}, {12, "#F08080"}, {13, "#C71585"}, {14, "#FFA500"}, {15, "#BDB76B"},
    {16, "#4B0082"}, {17, "#BC8F8F"}, {18, "#7FFFD4"}, {19, "#008B8B"}, {20, "#800000"},  {21, "#8B4513"}};
    string ans = "";
    int v_cnt = g.get_cnt_vertexes();
    vector<int> color(v_cnt, -1);
    vector<int> sat(v_cnt, 0);
    vector<int> degree(v_cnt);
    unordered_map<int, unordered_map<int, int>> uiuii_graph = g.get_graph();
    for (int i = 0; i < v_cnt; ++i) {
        degree[i] = g.get_v_degree(i);
    }
    for (int step = 0; step < v_cnt; ++step) {
        // Выбираем вершину с максимальной насыщенностью (если их несколько — с максимальной степенью)
        int maxSat = -1, selected = -1;
        for (int i = 0; i < v_cnt; ++i) {
            if (color[i] == -1) { // Если вершина ещё не раскрашена
                if (sat[i] > maxSat || (sat[i] == maxSat && degree[i] > degree[selected])) {
                    maxSat = sat[i];
                    selected = i;
                }
            }
        }
        if (selected == -1) break;
        set<int> usedColors;
        for (auto& [a, _] : uiuii_graph[selected]) {
            if (color[a] != -1) {
                usedColors.insert(color[a]);
            }
        }

        int newColor = 1;
        while (usedColors.count(newColor)) {
            newColor++;
        }

        color[selected] = newColor;

        // Обновляем насыщенность соседей
        for (auto& [a, _] : uiuii_graph[selected]) {
            if (color[a] == -1) {
                bool colorIsNew = true;
                for (auto& [d, _] : uiuii_graph[a]){
                    if (color[d] == newColor) {
                        colorIsNew = false;
                        break;
                    }
                }
                if (colorIsNew) {
                    sat[a]++;
                }
            }
        }
    }
    for(auto& el : color){
        ans += colors[el];
        ans += " ";
    }


    return ans;
}
