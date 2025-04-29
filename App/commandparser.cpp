#include <QDebug>
#include "include/commandparser.h"

const string pref = "PanCrack>";

// trimming of string from left edge
string ltrim(string s) {
    int i = 0;
    while (s[i] == ' ' || s[i] == '\t') {
        i++;
    }
    return s.substr(i, s.size());
}

// trimmint of string from right edge
string rtrim(string s) {
    int i = s.size() - 1;
    while (s[i] == ' ' || s[i] == '\t') {
        i--;
    }
    return s.substr(0, i + 1);
}

string trim(string s) {
    return rtrim(ltrim(s));
}


CommandParser::CommandParser(ListCommands* _list_commands) :
    list_commands(_list_commands) {}


tuple<string,
      vector<string>,
      vector<string>
      > CommandParser::process_command(string input) {

    // это вектор НЕ ОПЦИЙ, т. е. в нем будут либо аргументы, либо команда
    // суть в том, что мы будет считать первый элемент этого вектора командой,
    // а все остальные за ним - аргументами
    vector<string> not_options;
    bool is_command = true; // нужно, чтобы командой была строка, которая идет первой

    input = input.substr(pref.size(), input.size());
    input = trim(input) + ' ';

    vector<string> options;     // порядок важен (если братки - command и arguments - внизу)

    // clear -h
    // clear --help
    // create G --matrix_of_adjacency
    // отличием опции от отрицательного числа - это наличие буквы за дефисом
    // теперь input не начинается с кучи пробелов и не заканчивается ими
    string buffer = "";
    for (int i = 0; i < input.size(); i++) {
        char c = input[i];
        buffer += c;
        if (c == ' ') {
            // если это первое слово
            if (is_command) {
                not_options.push_back(trim(buffer));
                is_command = false;
            }
            else {
                // если это опция
                if (buffer[0] == '-'
                    &&
                    (buffer[1] == '-' || !('0' <= buffer[1] && buffer[1] <= '9'))) {
                    options.push_back(trim(buffer));
                }
                else { // если НЕ ОПЦИЯ
                    string tbuffer = trim(buffer);
                    if (tbuffer.size() > 0) {
                        not_options.push_back(trim(buffer));
                    }
                }
            }
            buffer = "";
        }
    }

    string command = not_options[0];             // имя команды
    vector<string> arguments(++not_options.begin(), not_options.end());   // порядок важен

    return make_tuple(command, arguments, options);
}


QString CommandParser::on_output_command(const QString& input) {
    // command, arguments, options
    auto parsed_command = this->process_command(input.toStdString());

    string output;

    string command = get<0>(parsed_command);
    vector<string> args = get<1>(parsed_command);
    vector<string> opts = get<2>(parsed_command);

    qDebug() << "command: " << command;
    qDebug() << "args: " << args;
    qDebug() << "opts: " << opts;

    // если такой команды не существует, то сообщаем об этом
    if (!list_commands->exist_command(command)) {
        output = "Command \"" + command + "\" doesn`t exist";
        return QString(output.c_str());
    }

    // функция с определенными аргументами возвращает строку в output
    return QString("Empty");
}
