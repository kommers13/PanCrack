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


    // view -d GRAPH_NAME VERTEX_NAME (аргументы здесь позиционные,
    // т. е. первым идет имя графа, а затем только имя вершины)
    // ...


    // view -c GRAPH_NAME
    // ...


    // view -d -a GRAPH_NAME (флаги можно вводить в любом порядке)
    // ...

    // сообщение пользователю об ошибках,
    // либо просто сказать ему, что он неправильно использовал команду и попросить
    // ПОЧИТАТЬ МАНУАЛ
    return "Usage of command <b>view</b> is incorrect." + output;

}
