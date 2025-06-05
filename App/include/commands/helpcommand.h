#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "../listcommands.h"
#include "../dataconverse.h"
#include <string>
#include <vector>
#include <unordered_map>

#include "macros/commacros.h"


using namespace std;
class HelpCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );
};

#endif // HELPCOMMAND_H
