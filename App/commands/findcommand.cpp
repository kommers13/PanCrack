#include "../include/commands/findcommand.h"

string FindCommand::execute(const string& command,
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
    return "Usage of command <b>find</b> is incorrect." + output;
}
