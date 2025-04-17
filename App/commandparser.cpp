#include "include/commandparser.h"
#include <QDebug>

CommandParser::CommandParser() : command(""), arguments(), options() {}



tuple<string,
      vector<string>,
      vector<string>
      > CommandParser::process_command(const string& input) {

    // ...

    command = "create";
    arguments.push_back("G");
    options.push_back("--matrix_of_adjacency");

    return make_tuple(command, arguments, options);
}

void CommandParser::output_command(const QString& input, QObject* text_field) {
    qDebug() << input;
    // ...
}
