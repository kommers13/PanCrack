#ifndef VIEWCOMMAND_H
#define VIEWCOMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <graph.h>
#include <task0.h>
#include "../listcommands.h"
#include "../dataconverse.h"

using namespace std;


class ViewCommand
{

    /*
        Прежде чем разрабатывать новую команду, нужно очистить проект:
        нужно нажать в меню в верхней части экрана "Сборка" и там "Очистка" под
        "PanCrackApp"

        И каждый раз, когда вы обновляете json-файлы команды вы должны очищать проект

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
