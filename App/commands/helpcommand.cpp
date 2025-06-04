#include "../include/commands/helpcommand.h"

string HelpCommand::execute(const string& command,
                     const vector<string>& args,
                     const vector<string>& opts) {

    // вывод команды
    string output;

    // документация команды
    string description;

    VALIDATE_COMMAND_FLAGS(command, opts);

    // =================== your business logic ===================

    // к этому моменту мы знаем, что если мы оказались здесь, то все опции правильные
    if (args.size() == 0 && opts.size() == 1) {
        if (opts[0] == "-h" || opts[0] == "--help") {
            return "Just input <i>help</i> for reference.";
        }
    }
    return description;
}
