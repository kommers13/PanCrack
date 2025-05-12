#include "../include/commands/clearcommand.h"

// если мы здесь, значит такая команда СУЩЕСТВУЕТ
string ClearCommand::execute(const string& command,
                             const vector<string>& args,
                             const vector<string>& opts,
                             Signals* my_signals) {
    string output = "<br>You may input <b>clear --help</b> for more information.";
    // command name
    // description
    // {-h: --help}, {-h: --help} and so on
    auto com_inf = list_commands::get(command);

    string description = get<1>(com_inf);
    unordered_map<string, string> got_opts = get<2>(com_inf);

    // CHECKING OPTIONS
    // проверка, существуют ли введенные флаги
    // если количество опций больше, чем может быть для этой команды
    if (opts.size() > 1) {
        output = "<b>clear</b> can get only one unnecessary option." + output;
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
    // CHECKING ARGUMENTS
    // проверка, правильно ли введены аргументы
    // в данном случае аргументов нет, но если мы найдем хотя бы один, то
    // мы должны сообщить об ошибке
    if (args.size() > 0) {
        output = "<font color=\"red\">clear</font> doesn`t have any required arguments." + output;
        return output;
    }
    // EXECUTING COMMAND
    // начинаем обрабатывать ПРАВИЛЬНО введенные данные
    // флаг справки
    if (opts.size() == 1 && (opts[0] == "--help" || opts[0] == "-h")) {
        return description + "<br>";
    }
    // если мы дошли до сюда, то все проверки прошли успешно, и мы можем выполнять функции
    emit my_signals->clearCommand();
    // в выводе у нее ничего нет, так как она очищает консоль
    output = "";
    return output;
}
