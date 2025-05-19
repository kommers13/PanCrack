#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H


#include <QDebug>

#include "../signals.h"
#include "../listcommands.h"
#include "../dataconverse.h"
#include "../graphdraw.h"

#include <graph.h>
#include <task12.h>

#include <string>
#include <vector>

using namespace std;

class ColorCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts,  // вектор опций
        Signals* my_signals
        );
};

#endif // COLORCOMMAND_H
