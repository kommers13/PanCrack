#include "../include/commands/createcommand.h"

#include <QDebug>


string construct(int type, const vector<string>& args) {
    // если мы дошли до сюда, то все проверки прошли успешно, и мы можем выполнять функции
    // строим матрицу смежности из аргументов
    // первый аргумент - это имя графа, остальные - описание графа, в данном случае
    // в виде матрицы смежности

    string output;

    // если все аргументы пустые, то заканчиваем
    if (args.size() == 0) {
        output = "<font color=\"red\">Error:</font> no arguments";
        return output;
    }

    string name = args[0];  // нужно проверить, что такого имени еще не было, прежде чем добавлять

    // проверка, что такого графа еще нет
    const string path = "graphs";
    for (const auto& entry: fs::directory_iterator(path)) {
        if (entry.path() == (path + "/" + name + ".json")) {
            output = "<font color=\"red\">Error:</font> graph <b>" + name + "</b> already exists";
            return output;
        }
    }

    // создание графа
    string data = "";
    for (int i = 1; i < args.size(); i++) {
        data += args[i];
        data += ' ';
    }

    // вывод ошибок, если они есть
    stringstream in_data(data);
    Graph* G;
    try {
        G = new Graph(type, in_data);
    }
    catch (const invalid_argument& e) {
        output = "<font color=\"red\">Error:</font> you input bad character, and I don`t tell where";
        return output;
    }
    catch (const logic_error& e) {
        string error_desc = e.what();
        output = "<font color=\"red\">Error:</font> " + error_desc;
        return output;
    }

    // запись графа в JSON-файл graphs/<name>.json
    dataconverse::fromGraphToJSONfile(*G, name);

    // сообщение о том, что граф был создан
    output = "Graph <b>" + name + "</b> has been constructed!<br>";
    output += G->get_str_graph("<br>");
    return output;
}


string CreateCommand::execute(const string& command,
                              const vector<string>& args,
                              const vector<string>& opts) {
    // вывод команды
    string output;

    // документация команды
    string description;

    VALIDATE_COMMAND_FLAGS(command, opts);

    // =================== your business logic ===================


    // в данном случае всегда одна опция в create
    // если количество опций больше, чем может быть для этой команды
    // в данном случае, всего 1 опция
    if (opts.size() < 1 || 1 < opts.size()) {
        output = "<b>create</b> can get only one necessary option of the three." + output;
        return output;
    }

    // для create [-h]
    if (opts.size() == 1 && args.size() == 0 && (opts[0] == "--help" || opts[0] == "-h")) {
        return description + "<br>";
    }

    // для create -a|-i|-l graphname data
    // CHECKING ARGUMENTS
    // проверка, правильно ли введены аргументы
    // в данном случае аргументов может быть любое количество, первый в args считается именем графа,
    // а остальные описанием его при помощи одного из трех способов
    // поэтому количество аргументов проверять не надо


    // EXECUTING COMMAND
    // начинаем обрабатывать ПРАВИЛЬНО введенные данные
    // флаг -a
    if (opts.size() == 1 && (opts[0] == "--adjacency-matrix" || opts[0] == "-a")) {
        return construct(0, args);
    }
    // флаг -i
    if (opts.size() == 1 && (opts[0] == "--incidence-matrix" || opts[0] == "-i")) {
        return construct(1, args);
    }
    // флаг -l
    if (opts.size() == 1 && (opts[0] == "--adjacency-lists" || opts[0] == "-l")) {
        return construct(2, args);
    }
    // это условие никогда не будет достигнуто
    output = "IT IS PROBLEM IN CREATECOMMAND::EXECUTE, CHECK IT URGENTLY";
    return output;
}
