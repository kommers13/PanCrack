#ifndef PRUFERCOMMAND_H
#define PRUFERCOMMAND_H
#include "../listcommands.h"
#include "../dataconverse.h"
#include <task10.h>
#include <task11.h>
#include <graph.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "macros/commacros.h"

using namespace std;
class PruferCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );
};

#endif // PRUFERCOMMAND_H
