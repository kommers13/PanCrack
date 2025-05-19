#include <task4.h>
using namespace std;
string task4::BFS(const Graph &g, const int &start_edge) {
    vector<char> vc = g.get_vs_name();
    // Проверка на пустой граф (лучше проверять вершины, а не рёбра)
    if(g.get_cnt_vertexes() == 0) {
        return "0";
    }

    // Проверка корректности стартовой вершины
    if(start_edge < 0 || start_edge >= g.get_cnt_vertexes()) {
        return "ERROR: start edge out of range";
    }

    string bfs_ans;
    const auto& graph = g.get_graph(); // избегаем копирования
    vector<bool> visited(g.get_cnt_vertexes(), false);
    queue<int> que_edges;

    que_edges.push(start_edge);
    visited[start_edge] = true;

    while(!que_edges.empty()) {
        int edge = que_edges.front();
        que_edges.pop();

        // Добавляем разделитель, если строка не пустая
        if(!bfs_ans.empty()) {
            bfs_ans += ","; // используем запятую как разделитель
        }
        bfs_ans += vc[edge];

        // Проверка наличия вершины в графе
        auto it = graph.find(edge);
        if(it != graph.end()) {
            for(const auto& [ed, pii] : it->second) {
                if(!visited[ed]) {
                    que_edges.push(ed);
                    visited[ed] = true;
                }
            }
        }
    }

    return bfs_ans;
}

string task4::parse(string& s) {
    string s_parse;
    s_parse.reserve(s.length());

    for(char c : s) {
        // Разрешаем цифры и запятые
        if((c >= 'A' && c <= 'Z')) {
            s_parse += c;
        }
    }

    // Удаляем возможные лишние запятые в начале/конце
    if(!s_parse.empty() && s_parse.front() == ',') {
        s_parse.erase(0, 1);
    }
    if(!s_parse.empty() && s_parse.back() == ',') {
        s_parse.pop_back();
    }

    return s_parse;
}

string task4::input(string user_input, string start_edge, Graph g) {
    // Безопасное преобразование строки в число
    int start = char(start_edge[0]) - 65;

    // Проверка на некорректный ввод (atoi вернет 0 для нечисловых строк)

    string ans = BFS(g, start);

    // Парсим ввод и результат
    user_input = parse(user_input);
    ans = parse(ans);
    // Сравниваем результаты
    return (ans == user_input)
               ? "You're right, Mr.Panteleev is proud of you!"
               : "You're not right, Mr.Panteleev is very angry!!!";
}
