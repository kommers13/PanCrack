#include <task10.h>
#include <climits>
using namespace std;

string task10::input() {
    string n;
    cout << "\nINPUT n vars for code Prufers: ";
    cin >> n;
    string ans = task10::coding(n);
    cout << "ANSWER: " << ans << '\n' << '\n';
    return ans;
}
string task10::coding(string n) {

    int nodes = stoi(n);
    if(nodes <= 0) return "Invalid input";
    map<int, pair<int, int>> tree = task10::buildTreeMap(nodes);
    string answer = "";
    task10::printTreeMap(tree, nodes);
    //answer = task10::rec_code(tree, answer);
    return answer;


}
string task10::rec_code(map<int, pair<int, int>>& tree, string& answer) {
    if(tree.size() <= 1) {
        return answer;
    }

    // 1. Находим минимальный лист
    int mini = INT_MAX;

    // Сначала собираем все листья
    for(const auto& [node, children] : tree) {
        if(children.first == 0 && children.second == 0) {
            if(node < mini) mini = node;
        }
    }

    // 2. Находим родителя и обновляем дерево
    for(auto it = tree.begin(); it != tree.end(); ++it) {
        auto& [parent, children] = *it;

        if(children.first == mini) {
            answer += to_string(parent);
            children.first = 0;
            tree.erase(mini);
            break;
        }
        else if(children.second == mini) {
            answer += to_string(parent);
            children.second = 0;
            tree.erase(mini);
            break;
        }

    }
    cout << answer << '\n';
    // 3. Рекурсивный вызов
    return task10::rec_code(tree, answer);
}



map<int, pair<int, int>> task10::buildTreeMap(int n) {
    map<int, pair<int, int>> tree;

    for(int i = 1; i <= n; i++) {
        int left = 2 * i;
        int right = 2 * i + 1;
        pair<int, int> children = {0, 0};

        if(left <= n) children.first = left;
        if(right <= n) children.second = right;

        if(children.first != 0 || children.second != 0) {
            tree[i] = children;
        }
    }

    return tree;
}
void task10::printTreeMap(const map<int, pair<int, int>>& tree, int n) {
    cout << "Представление дерева в виде map рёбер:" << endl;
    cout << "Узел -> (Левый потомок, Правый потомок)" << endl;

    for (int i = 1; i <= n; i++) {
        if (tree.find(i) != tree.end()) {
            cout << i << " -> (" << tree.at(i).first << ", " << tree.at(i).second << ")" << endl;
        } else {
            cout << i << " -> (лист)" << endl;
        }
    }
}
