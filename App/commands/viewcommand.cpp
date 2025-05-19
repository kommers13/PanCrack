#include "../include/commands/viewcommand.h"

string ViewCommand::execute(const string& command,
                     const vector<string>& args,
                     const vector<string>& opts) {
    // дефолтная строка, которая говорит о том, что пользователю нужно почитать МАНУАЛ
    string output = "<br>You may input <b>" + command + " --help</b> for more information.";
    // command name
    // description
    // {-h: --help} and so on
    // достаем информацию о команде command из json-файла
    auto com_inf = list_commands::get(command);

    // записываем в переменную описание команды
    string description = get<1>(com_inf);
    // записываем все опции, которые имеет команда
    unordered_map<string, string> got_opts = get<2>(com_inf);

    // если хотя бы один флаг не совпадает, команда НЕ ВЫПОЛНЯЕТСЯ
    for (string opt: opts) {
        // если флаг не найден (ни короткий, ни полный)
        if (got_opts[opt] == "") {
            output = "Flag <b>" + opt + "</b> wasn`t found." + output;
            return output;
        }
    }

    // к этому моменту мы знаем, что если мы оказались здесь, то все опции правильные
    // РАЗРАБОТКА КОМАНДЫ
    // view -h
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return description;
        }

    }


    // view -d GRAPH_NAME degree_vertexes and view -c GRAPH_NAME comps_connect
    if(args.size() == 1 && opts.size() == 1){
        if (opts[0] == "-d" || opts[0] == "--vertex-degree") {
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task0::input(G,"0");
                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> doesn't have vertexs!!!<br>";
                }
                else{
                    return ans;
                }
            }
        }
        if (opts[0] == "-c" || opts[0] == "--connected-components") {
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            if (exist) {
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task0::input(G,"1");
                if(ans == "-1"){
                    return "Graph <b>" + graph_name + "</b> doesn't have components connection!!!<br>";
                }
                else{
                    return "Graph <b>" + graph_name + "</b> has <b>" + ans + "</b> components connection.<br>";
                }

            }
        }
    }




    // view -d -a GRAPH_NAME (флаги можно вводить в любом порядке)
    if(args.size() == 1 && opts.size() == 2){
        string all_ans = "";
        for(auto& op : opts){

            if (op == "-d" || op == "--vertex-degree") {
                string graph_name = args[0];
                bool exist = list_commands::exist_file("graphs", graph_name, ".json");
                // если такой граф существует
                if (exist) {
                    // создаем граф из JSON-файла
                    Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                    string ans = task0::input(G,"0");
                    if(ans == ""){
                        all_ans += ("Graph <b>" + graph_name + "</b> doesn't have vertexs!!!<br>");
                    }
                    else{
                        all_ans += (ans + "<br>");
                    }
                }
            }
            if (op == "-c" || op == "--connected-components") {
                string graph_name = args[0];
                bool exist = list_commands::exist_file("graphs", graph_name, ".json");
                if (exist) {
                    Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                    string ans = task0::input(G,"1");
                    if(ans == "-1"){
                        all_ans += ("Graph <b>" + graph_name + "</b> doesn't have components connection!!!<br>");
                    }
                    else{
                        all_ans += ("Graph <b>" + graph_name + "</b> has <b>" + ans + "</b> components connection.<br>");
                    }

                }
            }

        }
        return all_ans;

    }


    // сообщение пользователю об ошибках,
    // либо просто сказать ему, что он неправильно использовал команду и попросить
    // ПОЧИТАТЬ МАНУАЛ
    return "Usage of command <b>view</b> is incorrect." + output;

}
