#include "../include/commands/gamecommand.h"

#include <qDebug>

string GameCommand::execute(const string& command,
                            const vector<string>& args,
                            const vector<string>& opts,
                            Signals* my_signals) {


    // вывод команды
    string output;

    // документация команды
    string description;

    VALIDATE_COMMAND_FLAGS(command, opts);

    // =================== your business logic ===================

    // game -h
    // game --help
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return description;
        }
    }

    // game LEVEL
    if (args.size() == 1 && opts.size() == 0) {
        if (args[0] == "1") {
            my_signals->levelStart(QString("1"));
            return "Game '1' is loading...";
        }
        else {
            return "Game " + args[0] + " doesn`t exist.";
        }
    }

    return "Usage of command <b>" + command + "</b> is incorrect." + output;

}
