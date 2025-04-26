#include <QDebug>
#include "include/commandparser.h"

CommandParser::CommandParser(const vector<pair<string, string>>& coms_and_hlp)
    : command(""), arguments(vector<string>()), options(vector<string>()),
    commands_and_help(coms_and_hlp) {}



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

void CommandParser::on_output_command(const QString& input, QObject* answer_field) {
    qDebug() << input;

    // ...

    // command, arguments, options
    auto parsed_command = this->process_command(input.toStdString());

    string output = "answer";
    answer_field->setProperty("text", QVariant(output.c_str()));

}
