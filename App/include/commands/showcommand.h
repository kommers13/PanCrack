#ifndef SHOWCOMMAND_H
#define SHOWCOMMAND_H


#include <string>
#include <vector>
#include <unordered_map>

#include "../listcommands.h"
#include "../dataconverse.h"

#include "macros/commacros.h"

using namespace std;


class ShowCommand
{

    /*
        Command 'show' shows all graphs
    */

public:

    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
    );

};

#endif // SHOWCOMMAND_H
