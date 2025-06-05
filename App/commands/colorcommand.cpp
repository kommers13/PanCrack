#include "../include/commands/colorcommand.h"

string ColorCommand::execute(
                            const string& command,      // имя команды
                            const vector<string>& args, // вектор строк-аргументов
                            const vector<string>& opts,  // вектор опций
                            Signals* my_signals
                            ) {
    // вывод команды
    string output;

    // документация команды
    string description;

    VALIDATE_COMMAND_FLAGS(command, opts);

    // =================== your business logic ===================

    // CHECKING OPTS
    if (opts.size() > 1) {
        output = "<b>color</b> can get only one unnecessary option." + output;
        return output;
    }

    // если аргументов больше 1
    if (args.size() > 1) {
        output = "<b>color</b> can get only one unnecessary argument." + output;
        return output;
    }


    // --help
    if (args.size() == 0 && opts.size() == 1 && (opts[0] == "--help" || opts[0] == "-h")) {
        return description + "<br>";
    }

    // нулевое количество аргументов
    if (args.size() == 0) {
        output = "You didn`t input any arguments, but <b>color</b> requires at least one." + output;
        return output;
    }

    // один аргумент и ноль опций
    if (args.size() == 1 && opts.size() == 0) {
        // проверяем наличие графа
        if (!list_commands::exist_file("graphs", args[0], ".json")) {
            output = "Graph <b>" + args[0] + "</b> doesn`t exist";
            return output;
        }
        // если такой граф есть, то преобразуем данный граф в QVariantMap из JSON-файла
        Graph graph = dataconverse::fromJSONfileToGraph(args[0]);

        // разукрашенный вершины
        vector<int> colors = task12::coloring(graph).first;

        QVariantMap graph_coords = graphdraw::draw_graph(graph, colors);

        emit my_signals->graphDraw(graph_coords);
        output = "Graph <b>" + args[0] + "</b> has been drawn";
        return output;
    }

     return "Usage of command <b>color</b> is incorrect." + output;
}
