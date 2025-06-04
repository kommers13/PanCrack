#include "../include/commands/clearcommand.h"

// если мы здесь, значит такая команда СУЩЕСТВУЕТ
string ClearCommand::execute(const string& command,
                             const vector<string>& args,
                             const vector<string>& opts,
                             Signals* my_signals) {
    // вывод команды
    string output;

    // документация команды
    string description;

    VALIDATE_COMMAND_FLAGS(command, opts);

    // =================== your business logic ===================

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
