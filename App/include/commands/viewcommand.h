#ifndef VIEWCOMMAND_H
#define VIEWCOMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <graph.h>
#include <task0.h>
#include "../listcommands.h"
#include "../dataconverse.h"

#include "macros/commacros.h"

using namespace std;


class ViewCommand
{

    /*
        Для чтение графа есть удобное пространство имен dataconverse, посмотрите его
        заголовочный файл и используйте его на здоровье.

        Command 'view' allows to view a couple of the graph properties.
    */

public:

    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );

};

#endif // VIEWCOMMAND_H
