#include "../include/commands/showcommand.h"


string get_list_of_graphs(const string& path) {
    string list_of_graphs = "";

    list_of_graphs += "<b>Graphs created by user</b>: <br>";

    for (const auto& entry: fs::directory_iterator(path)) {

        string graph_file = entry.path().filename().string();

        string graph_ext = entry.path().filename().extension().string();

        string graph_name = graph_file.substr(0, graph_file.size() - graph_ext.size());

        list_of_graphs += graph_name + "<br>";
    }

    if (list_of_graphs == "") {

        return "So far user hasn`t created any graph yet";
    }

    return list_of_graphs;
}


string ShowCommand::execute(const string& command,
                            const vector<string>& args,
                            const vector<string>& opts) {
    string output = "<br>You may input <b>" + command + " --help</b> for more information.";
    // command name
    // description
    // {-h: --help} and so on
    auto com_inf = list_commands::get(command);

    string description = get<1>(com_inf);
    unordered_map<string, string> got_opts = get<2>(com_inf);

    // если хотя бы один не совпадает, команда НЕ ВЫПОЛНЯЕТСЯ
    for (string opt: opts) {
        // если флаг не найден (ни короткий, ни полный)
        if (got_opts[opt] == "") {
            output = "Flag <b>" + opt + "</b> wasn`t found." + output;
            return output;
        }
    }

    // show GRAPH_NAME
    // show -a (show --all)
    // show -h (show --help)

    // show GRAPH_NAME
    if (args.size() == 1 && opts.size() == 0) {
        string graph_name = args[0];
        bool exist = list_commands::exist_file("graphs", graph_name, ".json");
        // если такой граф существует
        if (exist) {
            // создаем граф из JSON-файла
            Graph G = dataconverse::fromJSONfileToGraph(graph_name);
            return "Graph <b>" + graph_name + "</b>:<br>" + \
                    G.get_str_graph("<br>");
        }
        // если не существует
        else {
            output = "Graph <b>" + graph_name + "</b> doesn`t exist.";
            return output;
        }
    }

    // show -a
    // show -h
    if (opts.size() == 1 && args.size() == 0) {
        string option = opts[0];
        if (option == "-a" || option == "--all") {
            // возвращаем список графов
            return get_list_of_graphs("graphs");
        }
        else if (option == "-h" || option == "--help") {
            return description;
        }
        // ЭТО НИКОГДА НЕ ВЫПОЛНИТСЯ
        return "CHECK SHOWCOMMAND.CPP URGENTLY";
    }

    // ОШИБКИ
    if (args.size() == 1 && opts.size() > 0) {
        output = "Command <b>show</b> can get only one argument without flags." + output;
        return output;
    }

    if (opts.size() == 1 && args.size() > 0) {
        output = "Command <b>show</b> can get only one option without arguments." + output;
        return output;
    }

    return "Incorrect usage of command <b>show</b>." + output;

}
