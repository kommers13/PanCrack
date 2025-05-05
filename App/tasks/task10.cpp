#include <task10.h>
#include <climits>
using namespace std;

string task10::input(Graph tree) {
    string ans = coding(tree);
    //cout << ans << "\n\n\n";
    return ans;
} // принимаем на вход дерево, затем отправляем в функцию кодирования
string task10::coding(Graph g) {
    /*if(!g.is_tree()){
        cout << "ERROR, Graph isn't a tree";
    }*/
    unordered_map<int, unordered_map<int, int>> uiuii_tree = g.get_graph();
    string ans = "";
    while(uiuii_tree.size() > 2){
        int mini = INT_MAX;
        int point = -1;
        for(const auto& [node, edjes] : uiuii_tree){
            if(edjes.size() == 1 && node < mini){
                mini = node;
                point = edjes.begin()->first;
            }
        }
        //cout << "Удаляем лист: " << mini << ", родитель: " << point << endl;
        ans += to_string(point );
        uiuii_tree.erase(mini);
        // Удаляем ссылку на лист у родителя
        if(uiuii_tree.count(point)) {
            uiuii_tree[point].erase(mini);
        }
    }
    ans += "0";
    return ans;
    // Здесь происходит проверка что это дерево, и дальнейшее кодирование
}
