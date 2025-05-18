#include "../include/commands/prufercommand.h"

string PruferCommand::execute(const string& command,
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
    // prufer -h
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return description;
        }
    }
    // prufer -c Graph_name
    if(args.size() == 1 && opts.size() == 1){
        if(opts[0] == "-c" || opts[0] == "--coding"){
            string graph_name = args[0];
            bool exist = list_commands::exist_file("graphs", graph_name, ".json");
            // если такой граф существует
            if (exist) {
                // создаем граф из JSON-файла
                Graph G = dataconverse::fromJSONfileToGraph(graph_name);
                string ans = task10::input(G);
                if(ans == "-1"){
                    return "Graph <b>" + graph_name + "</b> isn't tree!!!<br>";
                }
                return "Graph <b>" + graph_name + "</b> prufer code is <b>" + ans + "<\b><br>";

            }
        }
        // prufer -d code
        if(opts[0] == "-d" || opts[0] == "--decoding"){
            string points = to_string(args[0].size() + 1);
            Graph g = task11::input(args[0], points);
            string ans = g.get_str_graph();
            if(ans == "0"){
                return "This code isn't code prufer<br>";
            }
            return "This tree for Prufer's code:<br>" + ans + "<br>" ;
        }
    }




    return "Usage of command <b>prufer</b> is incorrect." + output;
}

