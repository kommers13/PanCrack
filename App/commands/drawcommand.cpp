#include "../include/commands/drawcommand.h"


string DrawCommand::execute(const string& command,
                            const vector<string>& args,
                            const vector<string>& opts,
                            Signals* my_signals) {

    string output = "<br>You may input <b>" + command + " --help</b> for more information.";
    // command name
    // description
    // {-h: --help} and so on
    auto com_inf = list_commands::get(command);

    string description = get<1>(com_inf);
    unordered_map<string, string> got_opts = get<2>(com_inf);

    // CHECKING OPTS
    if (opts.size() > 1) {
        output = "<b>draw</b> can get only one unnecessary option." + output;
        return output;
    }

    // если хотя бы один не совпадает, команда НЕ ВЫПОЛНЯЕТСЯ
    for (string opt: opts) {
        // если флаг не найден (ни короткий, ни полный)
        if (got_opts[opt] == "") {
            output = "Flag <b>" + opt + "</b> wasn`t found." + output;
            return output;
        }
    }

    // CHECKING AMOUNT OF ARGS
    if (args.size() > 1) {
        output = "<b>draw</b> can get only ONE argument - name of graph." + output;
        return output;
    }

    // после всех проверок делаем так, как сказано в флагах
    // draw -h
    if (opts.size() == 1 && (opts[0] == "--help" || opts[0] == "-h") && args.size() == 0) {
        return description;
    }

    if (args.size() == 0) {
        output = "<b>draw</b> gets only one unnecessary option." + output;
        return output;
    }

    // если мы все проверили, то тогда получается, что нужно нарисовать граф

    // проверяем, есть ли такой граф
    // если такого графа нет, то выводим сообщение
    if (!list_commands::exist_file("graphs", args[0], ".json")) {
        output = "Graph <b>" + args[0] + "</b> doesn`t exist";
        return output;
    }

    // если такой граф есть, то преобразуем данный граф в QVariantMap из JSON-файла
    Graph graph = dataconverse::fromJSONfileToGraph(args[0]);

    // ТЕСТОВЫЕ ЦВЕТА (чтобы не передавать однотонные)
    vector<int> colors(graph.get_cnt_vertexes());
    for (int i = 0; i < colors.size(); i++) {
        colors[i] = i;
    }

    QVariantMap graph_coords = graphdraw::draw_graph(graph, colors);

    emit my_signals->graphDraw(graph_coords);
    output = "Graph <b>" + args[0] + "</b> has been drawn";
    return output;
}
