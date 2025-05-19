#include "../include/commands/algorithmcommand.h"
string AlgorithmCommand::execute(
                                const string& command,      // имя команды
                                const vector<string>& args, // вектор строк-аргументов
                                const vector<string>& opts  // вектор опций
                                ){
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

    // algorithm -h
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return description;
        }

    }
    if(args.size() == 1 && opts.size() == 1){

        if(opts[0] == "-s" || opts[0] == "--shortest_path"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task9::print_distance_matrix(task9::floyd_warshall(G));

                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> can't make matrix shortest path!!!<br>";
                }
                else{
                    return ans;
                }
            }
        }
        if(opts[0] == "-t" || opts[0] == "--skeleton_tree"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task7::create_MST(G).get_str_graph("<br>");

                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> can't make matrix shortest path!!!<br>";
                }
                else{
                    return "Ready skeleton tree:<br>" + ans;
                }
            }
        }
    }
    if(args.size() == 2 && opts.size() == 1){
        if(opts[0] == "-d" || opts[0] == "--dfs"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task1::print_DFS(G,args[1][0] - 65);

                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> can't make DFS!!!<br>";
                }
                else{
                    return ans;
                }
            }
        }
        if(opts[0] == "-b" || opts[0] == "--bfs"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                auto ans = task3::input(G,args[1]);

                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> can't make BFS!!!<br>";
                }
                else{
                    return ans;
                }
            }
        }

    }
    if(args.size() == 3 && opts.size() == 1){
        if(opts[0] == "-d" || opts[0] == "--dfs"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                char c = args[2][0];
                string a = task2::print_DFS(G, c-64);
                a = task4::parse(a);
                if(a != args[1]){
                    return "You're not right, Mr.Panteleev is very angry!!!<br>";
                }
                else{
                    return "You're right, Mr.Panteleev is proud of you!<br>";
                }
            }
        }
        if(opts[0] == "-b" || opts[0] == "--bfs"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task4::input(args[1], args[2], G);
                if(ans == ""){
                    return "Graph <b>" + graph_name + "</b> can't make BFS!!!<br>";
                }
                else{
                    return ans + "<br>";
                }
            }
        }
    }
    return "Usage of command <b>algorithm</b> is incorrect." + output;

}

