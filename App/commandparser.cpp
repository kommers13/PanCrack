#include <QDebug>
#include "include/commandparser.h"

const string pref = "PanCrack>";

// trimming of string from left edge
string ltrim(string s) {
    int i = 0;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
        i++;
    }
    return s.substr(i, s.size());
}

// trimmint of string from right edge
string rtrim(string s) {
    int i = s.size() - 1;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
        i--;
    }
    return s.substr(0, i + 1);
}

// trimming of both sides
string trim(string s) {
    return rtrim(ltrim(s));
}


CommandParser::CommandParser(Signals* _my_signals) :
    my_signals(_my_signals) {}


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
        if (c == ' ' || c == '\n') {
            // если это первое слово
            if (is_command) {
                not_options.push_back(trim(buffer));
                is_command = false;
            }
            else {
                // если это опция
                if (buffer[0] == '-'
                    &&
                    (buffer[1] == '-' || !('0' <= buffer[1] && buffer[1] <= '9'))
                    ) {
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

// сюда передается спаршенная команда, которая ТОЧНО существует,
// т. е. она должна выполнится ХОТЬ КАК
string CommandParser::execute_command(const string& command,
                                       const vector<string>& args,
                                       const vector<string>& opts) {
    if (command == "algorithm") {
        return AlgorithmCommand::execute(command, args, opts);
    }
    if (command == "check") {
        return CheckCommand::execute(command, args, opts);
    }
    if (command == "clear") {
        // данная команда нуждается в вызове JS-функции через испускание сигнала
        return ClearCommand::execute(command, args, opts, my_signals);
    }
    if (command == "prufer"){
        return PruferCommand::execute(command, args, opts);
    }
    if (command == "create") {
        // данная команда НЕ нуждается в вызове JS-функции через испускание сигнала
        return CreateCommand::execute(command, args, opts);
    }
    if (command == "draw") {
        // данная команда нуждается в вызове JS-функции
        return DrawCommand::execute(command, args, opts, my_signals);
    }
    if (command == "show") {
        return ShowCommand::execute(command, args, opts);
    }
    if (command == "view") {
        return ViewCommand::execute(command, args, opts);
    }
    if (command == "help") {
        return HelpCommand::execute(command, args, opts);
    }
    if (command == "color") {
        return ColorCommand::execute(command, args, opts, my_signals);
    }
    return "I don`t know how this happened, we need to check CommandParser::execute_command";
}


QString CommandParser::on_output_command(const QString& input) {
    // command, arguments, options
    auto parsed_command = this->process_command(input.toStdString());

    string output;

    string command = get<0>(parsed_command);
    vector<string> args = get<1>(parsed_command);
    vector<string> opts = get<2>(parsed_command);

    // qDebug() << "command: " << command;
    // qDebug() << "args: " << args;
    // qDebug() << "opts: " << opts;

    // если строка пустая, то возвращаем пустую строку

    if (command.size() == 0) {
        return QString();
    }

    // если такой команды не существует, то сообщаем об этом
    if (!list_commands::exist_file("cominf", command, ".json")) {
        output = "Command \"" + command + "\" doesn`t exist";
        return QString(output.c_str());
    }

    // запускаем команду
    output = execute_command(command, args, opts);

    // выводим ответ
    return QString(output.c_str());
}
