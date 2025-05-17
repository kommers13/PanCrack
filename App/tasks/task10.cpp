#include <task10.h>
#include <climits>
using namespace std;

string task10::input(Graph tree) {
    string ans = coding(tree);
    //cout << ans << "\n\n\n";
    return ans;
} // принимаем на вход дерево, затем отправляем в функцию кодирования
string task10::coding(Graph g) {
    // Проверка что граф является деревом
    if((g.get_cnt_edges() + 1) != g.get_cnt_vertexes()){
        return "-1"; // Не дерево
    }

    unordered_map<int, unordered_map<int, int>> uiuii_tree = g.get_graph();
    string ans = "";

    // Пока в дереве больше 2 вершин
    while(uiuii_tree.size() > 2){
        int min_leaf = INT_MAX;
        int parent = -1;

        // Ищем лист с минимальным номером
        for(const auto& [node, edges] : uiuii_tree){
            if(edges.size() == 1){  // Это лист
                if(node < min_leaf){
                    min_leaf = node;
                    parent = edges.begin()->first; // Сосед листа
                }
            }
        }

        // Если не нашли лист - что-то пошло не так
        if(min_leaf == INT_MAX){
            return "-1"; // Ошибка - цикл в графе
        }

        ans += to_string(parent); // Добавляем родителя в код

        // Удаляем лист из дерева
        uiuii_tree.erase(min_leaf);

        // Удаляем ссылку на лист у родителя
        if(uiuii_tree.count(parent)) {
            uiuii_tree[parent].erase(min_leaf);

            // Если родитель стал листом, проверим его на следующей итерации
        }
    }

    // ans += "0";

    // Удаляем последний пробел, если он есть
    if(!ans.empty() && ans.back() == ' '){
        ans.pop_back();
    }

    return ans += "0";
}
