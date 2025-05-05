#include "include/task4.h"
using namespace std;
// Обход в ширину - алгоритм похожий на розжиг огня то и есть волнами идёт
string task4::BFS(const Graph &g, const int &start_edge){
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
            bfs_ans += "->";
        }
    }
    //cout << bfs_ans;
    return bfs_ans;
}
// парсинг ответов - чтобы лишние пробелы у пользователя не помешали решению программы
string task4::parse(string& s){
    string s_parse = "";
    for(char& c : s){
        if(c == ' ') s_parse += c;
        else if(c < '0' && c > '9' || c != '-' || c != '>')
            return "Error input, input must be: 'start vertex -> vertex -> ... -> end vertex'";
    }
    return s_parse;
}
// метод для создания рандомного графа - надо вынести в граф
Graph task4::rand(int vers){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::vector<std::vector<int>> matrix(vers, std::vector<int>(vers, 0));
    // Заполняем матрицу случайными значениями
    for (int i = 0; i < vers; ++i) {
        for (int j = i + 1; j < vers; ++j) {
            matrix[i][j] = matrix[j][i] = dis(gen);
        }
    }
    // Гарантируем связность графа
    for (int i = 1; i < vers; ++i) {
        matrix[i-1][i] = matrix[i][i-1] = 1;
    }

    return Graph(matrix);

}
bool task4::input(string user_input, string start_edge, Graph rand_g) {
    string as = "You're not right, Mr.Panteleev's very angry!!!";
    bool flag = false;
    string ans = task4::BFS(rand_g, stoi(start_edge));
    user_input = parse(user_input);
    ans = parse(ans);
    if(ans == user_input){
        flag = true;
        as = "You're right, Mr.Panteleev proud for you!";
    }
    //cout <<'\n'<<as << "\n\n";
    return flag;
}
