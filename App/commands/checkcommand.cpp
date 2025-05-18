#include "../include/commands/checkcommand.h"

string CheckCommand::execute(const string& command,
                         const vector<string>& args,
                         const vector<string>& opts) {
    string output = "<br>You may input <b>" + command + " --help</b> for more information.";
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
    // check -h
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return description;
        }

    }
    if (args.size() == 1 && opts.size() == 1){
        if(opts[0] == "-c" || opts[0] == "--connect_components"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task5::print_connected_components(G);
                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> doesn't have connection components!!! <br>";
                }
                else{
                    return ans + " <br>";
                }
            }
        }
        if(opts[0] == "-e" || opts[0] == "--euler_graph"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task0::if_eulers_graph(G);
                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> isn't Eulers!!! <br>";
                }
                else{
                    return ans + "<br>";
                }
            }
        }
        if(opts[0] == "-b" || opts[0] == "--bipartite_graph"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task0::if_bipart_graph(G);
                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> isn't bipart!!!<br>";
                }
                else{
                    return ans + "<br>";
                }
            }
        }
    }
    if (args.size() == 2 && opts.size() == 1){
        if(opts[0] == "-c" || opts[0] == "--connect_components"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                stringstream ss(args[1]);
                int c;
                ss >> c;
                pair<bool,string> ans = task6::check_answer(G, c);
                if(ans.first){
                    return "You're right!!! <br>";
                }
                else{
                    return "You're not right! <br>";
                }
            }
        }
    }
    return "Usage of command <b>check</b> is incorrect." + output;
}

