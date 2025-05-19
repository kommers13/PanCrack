#ifndef FINDCOMMAND_H
#define FINDCOMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <graph.h>
#include <task7.h>
#include <task8.h>
#include "../listcommands.h"
#include "../dataconverse.h"
using namespace std;
class FindCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );
};

#endif // FINDCOMMAND_H
