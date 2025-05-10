#include "../include/commands/ilyuacommand.h"

string ILYUACommand::execute(const string& command,
                             const vector<string>& args,
                             const vector<string>& opts) {
    if (args.size() == 0 && opts.size() == 0) {
        return "ILYA is 19 years old";
    }

    if (args.size() == 1 && args[0] == "SEMEN") {
        return "SEMEN is Semyon";
    }

}
