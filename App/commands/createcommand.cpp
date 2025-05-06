#include "../include/commands/createcommand.h"

string CreateCommand::execute(const string& command,
                              const vector<string>& args,
                              const vector<string>& opts,
                              Signals* my_signals) {
    string output = "<br>You may input <b>create --help</b> for more information.";
    // command name
    // description
    // {-h: --help} and so on
    auto com_inf = list_commands::get(command);

    string description = get<1>(com_inf);
    unordered_map<string, string> got_opts = get<2>(com_inf);

    // CHECKING OPTIONS
    // в данном случае всегда одна опция в create
    // проверка, существуют ли введенные флаги
    // если количество опций больше, чем может быть для этой команды
    // в данном случае, всего 1 опция
    if (opts.size() < 1 || 1 < opts.size()) {
        output = "<b>create</b> can get only one necessary option of the three." + output;
        return output;
    }
    // если хотя бы одна не совпадает, команда НЕ ВЫПОЛНЯЕТСЯ
    for (string opt: opts) {
        // если опция не найдена (ни короткая, ни полная)
        if (got_opts[opt] == "") {
            output = "Flag <b>" + opt + "</b> wasn`t found." + output;
            return output;
        }
    }

    // для create [-h]
    if (opts.size() == 1 && args.size() == 0 && (opts[0] == "--help" || opts[0] == "-h")) {
        return description + "<br>";
    }

    // для create -a|-i|-l graphname
    // CHECKING ARGUMENTS
    // проверка, правильно ли введены аргументы
    // в данном случае аргумент один - имя графа
    // если больше одного или меньше одного, то
    // мы должны сообщить об ошибке
    if (args.size() < 1 || 1 < args.size()) {
        output = "<font color=\"red\">create</font> has one required arguments." + output;
        return output;
    }
    // EXECUTING COMMAND
    // начинаем обрабатывать ПРАВИЛЬНО введенные данные
    // флаг -a
    if (opts.size() == 1 && (opts[0] == "--adjacency-matrix" || opts[0] == "-a")) {
        // если мы дошли до сюда, то все проверки прошли успешно, и мы можем выполнять функции
        emit my_signals->createCommand();
        output = "<b>--adjacency-matrix</b> is being developing.";
        return output;
    }
    // флаг -i
    if (opts.size() == 1 && (opts[0] == "--incidence-matrix" || opts[0] == "-i")) {
        output = "<b>--incidence-matrix</b> is being developing.";
        return output;
    }
    // флаг -l
    if (opts.size() == 1 && (opts[0] == "--adjacency-lists" || opts[0] == "-l")) {
        output = "<b>--adjacency-lists</b> is being developing.";
        return output;
    }
    // если мы дошли до сюда, то все проверки прошли успешно, и мы можем выполнять функции
    emit my_signals->createCommand();
    // в выводе будет небольшое описание графа, который создался
    output = "";
    return output;
}
